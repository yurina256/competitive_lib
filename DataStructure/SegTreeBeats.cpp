#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

using ll = long long;

/**
 * @brief Segment Tree Beats! (区間chmin・区間chmax・区間加算・区間更新・区間和/最大/最小)
 *
 * 区間 chmin / chmax / 加算 / 更新 と、区間総和 / 最大値 / 最小値 の取得を処理するデータ構造。
 *
 * 計算量:
 *   - 構築: O(N)
 *   - 区間 chmin / chmax / 加算 / 更新: ならし O(log^2 N) (chmin/chmax を含まない場合は O(log N))
 *   - 区間クエリ (総和 / 最大値 / 最小値): O(log N)
 */
struct SegTreeBeats {
  static constexpr ll INF = std::numeric_limits<ll>::max() / 4;

  struct Node {
    ll sum = 0;
    ll max1 = -INF, max2 = -INF, max_c = 0;
    ll min1 = INF, min2 = INF, min_c = 0;
    ll add = 0;
    ll len = 0;
  };

  int n = 0, sz = 1, log = 0;
  std::vector<Node> tree;

  SegTreeBeats() = default;

  /**
   * @brief 要素数 n (初期値 0) で構築する (O(N))
   */
  explicit SegTreeBeats(int n) : SegTreeBeats(std::vector<ll>(n, 0)) {}

  /**
   * @brief 配列 v で構築する (O(N))
   */
  explicit SegTreeBeats(const std::vector<ll>& v) : n(static_cast<int>(v.size())) {
    sz = 1;
    log = 0;
    while (sz < std::max(1, n)) {
      sz <<= 1;
      ++log;
    }
    tree.resize(2 * sz);
    for (int i = 0; i < n; ++i) {
      tree[sz + i].sum = v[i];
      tree[sz + i].max1 = v[i];
      tree[sz + i].max2 = -INF;
      tree[sz + i].max_c = 1;
      tree[sz + i].min1 = v[i];
      tree[sz + i].min2 = INF;
      tree[sz + i].min_c = 1;
      tree[sz + i].len = 1;
    }
    for (int i = sz - 1; i >= 1; --i) {
      pull(i);
    }
  }

  /**
   * @brief 区間 [l, r) の各要素 a[i] を min(a[i], x) に更新する
   */
  void range_chmin(int l, int r, ll x) {
    assert(0 <= l && l <= r && r <= n);
    range_chmin(l, r, x, 1, 0, sz);
  }

  /**
   * @brief 区間 [l, r) の各要素 a[i] を max(a[i], x) に更新する
   */
  void range_chmax(int l, int r, ll x) {
    assert(0 <= l && l <= r && r <= n);
    range_chmax(l, r, x, 1, 0, sz);
  }

  /**
   * @brief 区間 [l, r) の各要素 a[i] に x を加算する
   */
  void range_add(int l, int r, ll x) {
    assert(0 <= l && l <= r && r <= n);
    range_add(l, r, x, 1, 0, sz);
  }

  /**
   * @brief 区間 [l, r) の各要素 a[i] を x に更新する
   */
  void range_update(int l, int r, ll x) {
    assert(0 <= l && l <= r && r <= n);
    range_update(l, r, x, 1, 0, sz);
  }

  /**
   * @brief 1点 p の値を x に更新する
   */
  void set(int p, ll x) {
    assert(0 <= p && p < n);
    range_update(p, p + 1, x);
  }

  /**
   * @brief 1点 p の値を取得する
   */
  ll get(int p) {
    assert(0 <= p && p < n);
    return prod_sum(p, p + 1);
  }

