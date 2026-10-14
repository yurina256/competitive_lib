#pragma once
#include <vector>
#include <string>
#include <utility>

using ll = long long;

/**
 * @brief ランレングス圧縮 (Run Length Encoding / RLE)
 * 
 * 文字列中の連続する同一文字を {文字, 連続する個数} のペアの配列に圧縮する。
 * 
 * 計算量: O(N)
 * 
 * @param s 圧縮対象の文字列
 * @return std::vector<std::pair<char, ll>> 圧縮結果
 */
inline std::vector<std::pair<char, ll>> rle(const std::string& s) {
  std::vector<std::pair<char, ll>> ans;
  if (s.empty()) return ans;

  ll n = s.size();
  ll cnt = 1;
  char c = s[0];

  for (ll i = 1; i < n; i++) {
    if (c != s[i]) {
      ans.push_back({c, cnt});
      cnt = 1;
      c = s[i];
    } else {
      cnt++;
    }
  }
  ans.push_back({c, cnt});
  return ans;
}
