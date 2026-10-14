#pragma once
#include <vector>
#include <algorithm>
#include <utility>

using ll = long long;

/**
 * @brief Heavy-Light Decomposition (Heavy-Light 分解 / HLD)
 *
 * 木をいくつかのパスに分解し、セグメント木やフェニック木などの1次元データ構造と
 * 組み合わせることで、木上のパスクエリや部分木クエリを高速に処理する構造体。
 *
 * 計算量:
 *   - 構築 (build): O(N)
 *   - LCA (lca / パス分解): O(log N)
 *   - パス分解 (process_path_vertex / process_path_edge): 分解された区間の数は O(log N) 個
 *
 * 空間計算量: O(N)
 * <: AI Gen :>
 * @date 2026.6.22 23:55
 */
struct HeavyLightDecomposition {
  ll n;                            // 頂点数
  std::vector<std::vector<ll>> g;  // 隣接リスト
  std::vector<ll> sz;              // 部分木サイズ
  std::vector<ll> in;              // 行きがけ順インデックス（1次元配列上の位置）
  std::vector<ll> out;             // 帰りがけ順インデックス（部分木の終了）
  std::vector<ll> head;            // 頂点 v が属する重パスの先頭頂点
  std::vector<ll> parent;          // 親頂点
  std::vector<ll> depth;           // 根からの深さ
  ll time;                         // 行きがけ順カウント用

  /**
   * @brief コンストラクタ
   * @param n 頂点数
   */
  HeavyLightDecomposition(ll n) : n(n), g(n), sz(n), in(n), out(n), head(n), parent(n), depth(n), time(0) {}

