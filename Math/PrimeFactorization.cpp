#pragma once
#include <vector>
#include <utility>

/**
 * @brief 素因数分解を行う (O(√N))
 * 
 * @param N 分解対象の整数
 * @return std::vector<std::pair<long long, long long>> {素因数, 指数} のリスト
 */
inline std::vector<std::pair<long long, long long>> p_fact(long long N) {
  std::vector<std::pair<long long, long long>> res;
  for (long long a = 2; a * a <= N; ++a) {
    if (N % a != 0) continue;
    long long ex = 0;  // 指数

    // 割れる限り割り続ける
    while (N % a == 0) {
      ++ex;
      N /= a;
    }

    res.push_back({a, ex});
  }

  // 最後に残った数について
  if (N != 1) {
    res.push_back({N, 1});
  }
  return res;
}
