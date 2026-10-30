#pragma once
#include "HuUtils.cpp"
#include <cmath>
#include <string>
#include <iostream>

namespace Hu {

/**
 * @brief 焼きなまし法・山登り法の受理判定器 (AnnealingAcceptor)
 * 
 * 最大化問題 (Maximize) と 最小化問題 (Minimize) の双方に対応し、
 * 現在の進行度 progress in [0, 1] に応じた温度計算と採択確率の判定を行います。
 */
class AnnealingAcceptor {
public:
    enum class Objective {
        Maximize,
        Minimize
    };

private:
    double start_temp;
    double end_temp;
    Objective obj;
    XorShift rng;

    // 統計情報
    uint64_t total_iterations = 0;
    uint64_t accepted_moves = 0;
    uint64_t improved_moves = 0;

public:
    AnnealingAcceptor(double start_temperature, double end_temperature,
                      Objective objective = Objective::Maximize, uint64_t seed = 88172645463325252ULL)
        : start_temp(start_temperature), end_temp(end_temperature), obj(objective), rng(seed) {}

    /// 山登り法用の初期化 (悪化遷移を一切許容しない)
    static AnnealingAcceptor create_hill_climbing(Objective objective = Objective::Maximize) {
        return AnnealingAcceptor(0.0, 0.0, objective);
    }

    /// 現在の進行割合 [0, 1] に応じた温度を計算 (指数冷却 / 線形冷却)
    inline double get_temperature(double progress) const {
        if (start_temp <= 0.0) return 0.0;
        // 指数スケジュール: start_temp * (end_temp / start_temp)^progress
        return start_temp * std::pow(end_temp / start_temp, progress);
    }

    /**
     * @brief 遷移を採用するかどうか判定する
     * 
     * @param current_score 変更前のスコア
     * @param next_score 変更後のスコア
     * @param progress 探索の進行割合 [0.0, 1.0]
     * @return true 遷移を採用する (更新確定)
     * @return false 遷移を棄却する (ロールバック)
     */
    inline bool accept(double current_score, double next_score, double progress) {
        ++total_iterations;

        double delta;
        if (obj == Objective::Maximize) {
            delta = next_score - current_score;
        } else {
            delta = current_score - next_score;
        }

        // スコア改善（または変化なし）は常に受理
        if (delta >= 0.0) {
            if (delta > 0.0) ++improved_moves;
            ++accepted_moves;
            return true;
        }

        // 山登り法設定、または探索終盤で温度がほぼ0なら棄却
        if (start_temp <= 0.0 || progress >= 1.0) {
            return false;
        }

        double temp = get_temperature(progress);
        if (temp <= 1e-9) return false;

        // メトロポリス基準: exp(delta / temp) > rand[0, 1)
        double prob = std::exp(delta / temp);
        if (rng.next_double() < prob) {
            ++accepted_moves;
            return true;
        }

        return false;
    }

    /// 統計情報を文字列として取得
    std::string summary() const {
        std::string res;
        res += "Iterations: " + std::to_string(total_iterations) + "\n";
        res += "Accepted:   " + std::to_string(accepted_moves);
        if (total_iterations > 0) {
            res += " (" + std::to_string(accepted_moves * 100.0 / total_iterations) + "%)\n";
        } else {
            res += "\n";
        }
        res += "Improved:   " + std::to_string(improved_moves) + "\n";
        return res;
    }

    void reset_stats() {
        total_iterations = 0;
        accepted_moves = 0;
        improved_moves = 0;
    }

    uint64_t get_iterations() const { return total_iterations; }
    uint64_t get_accepted() const { return accepted_moves; }
    uint64_t get_improved() const { return improved_moves; }
};

} // namespace Hu
