#pragma once
#include "HuUtils.cpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

namespace Hu {

/**
 * @brief Chokudai サーチ (ChokudaiSearch)
 * 
 * 深さごとに優先度付きキュー（またはソート配列）を保持し、
 * 時間が許す限り浅い深さと深い深さを交互に何周も展開し続ける時間駆動型木探索です。
 * ビーム幅を事前に決め打ちする必要がなく、制限時間いっぱい計算資源を使い切ることができます。
 * 
 * @tparam State 探索状態のクラス
 * @tparam Action 1ステップの行動を表す型
 * @tparam ScoreType スコアの型
 * @tparam Maximize スコアを最大化するかどうか (true: 最大化, false: 最小化)
 */
template <typename State, typename Action, typename ScoreType = double, bool Maximize = true>
class ChokudaiSearch {
public:
    struct SearchNode {
        ScoreType score;
        int state_id;    // 状態プール内のインデックス
        int parent_id;   // 親ノードの state_id (-1 は根)
        Action action;   // 親からこのノードに至った手
        int depth;       // ノードの深さ

        bool operator<(const SearchNode& other) const {
            if constexpr (Maximize) {
                return score < other.score; // 最大ヒープ用: score が大きい方が優先
            } else {
                return score > other.score; // 最小ヒープ用: score が小さい方が優先
            }
        }
    };

    struct Result {
        ScoreType best_score;
        std::vector<Action> actions;
        State final_state;
        int total_iterations;
    };

    /**
     * @brief Chokudai サーチを実行する
     * 
     * @param initial_state 初期状態
     * @param max_depth 最大深さ (手数・ターン数)
     * @param expand_per_depth 1周あたり各深さから展開するノード数 (通常 1〜3 程度)
     * @param timer 制限時間を管理するタイマー
     * @param beam_capacity 各深さで保持する最大ノード数 (メモリ溢れ防止用, デフォルト 2000)
     * @return Result 最良解とその行動履歴
     */
    static Result solve(const State& initial_state, int max_depth, int expand_per_depth,
                        const Timer& timer, int beam_capacity = 2000) {
        // 各深さごとの優先度付きキュー
        std::vector<std::priority_queue<SearchNode>> pque(max_depth + 1);

        // 木構造・状態のプール
        std::vector<State> state_pool;
        std::vector<SearchNode> node_pool;
        state_pool.reserve(beam_capacity * (max_depth + 1));
        node_pool.reserve(beam_capacity * (max_depth + 1));

        auto add_node = [&](const State& st, ScoreType sc, int parent_id, const Action& act, int depth) -> int {
            int id = static_cast<int>(state_pool.size());
            state_pool.push_back(st);
            SearchNode node{sc, id, parent_id, act, depth};
            node_pool.push_back(node);
            pque[depth].push(node);
            return id;
        };

        // 根ノード (深さ 0) を追加
        add_node(initial_state, ScoreType(0), -1, Action{}, 0);

        int best_node_id = 0;
        int best_reached_depth = 0;
        ScoreType best_score = (Maximize ? -std::numeric_limits<ScoreType>::infinity()
                                         : std::numeric_limits<ScoreType>::infinity());

        int iterations = 0;
        std::vector<std::pair<Action, ScoreType>> candidate_actions;

        // 時間制限まで何周も回す
        while (!timer.is_time_over()) {
            ++iterations;
            bool any_expanded = false;

            for (int d = 0; d < max_depth; ++d) {
                if (timer.is_time_over()) break;

                for (int e = 0; e < expand_per_depth; ++e) {
                    if (pque[d].empty()) break;

                    SearchNode cur = pque[d].top();
                    pque[d].pop();
                    any_expanded = true;

                    // vector の再確保で参照が無効化されないよう値コピー
                    State cur_st = state_pool[cur.state_id];
                    candidate_actions.clear();
                    cur_st.get_next_actions(candidate_actions);

                    for (const auto& [act, sc] : candidate_actions) {
                        if ((int)pque[d + 1].size() >= beam_capacity) {
                            // キャパシティ超過時は追加をスキップ
                            continue;
                        }

                        State next_st = cur_st;
                        next_st.apply(act);

                        int next_id = add_node(next_st, sc, cur.state_id, act, d + 1);

                        // 最大深さ到達を最優先し、その中で最良スコアを保持
                        int next_depth = d + 1;
                        bool update = false;
                        if (next_depth > best_reached_depth) {
                            update = true;
                        } else if (next_depth == best_reached_depth) {
                            if constexpr (Maximize) {
                                if (sc > best_score) update = true;
                            } else {
                                if (sc < best_score) update = true;
                            }
                        }

                        if (update) {
                            best_reached_depth = next_depth;
                            best_score = sc;
                            best_node_id = next_id;
                        }
                    }
                }
            }

            if (!any_expanded) {
                // 全ノードを展開し尽くした場合は早期終了
                break;
            }
        }

        // 行動履歴の復元 (Backtrack)
        std::vector<Action> actions;
        int cur_id = best_node_id;
        while (cur_id > 0 && cur_id < (int)node_pool.size()) {
            actions.push_back(node_pool[cur_id].action);
            cur_id = node_pool[cur_id].parent_id;
        }
        std::reverse(actions.begin(), actions.end());

        return Result{best_score, actions, state_pool[best_node_id], iterations};
    }
};

} // namespace Hu
