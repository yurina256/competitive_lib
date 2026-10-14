#pragma once
#include <vector>
#include <algorithm>

using ll = long long;

/**
 * @brief 強連結成分分解 (SCC / Strongly Connected Components)
 *
 * 有向グラフを強連結成分 (互いに行き来可能な頂点の集合) に分解します。
 * トポロジカルソートされた縮約されたグラフを得ることができます。
 *
 * 計算量: O(V + E)
 */
struct SCC {
  ll n;
  std::vector<std::vector<ll>> g, rg;
  std::vector<ll> comp;
  std::vector<std::vector<ll>> group;

  /**
   * @brief コンストラクタ
   * @param n 頂点数
   */
  SCC(ll n) : n(n), g(n), rg(n), comp(n, -1) {}

  /**
   * @brief 有向辺を追加する
   */
  void add_edge(ll from, ll to) {
    g[from].push_back(to);
    rg[to].push_back(from);
  }

  /**
   * @brief SCC分解を実行する
   */
  void build() {
    std::vector<ll> order;
    std::vector<bool> used(n, false);
    auto dfs = [&](auto self, ll v) -> void {
      used[v] = true;
      for (ll to : g[v]) {
        if (!used[to]) self(self, to);
      }
      order.push_back(v);
    };

    for (ll i = 0; i < n; i++) {
      if (!used[i]) dfs(dfs, i);
    }
    std::reverse(order.begin(), order.end());

    ll k = 0;
    std::vector<ll> current_group;
    auto rdfs = [&](auto self, ll v) -> void {
      comp[v] = k;
      current_group.push_back(v);
      for (ll to : rg[v]) {
        if (comp[to] == -1) self(self, to);
      }
    };

    for (ll v : order) {
      if (comp[v] == -1) {
        current_group.clear();
        rdfs(rdfs, v);
        group.push_back(current_group);
        k++;
      }
    }
  }

  /**
   * @brief 頂点 v が属する強連結成分のIDを取得する (縮約後のトポロジカル順)
   */
  ll operator[](ll v) const { return comp[v]; }

  /**
   * @brief 縮約後のグラフ(DAG)を構築して返す
   * @return 縮約後のグラフの隣接リスト
   */
  std::vector<std::vector<ll>> get_dag() {
    ll k = group.size();  // 強連結成分の数
    std::vector<std::vector<ll>> dag(k);

    // 全ての元の辺を確認する
    for (ll u = 0; u < n; u++) {
      for (ll v : g[u]) {
        ll comp_u = comp[u];
        ll comp_v = comp[v];
        // 異なる強連結成分に向かう辺のみを追加
        if (comp_u != comp_v) {
          dag[comp_u].push_back(comp_v);
        }
      }
    }

    // (オプション) 多重辺を削除する
    for (ll i = 0; i < k; i++) {
      std::sort(dag[i].begin(), dag[i].end());
      dag[i].erase(std::unique(dag[i].begin(), dag[i].end()), dag[i].end());
    }

    return dag;
  }
};