  /**
   * @brief 無向辺の追加 (O(1))
   * @param u 頂点番号1 (0-indexed)
   * @param v 頂点番号2 (0-indexed)
   */
  void add_edge(ll u, ll v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  /**
   * @brief HLDの構築を行う (O(N))
   * @param root 根とする頂点の番号 (デフォルト: 0)
   */
  void build(ll root = 0) {
    time = 0;
    dfs_sz(root, -1, 0);
    dfs_hld(root, -1, root);
  }

  /**
   * @brief 頂点属性パスクエリ用: 頂点 u と v の間のパスをいくつかの半開区間 [l, r) に分解し、関数 f に渡す (O(log N))
   *
   * @tparam F 処理用関数オブジェクト (引数は (ll l, ll r))
   * @param u 頂点番号
   * @param v 頂点番号
   * @param f 各区間に対して実行する関数 (引数は半開区間 [l, r))
   */
  template <typename F>
  void process_path_vertex(ll u, ll v, F f) {
    while (head[u] != head[v]) {
      if (depth[head[u]] > depth[head[v]]) std::swap(u, v);
      f(in[head[v]], in[v] + 1);
      v = parent[head[v]];
    }
    if (depth[u] > depth[v]) std::swap(u, v);
    f(in[u], in[v] + 1);
  }

  /**
   * @brief 辺属性パスクエリ用: 頂点 u と v の間のパス（辺）をいくつかの半開区間 [l, r) に分解し、関数 f に渡す (O(log N))
   *
   * 頂点属性クエリと異なり、LCA (最深共通祖先) に対応する頂点位置は辺属性に含まれないため除外します。
   *
   * @tparam F 処理用関数オブジェクト (引数は (ll l, ll r))
   * @param u 頂点番号
   * @param v 頂点番号
   * @param f 各区間に対して実行する関数 (引数は半開区間 [l, r))
   */
  template <typename F>
  void process_path_edge(ll u, ll v, F f) {
    while (head[u] != head[v]) {
      if (depth[head[u]] > depth[head[v]]) std::swap(u, v);
      f(in[head[v]], in[v] + 1);
      v = parent[head[v]];
    }
    if (depth[u] > depth[v]) std::swap(u, v);
    // LCA(uとvの浅い方)に対応するインデックス(in[u])を+1して除外
    if (in[u] < in[v]) {
      f(in[u] + 1, in[v] + 1);
    }
  }

  /**
   * @brief 有向パスクエリ（非可換演算）用: 頂点 u から v への有向パスを、「上り」と「下り」に分解して関数に渡す (O(log N))
   *
   * 行列積や一次関数の合成など、演算の順序が重要な（非可換な）パスクエリを処理する際に使用します。
   * パスは u -> LCA (上り) と、LCA -> v (下り) に分解されます。
   *
   * @tparam F1 上りパス処理用関数オブジェクト (引数は (ll l, ll r))
   * @tparam F2 下りパス処理用関数オブジェクト (引数は (ll l, ll r))
   * @param u 始点
   * @param v 終点
   * @param f_up 上りパスに対する処理 (始点側からLCA側へ向かう区間)
   * @param f_down 下りパスに対する処理 (LCA側から終点側へ向かう区間)
   */
  template <typename F1, typename F2>
  void process_directed_path(ll u, ll v, F1 f_up, F2 f_down) {
    std::vector<std::pair<ll, ll>> up_paths;
    std::vector<std::pair<ll, ll>> down_paths;
    while (head[u] != head[v]) {
      if (depth[head[u]] > depth[head[v]]) {
        up_paths.push_back({in[head[u]], in[u] + 1});
        u = parent[head[u]];
      } else {
        down_paths.push_back({in[head[v]], in[v] + 1});
        v = parent[head[v]];
      }
    }
    if (depth[u] > depth[v]) {
      up_paths.push_back({in[v], in[u] + 1});
    } else {
      down_paths.push_back({in[u], in[v] + 1});
    }

    // 上りパス (u -> LCA): 深い方から順次処理
    for (const auto& path : up_paths) {
      f_up(path.first, path.second);
    }
    // 下りパス (LCA -> v): 浅い方から順次処理 (down_pathsは深い順に入っているので逆順にする)
    std::reverse(down_paths.begin(), down_paths.end());
    for (const auto& path : down_paths) {
      f_down(path.first, path.second);
    }
  }

  /**
   * @brief 部分木クエリ用: 頂点 v の部分木全体に対応する1次元配列上の半開区間 [l, r) を取得する (O(1))
   *
   * @param v 頂点番号
   * @return std::pair<ll, ll> 部分木に対応する半開区間 {l, r}
   */
  std::pair<ll, ll> get_subtree(ll v) {
    return {in[v], out[v]};
  }

  /**
   * @brief 頂点 u と v の最深共通祖先 (LCA) を取得する (O(log N))
   *
   * @param u 頂点番号
   * @param v 頂点番号
   * @return ll LCA の頂点番号
   */
  ll lca(ll u, ll v) {
    while (head[u] != head[v]) {
      if (depth[head[u]] > depth[head[v]]) std::swap(u, v);
      v = parent[head[v]];
    }
    return depth[u] < depth[v] ? u : v;
  }

  /**
   * @brief 頂点 u と v の距離（パス上の辺の数）を取得する (O(log N))
   *
   * @param u 頂点番号
   * @param v 頂点番号
   * @return ll 距離
   */
  ll distance(ll u, ll v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
  }

  /**
   * @brief 辺 (u, v) において、深さが深い方の頂点（子）を取得する (O(1))
   * 
   * @param u 頂点番号1
   * @param v 頂点番号2
   * @return ll 子（深い方）の頂点番号
   */
  ll get_child(ll u, ll v) const {
    return depth[u] > depth[v] ? u : v;
  }

 private:
  void dfs_sz(ll v, ll p, ll d) {
    parent[v] = p;
    depth[v] = d;
    sz[v] = 1;
    if (!g[v].empty() && g[v][0] == p) std::swap(g[v][0], g[v].back());
    for (ll& to : g[v]) {
      if (to == p) continue;
      dfs_sz(to, v, d + 1);
      sz[v] += sz[to];
      if (sz[to] > sz[g[v][0]]) std::swap(to, g[v][0]);  // 重い辺を先頭に持ってくる
    }
  }

  void dfs_hld(ll v, ll p, ll h) {
    head[v] = h;
    in[v] = time++;
    if (!g[v].empty() && g[v][0] != p) {
      dfs_hld(g[v][0], v, h);  // 重い子ノードは同じ head を引き継ぐ
    }
    for (ll to : g[v]) {
      if (to == p || to == g[v][0]) continue;
      dfs_hld(to, v, to);  // 軽い子ノードは自分が新しい head になる
    }
    out[v] = time;
  }
};
