#pragma once
#include <functional>

/**
 * @brief 二分探索 (True -> False)
 * 
 * 条件 f(mid) が True となる境界を探す。
 * l 側が True、r 側が False であり、境界の True 側の最大インデックスを返す。
 * 
 * @param l 探索下限（True であることが保証されている、または条件を満たす最小値より1小さい値）
 * @param r 探索上限（False であることが保証されている、または条件を満たす最大値より1大きい値）
 * @param f 判定関数 (bool)
 * @return long long f(x) == true となる最大の x
 */
inline long long binary_search_tf(long long l, long long r, std::function<bool(long long)> f) {
  while (r - l > 1) {
    long long mid = l + (r - l) / 2;
    if (f(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return l;
}

/**
 * @brief 二分探索 (False -> True)
 * 
 * 条件 f(mid) が True となる境界を探す。
 * l 側が False、r 側が True であり、境界の False 側の最大インデックス（すなわち True の直前）を返す。
 * True となる最小値を得るには `binary_search_ft(l, r, f) + 1` のように調整するか、この戻り値を利用します。
 * 
 * @param l 探索下限（False であることが保証されている）
 * @param r 探索上限（True であることが保証されている）
 * @param f 判定関数 (bool)
 * @return long long f(x) == false となる最大の x
 */
inline long long binary_search_ft(long long l, long long r, std::function<bool(long long)> f) {
  while (r - l > 1) {
    long long mid = l + (r - l) / 2;
    if (f(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return l;
}
