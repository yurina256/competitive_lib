#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include "../DataStructure/UnionFind.cpp"

using ll = long long;

/**
 * @brief クラスカル法 (最小/最大全域木)
 * 
 * 接続された無向グラフから、すべての頂点を含む木のうち辺の重みの総和が最小/最大となるものを求める。
 * 
 * 計算量: O(E log V)
 * 
 * @param ans 選ばれた辺で構成される無向全域木の隣接リスト (出力先)
 * @param graph 元のグラフ。各頂点に対して {隣接頂点, 辺の重み}
 * @param minimum true の場合は最小全域木、false の場合は最大全域木を求める
 * @return ll 全域木の辺の重みの総和
 */
inline ll kruskal(std::vector<std::vector<std::pair<ll, ll>>>& ans, 
                  const std::vector<std::vector<std::pair<ll, ll>>>& graph, 
                  bool minimum = true) {
  ll n = graph.size();
  ans.assign(n, std::vector<std::pair<ll, ll>>());

  // {cost, {from, to}} の形で辺を抽出
  std::vector<std::pair<ll, std::pair<ll, ll>>> edges;
  for (ll i = 0; i < n; ++i) {
    for (size_t j = 0; j < graph[i].size(); ++j) {
      ll to = graph[i][j].first;
      ll cost = graph[i][j].second;
      edges.push_back({cost, {i, to}});
    }
  }

  // コスト順にソート
  std::sort(edges.begin(), edges.end());
  if (!minimum) {
    std::reverse(edges.begin(), edges.end());
  }

  UnionFind uf(n);
  ll cost_sum = 0;

  for (size_t i = 0; i < edges.size(); ++i) {
    ll cost = edges[i].first;
    ll from = edges[i].second.first;
    ll to = edges[i].second.second;
    if (!uf.same(from, to)) {
      cost_sum += cost;
      uf.unite(from, to);
      ans[from].push_back({to, cost});
      ans[to].push_back({from, cost}); // 無向木として構築
    }
  }

  return cost_sum;
}
