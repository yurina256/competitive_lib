#pragma once
#include <chrono>
#include <cstdint>
#include <limits>

namespace Hu {

/**
 * @brief 高速擬似乱数生成器 (xoshiro256** / 64-bit XorShift)
 * 
 * 標準の std::mt19937 比で数倍高速に動作し、
 * 1秒間に数百万〜数千万回のループを回す焼きなまし法やビームサーチに適しています。
 */
struct XorShift {
    using result_type = uint64_t;
    uint64_t state[4];

    static constexpr uint64_t default_seed = 88172645463325252ULL;

    explicit XorShift(uint64_t seed = default_seed) {
        set_seed(seed);
    }

    void set_seed(uint64_t seed) {
        // SplitMix64 でシードを4つの状態に初期展開
        for (int i = 0; i < 4; ++i) {
            seed += 0x9e3779b97f4a7c15ULL;
            uint64_t z = seed;
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
            state[i] = z ^ (z >> 31);
        }
    }

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    /// 64ビット非負整数乱数を生成
    inline uint64_t next() {
        const uint64_t result = rotl(state[1] * 5, 7) * 9;
        const uint64_t t = state[1] << 17;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = rotl(state[3], 45);
        return result;
    }

    inline uint64_t operator()() {
        return next();
    }

    static constexpr uint64_t min() { return 0; }
    static constexpr uint64_t max() { return std::numeric_limits<uint64_t>::max(); }

    /// [0, n) の範囲の一様整数乱数を取得
    inline uint64_t next_int(uint64_t n) {
        return next() % n;
    }

    /// [low, high] の範囲の一様整数乱数を取得
    inline int64_t next_range(int64_t low, int64_t high) {
        return low + static_cast<int64_t>(next() % (high - low + 1));
    }

    /// [0.0, 1.0) の範囲の一様実数乱数を取得
    inline double next_double() {
        return (next() >> 11) * (1.0 / 9007199254740992.0); // 53-bit resolution
    }

    /// 確率 p で true を返す
    inline bool toss(double p) {
        return next_double() < p;
    }
};

/**
 * @brief 高精度タイマー (Timer)
 * 
 * 開始時刻からの経過秒数・ミリ秒数、制限時間に対する進行割合 [0.0, 1.0] を取得できます。
 */
class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    double time_limit_sec;

public:
    explicit Timer(double time_limit_seconds = 2.0)
        : start_time(std::chrono::high_resolution_clock::now()),
          time_limit_sec(time_limit_seconds) {}

    /// タイマーをリセット
    inline void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    /// 経過秒数を取得 (double)
    inline double elapsed_sec() const {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(now - start_time).count();
    }

    /// 経過ミリ秒数を取得 (double)
    inline double elapsed_ms() const {
        return elapsed_sec() * 1000.0;
    }

    /// 制限時間に対する進行割合 [0.0, 1.0+] を取得
    inline double progress() const {
        return elapsed_sec() / time_limit_sec;
    }

    /// 制限時間を超過したか判定
    inline bool is_time_over() const {
        return elapsed_sec() >= time_limit_sec;
    }
};

} // namespace Hu
