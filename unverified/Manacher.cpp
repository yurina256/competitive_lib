#pragma once
#include <vector>
#include <string>

/**
 * @brief Manacher's Algorithm
 * 
 * 文字列 S について、各 i において「s[i] を中心とする最長奇数長回文の半径（(全長+1)/2）」を計算して返します。
 * 偶数長の回文も検出したい場合は、文字列の文字間にダミー文字を挿入（例: "aba" -> "$a$b$a$"）してから
 * 本関数を呼び出してください。
 * 
 * 計算量: O(|S|)
 * 
 * @param s 対象の文字列
 * @return std::vector<int> 回文半径の配列
 */
inline std::vector<int> manacher(const std::string& s) {
  int n = s.size();
  std::vector<int> R(n);
  int i = 0, j = 0;
  while (i < n) {
    while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) j++;
    R[i] = j;
    int k = 1;
    while (i - k >= 0 && k + R[i - k] < j) {
      R[i + k] = R[i - k];
      k++;
    }
    i += k;
    j -= k;
  }
  return R;
}
