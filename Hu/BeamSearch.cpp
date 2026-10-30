#pragma once
#include <vector>
#include <algorithm>
#include <cstdint>
#include <concepts>
#include <limits>

namespace Hu {

/**
 * @brief ビームサーチの探索木ノード (BeamNode)
 * 
 * 状態全体ではなく、「親ノードへのインデックス」と「選んだ手 (Action)」を保持することで
 * メモリ消費を最小限に抑え、探索終了後に根までの行動履歴を高速に復元します。
 */
template <typename Action, typename ScoreType = double>
struct BeamNode {
    ScoreType score;
    int parent_idx;      // 直前の深さにおける親ノードのインデックス (-1 は根)
    Action action;       // 親からこのノードへ遷移した行動
    uint64_t hash_key;   // 同一盤面の重複排除用ハッシュ (不要な場合は0)

    bool operator>(const BeamNode& other) const {
        return score > other.score;
    }
    bool operator<(const BeamNode& other) const {
        return score < other.score;
    }
};

/**
 * @brief 汎用ビームサーチ (BeamSearch)
 * 
 * @tparam State 探索状態のクラス
 * @tparam Action 1ステップの行動・遷移を表す型
 * @tparam ScoreType スコアの型 (double, int64_t など)
 * 
 * 状態 State に求められる要件:
 *   - void apply(const Action& act): 行動を適用して状態を進める
 *   - void get_next_actions(std::vector<std::pair<Action, ScoreType>>& cand) const:
 *       次に取りうる候補手と、その手を適用した後の評価スコアのペアを列挙する
 *   - (任意) uint64_t get_hash() const: 状態のハッシュ値を返す (重複排除用)
 */
template <typename State, typename Action, typename ScoreType = double, bool Maximize = true>
class BeamSearch {
public:
    using Node = BeamNode<Action, ScoreType>;

    struct Result {
        ScoreType best_score;
        std::vector<Action> actions; // 根から最良解までの行動列
        State final_state;          // 最終状態
    };

    /**
     * @brief ビームサーチを実行する
     * 
     * @param initial_state 初期状態
     * @param max_depth 探索する深さ (手数・ターン数)
     * @param beam_width 各深さで保持する候補数 (ビーム幅)
     * @return Result 最良解とその行動履歴
     */
    static Result solve(const State& initial_state, int max_depth, int beam_width) {
        // 各深さのノードリスト: tree[d] = 深さ d の全候補ノード
        std::vector<std::vector<Node>> tree(max_depth + 1);
        std::vector<std::vector<State>> states(max_depth + 1);

        // 深さ 0 (根ノード)
        tree[0].push_back(Node{ScoreType(0), -1, Action{}, 0});
        states[0].push_back(initial_state);

        std::vector<std::pair<Action, ScoreType>> candidate_actions;

        for (int d = 0; d < max_depth; ++d) {
            std::vector<Node> next_beam;
            std::vector<int> parent_indices;

            // 前の深さの各ノードから次手を展開
            for (int p_idx = 0; p_idx < (int)tree[d].size(); ++p_idx) {
                const State& cur_state = states[d][p_idx];
                candidate_actions.clear();
                cur_state.get_next_actions(candidate_actions);

                for (const auto& [act, score] : candidate_actions) {
                    Node child;
                    child.score = score;
                    child.parent_idx = p_idx;
                    child.action = act;
                    child.hash_key = 0; // 必要に応じて設定
                    next_beam.push_back(child);
                }
            }

            if (next_beam.empty()) break; // 進行不能

            // 上位 beam_width 個を選択
            auto comp = [](const Node& a, const Node& b) {
                if constexpr (Maximize) {
                    return a.score > b.score;
                } else {
                    return a.score < b.score;
                }
            };

            int keep_size = std::min((int)next_beam.size(), beam_width);
            std::nth_element(next_beam.begin(), next_beam.begin() + keep_size, next_beam.end(), comp);
            next_beam.resize(keep_size);
            std::sort(next_beam.begin(), next_beam.end(), comp);

            // 次の深さの状態を生成
            std::vector<State> next_states(keep_size);
            for (int i = 0; i < keep_size; ++i) {
                next_states[i] = states[d][next_beam[i].parent_idx];
                next_states[i].apply(next_beam[i].action);
            }

            tree[d + 1] = std::move(next_beam);
            states[d + 1] = std::move(next_states);
        }

        // 最良ノードを探索
        int best_depth = 0;
        int best_idx = 0;
        ScoreType best_score = (Maximize ? -std::numeric_limits<ScoreType>::infinity()
                                         : std::numeric_limits<ScoreType>::infinity());

        for (int d = max_depth; d >= 0; --d) {
            if (!tree[d].empty()) {
                best_depth = d;
                best_idx = 0; // sort されているので 0 番目が最良
                best_score = tree[d][0].score;
                break;
            }
        }

        // 行動履歴の復元 (Backtrack)
        std::vector<Action> actions;
        int cur_d = best_depth;
        int cur_idx = best_idx;
        while (cur_d > 0 && cur_idx != -1) {
            actions.push_back(tree[cur_d][cur_idx].action);
            cur_idx = tree[cur_d][cur_idx].parent_idx;
            --cur_d;
        }
        std::reverse(actions.begin(), actions.end());

        return Result{best_score, actions, states[best_depth][best_idx]};
    }
};

} // namespace Hu
