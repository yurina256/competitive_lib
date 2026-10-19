#pragma once
#include <vector>
#include <utility>
#include <algorithm>

constexpr long long BF_INF = 4001001001001001001ll;

/**
 * @brief ベルマンフォード法 (O(NM))
 * 
 * 単一始点最短経路を負辺ありのグラフで求める。
 * 始点 s から到達可能な負閉路が存在し、そこからさらに到達可能な頂点 v については
 * dt[v] = -BF_INF となる（特定頂点 t が負閉路の影響を受けるかの判定にも対応）。
 * 
 * @param g 隣接リスト表現のグラフ。各頂点に対して {隣接頂点, 辺の重み} のリスト (dijkstra と同じ形式)
 * @param s 始点
 * @return std::vector<long long> 各頂点への最短距離
 *         - dt[v] == BF_INF  : 始点 s から到達不可能
 *         - dt[v] == -BF_INF : 負閉路を経由して到達可能（距離を無限に小さくできる）
 *         - それ以外         : 最短距離
 */
inline std::vector<long long> bellman_ford(const std::vector<std::vector<std::pair<long long, long long>>>& g, long long s) {
  long long n = g.size();
  std::vector<long long> dt(n, BF_INF);
  dt[s] = 0;

  // 1. 最短距離の更新 (最大 n - 1 回)
  for (long long iter = 0; iter < n - 1; ++iter) {
    bool updated = false;
    for (long long u = 0; u < n; ++u) {
      if (dt[u] == BF_INF) continue;
      for (const auto& edge : g[u]) {
        long long v = edge.first;
        long long cost = edge.second;
        if (dt[u] + cost < dt[v]) {
          dt[v] = dt[u] + cost;
          updated = true;
        }
      }
    }
    if (!updated) return dt;  // 更新がなくなれば負閉路なしで早期終了
  }

  // 2. 負閉路の検出と影響範囲の伝播 (n 回回すことで負閉路から到達可能な全頂点を -BF_INF にする)
  for (long long iter = 0; iter < n; ++iter) {
    for (long long u = 0; u < n; ++u) {
      if (dt[u] == BF_INF) continue;
      for (const auto& edge : g[u]) {
        long long v = edge.first;
        long long cost = edge.second;
        if (dt[u] == -BF_INF) {
          dt[v] = -BF_INF;
        } else if (dt[u] + cost < dt[v]) {
          dt[v] = -BF_INF;
        }
      }
    }
  }

  return dt;
}

/**
 * @brief グラフ全体（非連結成分を含む）に負閉路が存在するかを判定する (O(NM))
 * 
 * @param g 隣接リスト表現のグラフ。各頂点に対して {隣接頂点, 辺の重み} のリスト
 * @return true グラフ内のどこかに負閉路が存在する場合
 * @return false 負閉路が存在しない場合
 */
inline bool has_negative_cycle(const std::vector<std::vector<std::pair<long long, long long>>>& g) {
  long long n = g.size();
  std::vector<long long> dt(n, 0);  // 全頂点を距離0で初期化（全頂点に超始点からコスト0の辺を張るのと同値）
  for (long long iter = 0; iter < n; ++iter) {
    bool updated = false;
    for (long long u = 0; u < n; ++u) {
      for (const auto& edge : g[u]) {
        long long v = edge.first;
        long long cost = edge.second;
        if (dt[u] + cost < dt[v]) {
          dt[v] = dt[u] + cost;
          updated = true;
          if (iter == n - 1) return true;  // n回目にも更新があれば負閉路が存在
        }
      }
    }
    if (!updated) return false;
  }
  return false;
}
