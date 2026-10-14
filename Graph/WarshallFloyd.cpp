#pragma once
#include <vector>
#include <algorithm>

using ll = long long;

constexpr ll WF_INF = 4001001001001001001ll;

/**
 * @brief ワーシャルフロイド法の初期化を行う
 * 
 * @param dist 距離行列 (WF_INFで初期化されている想定)
 * @param graph 隣接リスト表現のグラフ (重み付き)
 * @param prev 経路復元用の前頂点行列
 */
inline void warshall_floyd_init(std::vector<std::vector<ll>>& dist, 
                                 const std::vector<std::vector<std::pair<ll, ll>>>& graph, 
                                 std::vector<std::vector<ll>>& prev) {
  ll n = graph.size();
  for (ll i = 0; i < n; ++i) {
    for (size_t j = 0; j < graph[i].size(); ++j) {
      dist[i][graph[i][j].first] = std::min(dist[i][graph[i][j].first], graph[i][j].second);
    }
  }
  for (ll i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < n; ++j) {
      prev[i][j] = i;
    }
  }
}

/**
 * @brief ワーシャルフロイド法を実行し、全点対最短経路を求める (O(N^3))
 * 
 * @param dist 距離行列
 * @param prev 経路復元用の前頂点行列
 */
inline void warshall_floyd(std::vector<std::vector<ll>>& dist, std::vector<std::vector<ll>>& prev) {
  ll n = dist.size();
  for (ll k = 0; k < n; ++k) {
    for (ll i = 0; i < n; ++i) {
      for (ll j = 0; j < n; ++j) {
        if (dist[i][k] < WF_INF && dist[k][j] < WF_INF) {
          if (dist[i][k] + dist[k][j] < dist[i][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
            prev[i][j] = prev[k][j];
          }
        }
      }
    }
  }
}
