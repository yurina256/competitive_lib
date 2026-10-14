#pragma once
#include <vector>
#include <algorithm>

using ll = long long;

constexpr ll LIS_INF = 4001001001001001001ll;

/**
 * @brief 最長増加部分列 (Longest Increasing Subsequence / LIS)
 * 
 * @param input 対象の配列
 * @param strict true の場合は「狭義」単調増加、false の場合は「広義」単調増加
 * @return ll 最長増加部分列の長さ
 */
inline ll get_lis(const std::vector<ll>& input, bool strict = true) {
  ll n = input.size();
  std::vector<ll> dp(n + 2, LIS_INF);
  for (ll i = 0; i < n; i++) {
    ll a = input[i];
    auto iter = strict ? std::lower_bound(dp.begin(), dp.end(), a) 
                       : std::upper_bound(dp.begin(), dp.end(), a);
    *iter = a;
  }
  return std::lower_bound(dp.begin(), dp.end(), LIS_INF) - dp.begin();
}
