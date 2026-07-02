#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

/**
 * @brief 木の直径を求める (O(N))
 * 
 * 最も遠い2頂点間の距離を求める。BFSを2回行うことで直径を求める。
 */

/**
 * @brief 重み付き無向木の直径を求める
 * 
 * @param g 隣接リスト表現のグラフ。各要素は {隣接頂点, 辺の重み}
 * @return long long 直径（最遠パスの重みの総和）
 */
inline long long tree_diameter_weighted(const std::vector<std::vector<std::pair<long long, long long>>>& g) {
  long long n = g.size();
  if (n == 0) return 0;

  auto bfs = [&](long long start) -> std::pair<long long, long long> {
    std::vector<long long> dist(n, -1);
    std::queue<long long> que;
    que.push(start);
    dist[start] = 0;
    long long max_d = 0;
    long long max_v = start;
    while (!que.empty()) {
      long long u = que.front();
      que.pop();
      for (const auto& edge : g[u]) {
        long long v = edge.first;
        long long w = edge.second;
        if (dist[v] == -1) {
          dist[v] = dist[u] + w;
          que.push(v);
          if (dist[v] > max_d) {
            max_d = dist[v];
            max_v = v;
          }
        }
      }
    }
    return {max_v, max_d};
  };

  // 任意の頂点（0）から最も遠い頂点 u を見つける
  auto [u, _] = bfs(0);
  // u から最も遠い頂点 v を見つける。その距離が直径
  auto [v, diameter] = bfs(u);
  return diameter;
}

/**
 * @brief 重みなし無向木の直径を求める
 * 
 * @param g 隣接リスト表現のグラフ
 * @return long long 直径（最遠パスの辺の数）
 */
inline long long tree_diameter(const std::vector<std::vector<long long>>& g) {
  long long n = g.size();
  if (n == 0) return 0;

  auto bfs = [&](long long start) -> std::pair<long long, long long> {
    std::vector<long long> dist(n, -1);
    std::queue<long long> que;
    que.push(start);
    dist[start] = 0;
    long long max_d = 0;
    long long max_v = start;
    while (!que.empty()) {
      long long u = que.front();
      que.pop();
      for (long long v : g[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          que.push(v);
          if (dist[v] > max_d) {
            max_d = dist[v];
            max_v = v;
          }
        }
      }
    }
    return {max_v, max_d};
  };

  // 任意の頂点（0）から最も遠い頂点 u を見つける
  auto [u, _] = bfs(0);
  // u から最も遠い頂点 v を見つける。その距離が直径
  auto [v, diameter] = bfs(u);
  return diameter;
}
