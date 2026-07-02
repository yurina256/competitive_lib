#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

constexpr long long DIJKSTRA_INF = 4001001001001001001ll;

/**
 * @brief ダイクストラ法（重み付きグラフ）(O(M log N))
 * 
 * @param g 隣接リスト表現のグラフ。各頂点に対して {隣接頂点, 辺の重み} のリスト
 * @param s 始点
 * @return std::vector<long long> 各頂点への最短距離。到達不可能な場合は DIJKSTRA_INF
 */
inline std::vector<long long> dijkstra(const std::vector<std::vector<std::pair<long long, long long>>>& g, long long s) {
  std::vector<long long> dt(g.size(), DIJKSTRA_INF);
  std::priority_queue<std::pair<long long, long long>, 
                      std::vector<std::pair<long long, long long>>, 
                      std::greater<std::pair<long long, long long>>> que;
  que.push({0, s});
  dt[s] = 0;
  while (!que.empty()) {
    long long d = que.top().first;
    long long e = que.top().second;
    que.pop();
    if (d > dt[e]) continue;
    for (size_t i = 0; i < g[e].size(); ++i) {
      long long next = g[e][i].first;
      long long cost = g[e][i].second;
      if (d + cost < dt[next]) {
        que.push({d + cost, next});
        dt[next] = d + cost;
      }
    }
  }
  return dt;
}

/**
 * @brief ダイクストラ法（重みなしグラフ）
 * 
 * 辺の重みがすべて1の場合の最短経路。
 * 
 * @param g 隣接リスト表現のグラフ
 * @param s 始点
 * @return std::vector<long long> 各頂点への最短距離
 */
inline std::vector<long long> dijkstra_unweighted(const std::vector<std::vector<long long>>& g, long long s) {
  std::vector<long long> dt(g.size(), DIJKSTRA_INF);
  std::priority_queue<std::pair<long long, long long>, 
                      std::vector<std::pair<long long, long long>>, 
                      std::greater<std::pair<long long, long long>>> que;
  que.push({0, s});
  dt[s] = 0;
  while (!que.empty()) {
    long long d = que.top().first;
    long long e = que.top().second;
    que.pop();
    if (d > dt[e]) continue;
    for (size_t i = 0; i < g[e].size(); ++i) {
      long long next = g[e][i];
      if (d + 1 < dt[next]) {
        que.push({d + 1, next});
        dt[next] = d + 1;
      }
    }
  }
  return dt;
}
