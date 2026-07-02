#pragma once
#include <vector>
#include <algorithm>

/**
 * @brief 強連結成分分解 (SCC / Strongly Connected Components)
 * 
 * 有向グラフを強連結成分 (互いに行き来可能な頂点の集合) に分解します。
 * トポロジカルソートされた縮約されたグラフを得ることができます。
 * 
 * 計算量: O(V + E)
 */
struct SCC {
  int n;
  std::vector<std::vector<int>> g, rg;
  std::vector<int> comp;
  std::vector<std::vector<int>> group;

  /**
   * @brief コンストラクタ
   * @param n 頂点数
   */
  SCC(int n) : n(n), g(n), rg(n), comp(n, -1) {}

  /**
   * @brief 有向辺を追加する
   */
  void add_edge(int from, int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
  }

  /**
   * @brief SCC分解を実行する
   */
  void build() {
    std::vector<int> order;
    std::vector<bool> used(n, false);
    auto dfs = [&](auto self, int v) -> void {
      used[v] = true;
      for (int to : g[v]) {
        if (!used[to]) self(self, to);
      }
      order.push_back(v);
    };

    for (int i = 0; i < n; i++) {
      if (!used[i]) dfs(dfs, i);
    }
    std::reverse(order.begin(), order.end());

    int k = 0;
    std::vector<int> current_group;
    auto rdfs = [&](auto self, int v) -> void {
      comp[v] = k;
      current_group.push_back(v);
      for (int to : rg[v]) {
        if (comp[to] == -1) self(self, to);
      }
    };

    for (int v : order) {
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
  int operator[](int v) const { return comp[v]; }
};
