#include "BeamSearch.cpp"
#include "ChokudaiSearch.cpp"
#include "HuUtils.cpp"
#include <iostream>
#include <vector>
#include <string>

// グリッド問題の設定
constexpr int H = 20;
constexpr int W = 20;
int grid[H][W];

// 4近傍の移動方向
const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};
const char dir_char[4] = {'U', 'D', 'L', 'R'};

// 探索状態 (State)
struct GridState {
    int r = 0, c = 0;       // 現在座標
    int current_score = 0;  // 累積スコア
    int turn = 0;           // 現在のターン数

    // 行動 (Action: 方向インデックス 0~3) を適用
    void apply(int act) {
        r += di[act];
        c += dj[act];
        current_score += grid[r][c];
        ++turn;
    }

    // 次に取りうる候補手とスコアの列挙
    void get_next_actions(std::vector<std::pair<int, int>>& cand) const {
        for (int d = 0; d < 4; ++d) {
            int nr = r + di[d];
            int nc = c + dj[d];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                cand.emplace_back(d, current_score + grid[nr][nc]);
            }
        }
    }
};

int main() {
    std::cout << "=== グリッド移動によるビームサーチ & Chokudaiサーチの比較 ===" << std::endl;

    // 盤面の生成 (0〜99のスコアを各マスに配置)
    Hu::XorShift rng(42);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            grid[i][j] = rng.next_range(0, 99);
        }
    }

    const int MAX_TURNS = 30;
    GridState start_state;
    start_state.r = 0;
    start_state.c = 0;
    start_state.current_score = grid[0][0];

    // ---------------------------------------------------------
    // A. 汎用ビームサーチ (Beam Search)
    // ---------------------------------------------------------
    {
        Hu::Timer timer(1.0);
        const int BEAM_WIDTH = 50;

        auto result = Hu::BeamSearch<GridState, int, int, true>::solve(
            start_state, MAX_TURNS, BEAM_WIDTH
        );

        std::cout << "\n[ビームサーチ 結果 (幅=" << BEAM_WIDTH << ")]" << std::endl;
        std::cout << "獲得スコア: " << result.best_score << std::endl;
        std::cout << "最終座標:   (" << result.final_state.r << ", " << result.final_state.c << ")" << std::endl;
        std::cout << "移動経路:   ";
        for (int act : result.actions) std::cout << dir_char[act];
        std::cout << "\n実行時間:   " << timer.elapsed_ms() << " ms" << std::endl;
    }

    // ---------------------------------------------------------
    // B. Chokudai サーチ (Chokudai Search)
    // ---------------------------------------------------------
    {
        Hu::Timer timer(0.05); // 0.05秒の制限時間
        const int EXPAND_PER_DEPTH = 2;

        auto result = Hu::ChokudaiSearch<GridState, int, int, true>::solve(
            start_state, MAX_TURNS, EXPAND_PER_DEPTH, timer
        );

        std::cout << "\n[Chokudai サーチ 結果 (制限時間=50ms)]" << std::endl;
        std::cout << "獲得スコア: " << result.best_score << std::endl;
        std::cout << "最終座標:   (" << result.final_state.r << ", " << result.final_state.c << ")" << std::endl;
        std::cout << "移動経路:   ";
        for (int act : result.actions) std::cout << dir_char[act];
        std::cout << "\n反復周回数: " << result.total_iterations << std::endl;
        std::cout << "実行時間:   " << timer.elapsed_ms() << " ms" << std::endl;
    }

    return 0;
}
