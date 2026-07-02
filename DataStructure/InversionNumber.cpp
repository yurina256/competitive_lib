#pragma once
#include <vector>
#include <algorithm>
#include <atcoder/segtree>

/**
 * @brief 座標圧縮 (O(N log N))
 * 
 * 配列の要素を 0 から始まる重複のないインデックスに変換する。
 * 例: {10, 50, 20, 20} -> {0, 2, 1, 1}
 */
inline void zaatu(std::vector<long long>& vec) {
  std::vector<long long> tmp_vec = vec;
  std::sort(tmp_vec.begin(), tmp_vec.end());
  tmp_vec.erase(std::unique(tmp_vec.begin(), tmp_vec.end()), tmp_vec.end());
  for (size_t i = 0; i < vec.size(); ++i) {
    vec[i] = std::lower_bound(tmp_vec.begin(), tmp_vec.end(), vec[i]) - tmp_vec.begin();
  }
}

/**
 * @brief 転倒数を求める (O(N log N))
 * 
 * i < j かつ v[i] > v[j] となる組の個数を求める。
 */
inline long long inv_num(std::vector<long long> v) {
  long long n = v.size();
  zaatu(v);
  auto op = [](long long a, long long b) { return a + b; };
  auto e = []() { return 0ll; };
  atcoder::segtree<long long, op, e> seg(n + 1);
  long long ans = 0;
  for (long long val : v) {
    ans += seg.prod(val + 1, n + 1);
    seg.set(val, seg.get(val) + 1);
  }
  return ans;
}
