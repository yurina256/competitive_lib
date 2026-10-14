#pragma once
#include <algorithm>
#include <vector>

/**
 * @brief Link-Cut Tree
 *
 * 動的な森に対する辺の追加・削除、連結判定、根変更、パス上のモノイド集約を
 * O(log N) 償却で処理するデータ構造。
 *
 * T は集約する値の型、op は二項演算、e は単位元を返す関数。
 * op は結合的である必要がある。非可換な演算にも対応するため、正方向と逆方向
 * の集約値をそれぞれ保持する。
 */
template <class T, T (*op)(T, T), T (*e)()>
struct LinkCutTree {
  struct Node {
    int child[2] = {-1, -1};
    int parent = -1;
    T value = e();
    T aggregate = e();
    T reverse_aggregate = e();
    bool reversed = false;
  };

  std::vector<Node> nodes;

  /**
   * @brief 頂点数 N で初期化する (O(N))
   *
   * 初期値はすべて e() です。
   */
  explicit LinkCutTree(int n) : nodes(n) {}

  /**
   * @brief 頂点 v の値を指定して初期化する (O(N))
   */
  explicit LinkCutTree(const std::vector<T>& values) : nodes(values.size()) {
    for (int v = 0; v < static_cast<int>(values.size()); ++v) {
      nodes[v].value = values[v];
      pull(v);
    }
  }

  /**
   * @brief 頂点 v の値を変更する (O(log N) 償却)
   */
  void set_value(int v, const T& value) {
    access(v);
    nodes[v].value = value;
    pull(v);
  }

  /**
   * @brief 頂点 v の値を取得する (O(log N) 償却)
   */
  T get_value(int v) {
    access(v);
    return nodes[v].value;
  }

  /**
   * @brief u と v が同じ木に属するか判定する (O(log N) 償却)
   */
  bool connected(int u, int v) {
    if (u == v) return true;
    return find_root(u) == find_root(v);
  }

  /**
   * @brief u を v の子として辺を追加する (O(log N) 償却)
   *
   * すでに連結な頂点同士を link することはできません。
   * @return 辺が追加された場合 true
   */
  bool link(int u, int v) {
    make_root(u);
    if (find_root(v) == u) return false;
    nodes[u].parent = v;
    return true;
  }

  /**
   * @brief u と v の間の辺を削除する (O(log N) 償却)
   *
   * u と v が直接接続されていない場合は何もしません。
   * @return 辺が削除された場合 true
   */
  bool cut(int u, int v) {
    make_root(u);
    access(v);
    if (nodes[v].child[0] != u || nodes[u].child[1] != -1) return false;
    nodes[v].child[0] = -1;
    nodes[u].parent = -1;
    pull(v);
    return true;
  }

  /**
   * @brief u を木の根にする (O(log N) 償却)
   */
  void make_root(int u) {
    access(u);
    toggle_reverse(u);
  }

  /**
   * @brief u が属する木の根を返す (O(log N) 償却)
   */
  int find_root(int u) {
    access(u);
    while (true) {
      push(u);
      if (nodes[u].child[0] == -1) break;
      u = nodes[u].child[0];
    }
    splay(u);
    return u;
  }

  /**
   * @brief u から v へのパス上の頂点値を順に集約する (O(log N) 償却)
   *
   * パスの向きは u -> v です。u と v が非連結の場合の結果は未定義です。
   */
  T path_query(int u, int v) {
    make_root(u);
    access(v);
    return nodes[v].aggregate;
  }

 private:
  bool is_splay_root(int v) const {
    int p = nodes[v].parent;
    return p == -1 || (nodes[p].child[0] != v && nodes[p].child[1] != v);
  }

  void toggle_reverse(int v) {
    if (v == -1) return;
    std::swap(nodes[v].child[0], nodes[v].child[1]);
    std::swap(nodes[v].aggregate, nodes[v].reverse_aggregate);
    nodes[v].reversed = !nodes[v].reversed;
  }

  void push(int v) {
    if (v == -1 || !nodes[v].reversed) return;
    toggle_reverse(nodes[v].child[0]);
    toggle_reverse(nodes[v].child[1]);
    nodes[v].reversed = false;
  }

  void pull(int v) {
    int left = nodes[v].child[0];
    int right = nodes[v].child[1];
    T left_aggregate = left == -1 ? e() : nodes[left].aggregate;
    T right_aggregate = right == -1 ? e() : nodes[right].aggregate;
    T left_reverse = left == -1 ? e() : nodes[left].reverse_aggregate;
    T right_reverse = right == -1 ? e() : nodes[right].reverse_aggregate;
    nodes[v].aggregate = op(op(left_aggregate, nodes[v].value), right_aggregate);
    nodes[v].reverse_aggregate = op(op(right_reverse, nodes[v].value), left_reverse);
  }

  void push_path(int v) {
    if (!is_splay_root(v)) push_path(nodes[v].parent);
    push(v);
  }

  void rotate(int v) {
    int p = nodes[v].parent;
    int g = nodes[p].parent;
    int direction = nodes[p].child[1] == v;
    int middle = nodes[v].child[direction ^ 1];

    if (!is_splay_root(p)) nodes[g].child[nodes[g].child[1] == p] = v;
    nodes[v].parent = g;
    nodes[v].child[direction ^ 1] = p;
    nodes[p].parent = v;
    nodes[p].child[direction] = middle;
    if (middle != -1) nodes[middle].parent = p;
    pull(p);
    pull(v);
  }

  void splay(int v) {
    push_path(v);
    while (!is_splay_root(v)) {
      int p = nodes[v].parent;
      int g = nodes[p].parent;
      if (!is_splay_root(p)) {
        bool zig_zig = (nodes[p].child[0] == v) == (nodes[g].child[0] == p);
        rotate(zig_zig ? p : v);
      }
      rotate(v);
    }
  }

  void access(int v) {
    int last = -1;
    for (int x = v; x != -1; x = nodes[x].parent) {
      splay(x);
      nodes[x].child[1] = last;
      pull(x);
      last = x;
    }
    splay(v);
  }
};
