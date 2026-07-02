#pragma once
#include <vector>
#include <algorithm>

constexpr int LIS_INF = 1001001001;

/**
 * @brief 最長増加部分列 (Longest Increasing Subsequence / LIS)
 * 
 * @param input 対象の配列
 * @param strict true の場合は「狭義」単調増加、false の場合は「広義」単調増加
 * @return int 最長増加部分列の長さ
 */
inline int get_lis(const std::vector<int>& input, bool strict = true) {
  int n = input.size();
  std::vector<int> dp(n + 2, LIS_INF);
  for (int i = 0; i < n; i++) {
    int a = input[i];
    auto iter = strict ? std::lower_bound(dp.begin(), dp.end(), a) 
                       : std::upper_bound(dp.begin(), dp.end(), a);
    *iter = a;
  }
  return std::lower_bound(dp.begin(), dp.end(), LIS_INF) - dp.begin();
}
