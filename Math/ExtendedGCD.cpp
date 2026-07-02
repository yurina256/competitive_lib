#pragma once
#include <utility>
#include <tuple>

/**
 * @brief 拡張ユークリッドの互除法 (Extended Euclidean Algorithm)
 * 
 * 方程式 ax + by = gcd(a, b) を満たす整数の組 (x, y) の一例を求める。
 * 
 * @param a 入力定数 a
 * @param b 入力定数 b
 * @return std::pair<long long, long long> 整数の組 {x, y}
 */
inline std::pair<long long, long long> extgcd(long long a, long long b) {
  if (b == 0) return {1, 0};
  long long x, y;
  std::tie(y, x) = extgcd(b, a % b);
  y -= a / b * x;
  return {x, y};
}
