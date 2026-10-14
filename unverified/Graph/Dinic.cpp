#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using ll = long long;

/**
 * @brief 最大流 (Dinic法)
 * 
 * 有向グラフ上の2点 s, t 間の最大流（最小カット）を求めます。
 * 
 * 計算量: O(V^2 E) (実用的には非常に高速。二部マッチングでは O(E√V))
 * 
 * @tparam Flow 流量の型 (デフォルト: ll)
 */
template <typename Flow = ll>
struct Dinic {
  struct Edge {
    ll to;
    Flow cap;
    ll rev;
  };

  ll n;
  std::vector<std::vector<Edge>> g;
  std::vector<ll> level;
  std::vector<ll> iter;

  Dinic(ll n) : n(n), g(n), level(n), iter(n) {}

  /**
   * @brief s から t へ容量 cap の有向辺を追加する (逆辺も追加)
   */
  void add_edge(ll from, ll to, Flow cap) {
    g[from].push_back({to, cap, (ll)g[to].size()});
    g[to].push_back({from, 0, (ll)g[from].size() - 1});
  }

  void bfs(ll s) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<ll> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
      ll v = que.front();
      que.pop();
      for (const auto& edge : g[v]) {
        if (edge.cap > 0 && level[edge.to] < 0) {
          level[edge.to] = level[v] + 1;
          que.push(edge.to);
        }
      }
    }
  }

  Flow dfs(ll v, ll t, Flow f) {
    if (v == t) return f;
    for (ll& i = iter[v]; i < (ll)g[v].size(); i++) {
      auto& edge = g[v][i];
      if (edge.cap > 0 && level[v] < level[edge.to]) {
        Flow d = dfs(edge.to, t, std::min(f, edge.cap));
        if (d > 0) {
          edge.cap -= d;
          g[edge.to][edge.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  /**
   * @brief s から t への最大流を求める
   */
  Flow max_flow(ll s, ll t) {
    Flow flow = 0;
    const Flow INF = std::numeric_limits<Flow>::max() / 2;
    while (true) {
      bfs(s);
      if (level[t] < 0) return flow;
      std::fill(iter.begin(), iter.end(), 0);
      Flow f;
      while ((f = dfs(s, t, INF)) > 0) {
        flow += f;
      }
    }
  }
};
