#pragma once
#include <vector>

using ll = long long;

/**
 * @brief 区別しない集合に分ける全列挙
 * 
 * N 個の要素を区別しないグループに分割するすべての方法 (Bell 数) を辞書順で列挙する。
 * 各グループには 0 から始まるインデックスが割り振られます。
 * 例: N=3 の場合、以下の5通りが出力されます:
 * {0, 0, 0} (aaa), {0, 0, 1} (aab), {0, 1, 0} (aba), {0, 1, 1} (abb), {0, 1, 2} (abc)
 * 
 * 計算量: O(Bell(N) * N) (N=10 のとき Bell(10) = 115,975 通り)
 * 
 * @param n 要素数
 * @return std::vector<std::vector<ll>> 列挙されたグループ割り当てのリスト
 */
inline std::vector<std::vector<ll>> enumerate_set_partitions(ll n) {
  std::vector<std::vector<ll>> res;
  std::vector<ll> current;

  auto dfs = [&](auto self, ll k) -> void {
    if ((ll)current.size() == n) {
      res.push_back(current);
      return;
    }
    for (ll i = 0; i <= k; i++) {
      current.push_back(i);
      self(self, (i == k) ? k + 1 : k);
      current.pop_back();
    }
  };

  dfs(dfs, 0);
  return res;
}
