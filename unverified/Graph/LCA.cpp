#pragma once
#include <vector>
#include <utility>

using ll = long long;

/**
 * @brief 最小共通祖先 (Lowest Common Ancestor / LCA)
 * 
 * ダブリングを用いて木における2頂点のLCAを求める構造体。
 * 距離計算や祖先方向への遡りもサポートします。
 * 
 * 計算量: 構築 O(V log V), クエリ O(log V)
 */
struct LCA {
  ll n;
  ll log_h;
  std::vector<ll> depth;
  std::vector<std::vector<ll>> parent;

  LCA() = default;

  /**
   * @brief 隣接リスト表現の無向木からLCAを構築する
   * @param g 隣接リスト
   * @param root 根とする頂点 (デフォルト 0)
   */
  LCA(const std::vector<std::vector<ll>>& g, ll root = 0) {
    n = g.size();
    log_h = 1;
    while ((1LL << log_h) <= n) log_h++;
    depth.assign(n, 0);
    parent.assign(log_h, std::vector<ll>(n, -1));

    auto dfs = [&](auto self, ll v, ll p, ll d) -> void {
      parent[0][v] = p;
      depth[v] = d;
      for (auto next : g[v]) {
        if (next != p) {
          self(self, next, v, d + 1);
        }
      }
    };
    dfs(dfs, root, -1, 0);

    for (ll k = 0; k < log_h - 1; k++) {
      for (ll v = 0; v < n; v++) {
        if (parent[k][v] < 0) {
          parent[k + 1][v] = -1;
        } else {
          parent[k + 1][v] = parent[k][parent[k][v]];
        }
      }
    }
  }

  /**
   * @brief 頂点 u と v のLCA（最小共通祖先）を取得する
   */
  ll query(ll u, ll v) const {
    if (depth[u] > depth[v]) std::swap(u, v);
    for (ll k = 0; k < log_h; k++) {
      if ((depth[v] - depth[u]) >> k & 1) {
        v = parent[k][v];
      }
    }
    if (u == v) return u;
    for (ll k = log_h - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }

  /**
   * @brief 頂点 u と v の間の辺数 (距離) を取得する
   */
  ll distance(ll u, ll v) const {
    return depth[u] + depth[v] - 2 * depth[query(u, v)];
  }
};
