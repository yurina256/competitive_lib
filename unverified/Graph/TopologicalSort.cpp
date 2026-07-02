#pragma once
#include <vector>
#include <queue>

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
inline bool topological_sort(const std::vector<std::vector<int>>& g, std::vector<int>& order) {
  int n = g.size();
  std::vector<int> indeg(n, 0);
  for (int i = 0; i < n; i++) {
    for (int to : g[i]) {
      indeg[to]++;
    }
  }

  std::queue<int> que;
  for (int i = 0; i < n; i++) {
    if (indeg[i] == 0) que.push(i);
  }

  order.clear();
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    order.push_back(v);
    for (int to : g[v]) {
      indeg[to]--;
      if (indeg[to] == 0) {
        que.push(to);
      }
    }
  }

  return (int)order.size() == n;
}
