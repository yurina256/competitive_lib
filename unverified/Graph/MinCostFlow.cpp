#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <utility>

using ll = long long;

/**
 * @brief 最小費用流 (Primal-Dual法)
 * 
 * ネットワーク上で指定された流量 f を送るのに必要な最小のコストを計算します。
 * ポテンシャル（h）を使用し、Dijkstra法を繰り返すことで高速化しています。
 * 
 * 計算量: O(F E log V) (F: 流量)
 * 
 * @tparam Flow 流量の型 (デフォルト: ll)
 * @tparam Cost コストの型 (デフォルト: ll)
 */
template <typename Flow = ll, typename Cost = ll>
struct MinCostFlow {
  struct Edge {
    ll to;
    Flow cap;
    Cost cost;
    ll rev;
  };

  ll n;
  std::vector<std::vector<Edge>> g;
  std::vector<Cost> h; // ポテンシャル
  std::vector<Cost> dist;
  std::vector<ll> prevv, preve;

  MinCostFlow(ll n) : n(n), g(n), h(n, 0), dist(n), prevv(n), preve(n) {}

  /**
   * @brief s から t へ容量 cap, コスト cost の有向辺を追加する
   */
  void add_edge(ll from, ll to, Flow cap, Cost cost) {
    g[from].push_back({to, cap, cost, (ll)g[to].size()});
    g[to].push_back({from, 0, -cost, (ll)g[from].size() - 1});
  }

  /**
   * @brief s から t へ流量 f を送る際の最小費用を計算する
   * @return Cost 最小費用。流しきれなかった場合は -1 を返す
   */
  Cost min_cost_flow(ll s, ll t, Flow f) {
    Cost res = 0;
    const Cost INF = std::numeric_limits<Cost>::max() / 2;
    std::fill(h.begin(), h.end(), 0);

    while (f > 0) {
      std::priority_queue<std::pair<Cost, ll>, std::vector<std::pair<Cost, ll>>, std::greater<std::pair<Cost, ll>>> que;
      std::fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      que.push({0, s});
      while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (dist[v] < d) continue;
        for (ll i = 0; i < (ll)g[v].size(); i++) {
          auto& edge = g[v][i];
          if (edge.cap > 0 && dist[edge.to] > dist[v] + edge.cost + h[v] - h[edge.to]) {
            dist[edge.to] = dist[v] + edge.cost + h[v] - h[edge.to];
            prevv[edge.to] = v;
            preve[edge.to] = i;
            que.push({dist[edge.to], edge.to});
          }
        }
      }
      if (dist[t] == INF) {
        return -1; // 流せない
      }
      for (ll v = 0; v < n; v++) h[v] += dist[v];

      Flow d = f;
      for (ll v = t; v != s; v = prevv[v]) {
        d = std::min(d, g[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (ll v = t; v != s; v = prevv[v]) {
        auto& edge = g[prevv[v]][preve[v]];
        edge.cap -= d;
        g[v][edge.rev].cap += d;
      }
    }
    return res;
  }
};
