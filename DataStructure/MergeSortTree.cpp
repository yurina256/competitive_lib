#pragma once
#include <vector>
#include <algorithm>

using ll = long long;

/**
 * @brief Merge Sort Tree (マージソート木)
 *
 * セグメント木の各ノードにソート済みの配列を載せたデータ構造。
 * 区間 [l, r) 内にある、値が x 以下の要素の個数などを二分探索で高速に取得できる。
 *
 * 計算量:
 *   - 前処理: O(N log N)
 *   - 空間計算量: O(N log N)
 *   - クエリ: O(log^2 N)
 * <: AI Gen :>
 * @date 2026.6.22 13:00
 * @tparam T 配列の要素の型
 */
template <typename T>
struct MergeSortTree {
  ll n;
  std::vector<std::vector<T>> tree;

  MergeSortTree() = default;

  /**
   * @brief コンストラクタ (前処理 O(N log N))
   *
   * @param a 対象の配列
   */
  MergeSortTree(const std::vector<T>& a) {
    ll sz = a.size();
    n = 1;
    while (n < sz) n <<= 1;
    tree.resize(2 * n);
    for (ll i = 0; i < sz; ++i) {
      tree[n + i] = {a[i]};
    }
    for (ll i = n - 1; i > 0; --i) {
      const auto& left = tree[2 * i];
      const auto& right = tree[2 * i + 1];
      tree[i].resize(left.size() + right.size());
      std::merge(left.begin(), left.end(), right.begin(), right.end(), tree[i].begin());
    }
  }

  /**
   * @brief 区間 [l, r) において、値が x 以下の要素数を取得する (O(log^2 N))
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   * @param x 上限値 (閉)
   * @return ll 要素数
   */
  ll count_le(ll l, ll r, T x) const {
    if (l >= r) return 0;
    ll count = 0;
    l += n;
    r += n;
    while (l < r) {
      if (l & 1) {
        count += std::upper_bound(tree[l].begin(), tree[l].end(), x) - tree[l].begin();
        l++;
      }
      if (r & 1) {
        r--;
        count += std::upper_bound(tree[r].begin(), tree[r].end(), x) - tree[r].begin();
      }
      l >>= 1;
      r >>= 1;
    }
    return count;
  }

  /**
   * @brief 区間 [l, r) において、値が x 未満の要素数を取得する (O(log^2 N))
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   * @param x 上限値 (開)
   * @return ll 要素数
   */
  ll count_lt(ll l, ll r, T x) const {
    if (l >= r) return 0;
    ll count = 0;
    l += n;
    r += n;
    while (l < r) {
      if (l & 1) {
        count += std::lower_bound(tree[l].begin(), tree[l].end(), x) - tree[l].begin();
        l++;
      }
      if (r & 1) {
        r--;
        count += std::lower_bound(tree[r].begin(), tree[r].end(), x) - tree[r].begin();
      }
      l >>= 1;
      r >>= 1;
    }
    return count;
  }

  /**
   * @brief 区間 [l, r) において、値が x 以上の要素数を取得する (O(log^2 N))
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   * @param x 下限値 (閉)
   * @return ll 要素数
   */
  ll count_ge(ll l, ll r, T x) const {
    return (r - l) - count_lt(l, r, x);
  }

  /**
   * @brief 区間 [l, r) において、値が x より大きい要素数を取得する (O(log^2 N))
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   * @param x 下限値 (開)
   * @return ll 要素数
   */
  ll count_gt(ll l, ll r, T x) const {
    return (r - l) - count_le(l, r, x);
  }

  /**
   * @brief 区間 [l, r) において、値が [x_min, x_max] (閉区間) に収まる要素数を取得する (O(log^2 N))
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   * @param x_min 下限値 (閉)
   * @param x_max 上限値 (閉)
   * @return ll 要素数
   */
  ll count_range(ll l, ll r, T x_min, T x_max) const {
    if (x_min > x_max || l >= r) return 0;
    return count_le(l, r, x_max) - count_lt(l, r, x_min);
  }
};
