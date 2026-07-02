#pragma once
#include <vector>
#include <cmath>

/**
 * @brief エラトステネスの篩 (Sieve of Eratosthenes)
 * 
 * 前計算 O(N log log N) で、N 以下の素数判定を O(1) で行い、
 * 累積和を用いて区間内の素数の個数を O(1) で計算する構造体。
 */
struct Eratosthenes {
  std::vector<bool> vec;
  std::vector<int> acc;

  /**
   * @brief コンストラクタ
   * @param n 最大値 N
   */
  Eratosthenes(int n) {
    // 判定パート
    vec.resize(n + 1, true);
    if (n >= 0) vec[0] = false;
    if (n >= 1) vec[1] = false;
    for (int i = 2; i * i <= n; i++) {
      if (!vec[i]) continue;
      for (int j = i * 2; j <= n; j += i) {
        vec[j] = false;
      }
    }

    // 累積和パート
    acc.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      acc[i] = acc[i - 1] + (vec[i] ? 1 : 0);
    }
  }

  /**
   * @brief index が素数であるかを判定する (O(1))
   */
  bool get(int index) {
    if (index < 0 || (int)vec.size() <= index) return false;
    return vec[index];
  }

  /**
   * @brief 半開区間 [l, r) における素数の個数を返す (O(1))
   */
  int prod(int l, int r) {
    if (l > r || l < 0) return 0;
    int limit = vec.size() - 1;
    r = std::min(r, limit + 1);
    l = std::min(l, limit + 1);
    return acc[r] - acc[l];
  }
};
