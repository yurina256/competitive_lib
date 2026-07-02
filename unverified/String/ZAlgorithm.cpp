#pragma once
#include <vector>
#include <string>

/**
 * @brief Z-algorithm
 * 
 * 文字列 S について、各 i において「S全体とS[i..]の最長共通接頭辞 (LCP) の長さ」を記録した配列を返します。
 * 
 * 計算量: O(|S|)
 * 
 * @param s 対象の文字列
 * @return std::vector<int> LCP長の配列
 */
inline std::vector<int> z_algorithm(const std::string& s) {
  int n = s.size();
  std::vector<int> z(n);
  if (n == 0) return z;
  z[0] = n;
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && s[j] == s[i + j]) j++;
    z[i] = j;
    if (j == 0) {
      i++;
      continue;
    }
    int k = 1;
    while (i + k < n && k + z[k] < j) {
      z[i + k] = z[k];
      k++;
    }
    i += k;
    j -= k;
  }
  return z;
}
