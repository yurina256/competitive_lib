#pragma once
#include <vector>
#include <queue>

using ll = long long;

/**
 * @brief トポロジカルソート (Topological Sort)
 * 
 * 有向グラフの頂点を、すべての有向辺が左から右へと向かうように並び替えます。
 * サイクルが含まれる（閉路がある）場合は false を返します。
 * 
 * 計算量: O(V + E)
 * 
 * @param g 有向グラフの隣接リスト
 * @param order トポロジカルソートされた結果の頂点番号配列 (出力先)
 * @return bool トポロジカルソートが成功したか (サイクルがなければ true)
 */
inline bool topological_sort(const std::vector<std::vector<ll>>& g, std::vector<ll>& order) {
  ll n = g.size();
  std::vector<ll> indeg(n, 0);
  for (ll i = 0; i < n; i++) {
    for (ll to : g[i]) {
      indeg[to]++;
    }
  }

  std::queue<ll> que;
  for (ll i = 0; i < n; i++) {
    if (indeg[i] == 0) que.push(i);
  }

  order.clear();
  while (!que.empty()) {
    ll v = que.front();
    que.pop();
    order.push_back(v);
    for (ll to : g[v]) {
      indeg[to]--;
      if (indeg[to] == 0) {
        que.push(to);
      }
    }
  }

  return (ll)order.size() == n;
}
