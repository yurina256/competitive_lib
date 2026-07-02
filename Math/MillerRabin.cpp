#pragma once
#include <vector>

/**
 * @brief ミラー・ラビン素数判定法 (Miller-Rabin Primality Test)
 * 
 * 64bit 整数 (unsigned long long) 範囲の大きな数が素数であるかを決定的に判定します。
 * GCCの __uint128_t を用いることでオーバーフローを防止しています。
 * 
 * 計算量: O(K log^3 N) (K: 基地の数。2^64未満では K = 7)
 */
struct MillerRabin {
  using u64 = unsigned long long;
  using u128 = __uint128_t;

  /**
   * @brief 安全なべき乗計算 (a^b % mod)
   */
  static u64 power(u64 a, u64 b, u64 mod) {
    u64 res = 1;
    a %= mod;
    while (b > 0) {
      if (b & 1) res = (u128)res * a % mod;
      a = (u128)a * a % mod;
      b >>= 1;
    }
    return res;
  }

  /**
   * @brief 素数判定本体
   * @return bool 素数であれば true, 合成数または1以下であれば false
   */
  static bool is_prime(u64 n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    u64 d = n - 1;
    u64 s = 0;
    while (d % 2 == 0) {
      d /= 2;
      s++;
    }

    // 2^64 未満のすべての奇数に対して決定的に判定可能な基地 (bases)
    const std::vector<u64> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    for (u64 a : bases) {
      if (n <= a) break;
      u64 y = power(a, d, n);
      if (y == 1 || y == n - 1) continue;
      bool composite = true;
      for (u64 r = 1; r < s; r++) {
        y = (u128)y * y % n;
        if (y == n - 1) {
          composite = false;
          break;
        }
      }
      if (composite) return false;
    }
    return true;
  }
};