  /**
   * @brief 区間 [l, r) の総和を取得する
   */
  ll prod_sum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return query_sum(l, r, 1, 0, sz);
  }

  /**
   * @brief 区間 [l, r) の最大値を取得する (空区間は -INF)
   */
  ll prod_max(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return query_max(l, r, 1, 0, sz);
  }

  /**
   * @brief 区間 [l, r) の最小値を取得する (空区間は INF)
   */
  ll prod_min(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return query_min(l, r, 1, 0, sz);
  }

 private:
  void pull(int k) {
    const Node& l = tree[2 * k];
    const Node& r = tree[2 * k + 1];
    Node& res = tree[k];
    res.sum = l.sum + r.sum;
    res.len = l.len + r.len;
    res.add = 0;

    if (l.max1 > r.max1) {
      res.max1 = l.max1;
      res.max2 = std::max(l.max2, r.max1);
      res.max_c = l.max_c;
    } else if (l.max1 < r.max1) {
      res.max1 = r.max1;
      res.max2 = std::max(l.max1, r.max2);
      res.max_c = r.max_c;
    } else {
      res.max1 = l.max1;
      res.max2 = std::max(l.max2, r.max2);
      res.max_c = l.max_c + r.max_c;
    }

    if (l.min1 < r.min1) {
      res.min1 = l.min1;
      res.min2 = std::min(l.min2, r.min1);
      res.min_c = l.min_c;
    } else if (l.min1 > r.min1) {
      res.min1 = r.min1;
      res.min2 = std::min(l.min1, r.min2);
      res.min_c = r.min_c;
    } else {
      res.min1 = l.min1;
      res.min2 = std::min(l.min2, r.min2);
      res.min_c = l.min_c + r.min_c;
    }
  }

  void apply_add(int k, ll x) {
    Node& node = tree[k];
    if (node.len == 0) return;
    node.sum += x * node.len;
    node.max1 += x;
    if (node.max2 != -INF) node.max2 += x;
    node.min1 += x;
    if (node.min2 != INF) node.min2 += x;
    node.add += x;
  }

  void apply_chmin(int k, ll x) {
    Node& node = tree[k];
    if (node.len == 0 || node.max1 <= x) return;
    node.sum += (x - node.max1) * node.max_c;
    if (node.max1 == node.min1) {
      node.max1 = node.min1 = x;
    } else if (node.max1 == node.min2) {
      node.max1 = node.min2 = x;
    } else {
      node.max1 = x;
    }
  }

  void apply_chmax(int k, ll x) {
    Node& node = tree[k];
    if (node.len == 0 || node.min1 >= x) return;
    node.sum += (x - node.min1) * node.min_c;
    if (node.min1 == node.max1) {
      node.min1 = node.max1 = x;
    } else if (node.min1 == node.max2) {
      node.min1 = node.max2 = x;
    } else {
      node.min1 = x;
    }
  }

  void push(int k) {
    Node& node = tree[k];
    if (node.len == 0) return;
    int l = 2 * k, r = 2 * k + 1;
    if (node.add != 0) {
      apply_add(l, node.add);
      apply_add(r, node.add);
      node.add = 0;
    }
    if (tree[l].max1 > node.max1) apply_chmin(l, node.max1);
    if (tree[r].max1 > node.max1) apply_chmin(r, node.max1);
    if (tree[l].min1 < node.min1) apply_chmax(l, node.min1);
    if (tree[r].min1 < node.min1) apply_chmax(r, node.min1);
  }

  void range_chmin(int ql, int qr, ll x, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0 || tree[k].max1 <= x) return;
    if (ql <= l && r <= qr && tree[k].max2 < x) {
      apply_chmin(k, x);
      return;
    }
    push(k);
    int mid = (l + r) >> 1;
    range_chmin(ql, qr, x, 2 * k, l, mid);
    range_chmin(ql, qr, x, 2 * k + 1, mid, r);
    pull(k);
  }

  void range_chmax(int ql, int qr, ll x, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0 || tree[k].min1 >= x) return;
    if (ql <= l && r <= qr && tree[k].min2 > x) {
      apply_chmax(k, x);
      return;
    }
    push(k);
    int mid = (l + r) >> 1;
    range_chmax(ql, qr, x, 2 * k, l, mid);
    range_chmax(ql, qr, x, 2 * k + 1, mid, r);
    pull(k);
  }

  void range_add(int ql, int qr, ll x, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0) return;
    if (ql <= l && r <= qr) {
      apply_add(k, x);
      return;
    }
    push(k);
    int mid = (l + r) >> 1;
    range_add(ql, qr, x, 2 * k, l, mid);
    range_add(ql, qr, x, 2 * k + 1, mid, r);
    pull(k);
  }

  void range_update(int ql, int qr, ll x, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0) return;
    if (ql <= l && r <= qr && tree[k].max2 < x && x < tree[k].min2) {
      apply_chmin(k, x);
      apply_chmax(k, x);
      return;
    }
    push(k);
    int mid = (l + r) >> 1;
    range_update(ql, qr, x, 2 * k, l, mid);
    range_update(ql, qr, x, 2 * k + 1, mid, r);
    pull(k);
  }

  ll query_sum(int ql, int qr, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0) return 0;
    if (ql <= l && r <= qr) return tree[k].sum;
    push(k);
    int mid = (l + r) >> 1;
    return query_sum(ql, qr, 2 * k, l, mid) + query_sum(ql, qr, 2 * k + 1, mid, r);
  }

  ll query_max(int ql, int qr, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0) return -INF;
    if (ql <= l && r <= qr) return tree[k].max1;
    push(k);
    int mid = (l + r) >> 1;
    return std::max(query_max(ql, qr, 2 * k, l, mid), query_max(ql, qr, 2 * k + 1, mid, r));
  }

  ll query_min(int ql, int qr, int k, int l, int r) {
    if (qr <= l || r <= ql || tree[k].len == 0) return INF;
    if (ql <= l && r <= qr) return tree[k].min1;
    push(k);
    int mid = (l + r) >> 1;
    return std::min(query_min(ql, qr, 2 * k, l, mid), query_min(ql, qr, 2 * k + 1, mid, r));
  }
};
