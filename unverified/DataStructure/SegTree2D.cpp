#pragma once
#include <vector>
#include <functional>

using ll = long long;

/**
 * @brief 2次元セグメント木 (2D Segment Tree / Point Update Range Query)
 * 
 * 2次元グリッド上の 1点更新 (Point Update)・矩形区間クエリ (Range Query) を行います。
 * 
 * 計算量: 更新 O(log H * log W), クエリ O(log H * log W)
 * 
 * @tparam T モノイドの型
 */
template <typename T>
struct SegTree2D {
  using F = std::function<T(T, T)>;
  ll h, w;
  T ti;
  F f;
  std::vector<std::vector<T>> tree;

  /**
   * @brief コンストラクタ
   * @param h_ グリッドの行数
   * @param w_ グリッドの列数
   * @param ti モノイドの単位元
   * @param f 結合法則を満たす二項演算
   */
  SegTree2D(ll h_, ll w_, T ti, F f) : ti(ti), f(f) {
    h = 1; while (h < h_) h <<= 1;
    w = 1; while (w < w_) w <<= 1;
    tree.assign(2 * h, std::vector<T>(2 * w, ti));
  }

  /**
   * @brief セル (r, c) の値を val に更新する (0-indexed)
   */
  void update(ll r, ll c, T val) {
    r += h;
    c += w;
    tree[r][c] = val;
    for (ll j = c >> 1; j > 0; j >>= 1) {
      tree[r][j] = f(tree[r][2 * j], tree[r][2 * j + 1]);
    }
    for (ll i = r >> 1; i > 0; i >>= 1) {
      tree[i][c] = f(tree[2 * i][c], tree[2 * i + 1][c]);
      for (ll j = c >> 1; j > 0; j >>= 1) {
        tree[i][j] = f(tree[i][2 * j], tree[i][2 * j + 1]);
      }
    }
  }

  // [c1, c2) に対するクエリを特定の行に対して一次元的に行うヘルパー
  T query_w(ll r_idx, ll c1, ll c2) const {
    T res = ti;
    for (ll l = c1 + w, r = c2 + w; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = f(res, tree[r_idx][l++]);
      if (r & 1) res = f(res, tree[r_idx][--r]);
    }
    return res;
  }

  /**
   * @brief 矩形領域 [r1, r2) x [c1, c2) に対するクエリを処理する (0-indexed, 半開区間)
   */
  T query(ll r1, ll c1, ll r2, ll c2) const {
    T res = ti;
    for (ll l = r1 + h, r = r2 + h; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = f(res, query_w(l++, c1, c2));
      if (r & 1) res = f(res, query_w(--r, c1, c2));
    }
    return res;
  }
};
