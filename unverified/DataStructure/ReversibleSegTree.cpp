#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

/**
 * @brief 区間反転可能遅延セグメント木 (Reversible Lazy Segment Tree / Implicit Treap)
 *
 * 平衡二分探索木 (Implicit Treap) を用いて、列に対する以下の操作をすべて O(log N) で処理するデータ構造。
 * atcoder::lazy_segtree と同じテンプレート引数・インターフェースに加え、
 * 区間反転 reverse(l, r) や任意位置への挿入 insert(p, x)・削除 erase(p) に対応する。
 * 非可換なモノイド演算 op にも対応するため、正方向・逆方向の集約値を両方保持する。
 *
 * 計算量:
 *   - 構築: O(N)
 *   - 1点取得・更新 (get / set): O(log N)
 *   - 区間積 (prod) / 全体積 (all_prod): O(log N)
 *   - 区間作用 (apply): O(log N)
 *   - 区間反転 (reverse): O(log N)
 *   - 挿入・削除 (insert / erase): O(log N)
 */
template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct ReversibleSegTree {
  struct Node {
    int l = -1, r = -1;
    int cnt = 1;
    uint64_t pri = 0;
    S val = e();
    S sum = e();
    S rev_sum = e();
    F lazy = id();
    bool rev = false;
  };

  int root = -1;
  std::vector<Node> pool;

  ReversibleSegTree() = default;

  /**
   * @brief 要素数 n (初期値 e()) で構築する (O(N))
   */
  explicit ReversibleSegTree(int n) : ReversibleSegTree(std::vector<S>(n, e())) {}

  /**
   * @brief 配列 v で構築する (O(N))
   */
  explicit ReversibleSegTree(const std::vector<S>& v) {
    int n = static_cast<int>(v.size());
    pool.reserve(n);
    for (int i = 0; i < n; ++i) {
      new_node(v[i]);
    }
    if (n > 0) {
      // Cartesian Tree 構築により O(N) で初期木を作成
      std::vector<int> st;
      st.reserve(n);
      for (int i = 0; i < n; ++i) {
        int last = -1;
        while (!st.empty() && pool[st.back()].pri < pool[i].pri) {
          last = st.back();
          st.pop_back();
        }
        pool[i].l = last;
        if (!st.empty()) {
          pool[st.back()].r = i;
        }
        st.push_back(i);
      }
      root = st.front();
      auto dfs = [&](auto& self, int t) -> void {
        if (t == -1) return;
        self(self, pool[t].l);
        self(self, pool[t].r);
        pull(t);
      };
      dfs(dfs, root);
    }
  }

  /**
   * @brief 現在の要素数を返す (O(1))
   */
  int size() const {
    return count(root);
  }

  /**
   * @brief p 番目の要素を x に更新する (O(log N))
   */
  void set(int p, S x) {
    assert(0 <= p && p < size());
    auto [t1, t2] = split(root, p);
    auto [t2_1, t2_2] = split(t2, 1);
    pool[t2_1].val = pool[t2_1].sum = pool[t2_1].rev_sum = x;
    pool[t2_1].lazy = id();
    pool[t2_1].rev = false;
    root = merge(t1, merge(t2_1, t2_2));
  }

  /**
   * @brief p 番目の要素を取得する (O(log N))
   */
  S get(int p) {
    assert(0 <= p && p < size());
    return prod(p, p + 1);
  }

  /**
   * @brief 区間 [l, r) の総積 op(a[l], ..., a[r-1]) を返す (O(log N))
   */
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return e();
    auto [t1, t2] = split(root, l);
    auto [t2_1, t2_2] = split(t2, r - l);
    S res = pool[t2_1].sum;
    root = merge(t1, merge(t2_1, t2_2));
    return res;
  }

  /**
   * @brief 全区間の総積を返す (O(1))
   */
  S all_prod() const {
    return root == -1 ? e() : pool[root].sum;
  }

  /**
   * @brief p 番目の要素に作用素 f を適用する (O(log N))
   */
  void apply(int p, F f) {
    assert(0 <= p && p < size());
    apply(p, p + 1, f);
  }

  /**
   * @brief 区間 [l, r) に作用素 f を適用する (O(log N))
   */
  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto [t1, t2] = split(root, l);
    auto [t2_1, t2_2] = split(t2, r - l);
    apply_node(t2_1, f);
    root = merge(t1, merge(t2_1, t2_2));
  }

  /**
   * @brief 区間 [l, r) の並び順を反転する (O(log N))
   */
  void reverse(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l >= r - 1) return;
    auto [t1, t2] = split(root, l);
    auto [t2_1, t2_2] = split(t2, r - l);
    toggle_reverse(t2_1);
    root = merge(t1, merge(t2_1, t2_2));
  }

  /**
   * @brief p 番目の位置（0 <= p <= size()）に要素 x を挿入する (O(log N))
   */
  void insert(int p, S x) {
    assert(0 <= p && p <= size());
    auto [t1, t2] = split(root, p);
    root = merge(merge(t1, new_node(x)), t2);
  }

  /**
   * @brief p 番目の位置の要素を削除する (O(log N))
   */
  void erase(int p) {
    assert(0 <= p && p < size());
    auto [t1, t2] = split(root, p);
    auto [t2_1, t2_2] = split(t2, 1);
    root = merge(t1, t2_2);
  }

 private:
  static uint64_t rng() {
    static uint64_t x = 88172645463325252ULL;
    x ^= x << 7;
    x ^= x >> 9;
    return x;
  }

  int new_node(const S& x) {
    int idx = static_cast<int>(pool.size());
    Node node;
    node.pri = rng();
    node.val = x;
    node.sum = x;
    node.rev_sum = x;
    pool.push_back(node);
    return idx;
  }

  int count(int t) const {
    return t == -1 ? 0 : pool[t].cnt;
  }

  void apply_node(int t, const F& f) {
    if (t == -1) return;
    pool[t].val = mapping(f, pool[t].val);
    pool[t].sum = mapping(f, pool[t].sum);
    pool[t].rev_sum = mapping(f, pool[t].rev_sum);
    pool[t].lazy = composition(f, pool[t].lazy);
  }

  void toggle_reverse(int t) {
    if (t == -1) return;
    std::swap(pool[t].l, pool[t].r);
    std::swap(pool[t].sum, pool[t].rev_sum);
    pool[t].rev = !pool[t].rev;
  }

  void push(int t) {
    if (t == -1) return;
    if (pool[t].rev) {
      toggle_reverse(pool[t].l);
      toggle_reverse(pool[t].r);
      pool[t].rev = false;
    }
    if (pool[t].lazy != id()) {
      apply_node(pool[t].l, pool[t].lazy);
      apply_node(pool[t].r, pool[t].lazy);
      pool[t].lazy = id();
    }
  }

  void pull(int t) {
    if (t == -1) return;
    int l = pool[t].l;
    int r = pool[t].r;
    pool[t].cnt = 1 + count(l) + count(r);
    S l_sum = (l == -1) ? e() : pool[l].sum;
    S r_sum = (r == -1) ? e() : pool[r].sum;
    S l_rev = (l == -1) ? e() : pool[l].rev_sum;
    S r_rev = (r == -1) ? e() : pool[r].rev_sum;
    pool[t].sum = op(op(l_sum, pool[t].val), r_sum);
    pool[t].rev_sum = op(op(r_rev, pool[t].val), l_rev);
  }

  int merge(int l, int r) {
    if (l == -1 || r == -1) return l == -1 ? r : l;
    if (pool[l].pri > pool[r].pri) {
      push(l);
      pool[l].r = merge(pool[l].r, r);
      pull(l);
      return l;
    } else {
      push(r);
      pool[r].l = merge(l, pool[r].l);
      pull(r);
      return r;
    }
  }

  std::pair<int, int> split(int t, int k) {
    if (t == -1) return {-1, -1};
    push(t);
    int left_cnt = count(pool[t].l);
    if (k <= left_cnt) {
      auto [l, r] = split(pool[t].l, k);
      pool[t].l = r;
      pull(t);
      return {l, t};
    } else {
      auto [l, r] = split(pool[t].r, k - left_cnt - 1);
      pool[t].r = l;
      pull(t);
      return {t, r};
    }
  }
};
