#pragma once
#include <vector>
#include <algorithm>

using ll = long long;

/**
 * @brief Range Frequency Query (区間出現回数クエリ)
 *
 * 配列の指定された区間 [l, r) に含まれる特定の値 x の個数を二分探索を用いて高速に数える構造体。
 *
 * 計算量:
 *   - 前処理:
 *     - 座標圧縮ありの場合: O(N log N)
 *     - 値が 0 以上 V 未満の整数で座標圧縮なしの場合: O(N)
 *   - クエリ: O(log N)
 * <: AI Gen :>
 * @date 2026.6.22 13:00
 * @tparam T 配列の要素の型
 */
template <typename T>
struct RangeFreqQuery {
  std::vector<T> xs;                 // 座標圧縮用のユニークな値リスト
  std::vector<std::vector<ll>> pos;  // 各値が出現するインデックスのリスト
  bool is_compressed;                // 座標圧縮を使用しているかフラグ

  RangeFreqQuery() = default;

  /**
   * @brief 座標圧縮ありのコンストラクタ (前処理 O(N log N))
   *
   * 任意の型 T の配列に対して使用可能。
   * @param a 対象の配列
   */
  RangeFreqQuery(const std::vector<T>& a) : is_compressed(true) {
    ll n = a.size();
    xs = a;
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

    pos.resize(xs.size());
    for (ll i = 0; i < n; ++i) {
      ll val_idx = std::lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
      pos[val_idx].push_back(i);
    }
  }

  /**
   * @brief 座標圧縮なしのコンストラクタ (前処理 O(N))
   *
   * 値が 0 以上 V 未満の整数であることが分かっている場合に使用可能。
   * @param a 対象の配列 (要素は 0 以上 V 未満の整数)
   * @param V 値の上限 (0 以上 V 未満)
   */
  RangeFreqQuery(const std::vector<T>& a, ll V) : is_compressed(false) {
    ll n = a.size();
    pos.resize(V);
    for (ll i = 0; i < n; ++i) {
      if (a[i] >= 0 && a[i] < V) {
        pos[a[i]].push_back(i);
      }
    }
  }

  /**
   * @brief 半開区間 [l, r) における値 x の出現回数を取得する
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   * @param x カウント対象の値
   * @return ll 出現回数
   */
  ll count(ll l, ll r, T x) const {
    if (l >= r) return 0;
    ll val_idx = -1;
    if (is_compressed) {
      auto it = std::lower_bound(xs.begin(), xs.end(), x);
      if (it == xs.end() || *it != x) return 0;
      val_idx = it - xs.begin();
    } else {
      if (x < 0 || x >= (T)pos.size()) return 0;
      val_idx = (ll)x;
    }

    const auto& p = pos[val_idx];
    auto it_l = std::lower_bound(p.begin(), p.end(), l);
    auto it_r = std::lower_bound(p.begin(), p.end(), r);
    return std::distance(it_l, it_r);
  }

  /**
   * @brief 閉区間 [l, r] における値 x の出現回数を取得する
   *
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 閉)
   * @param x カウント対象の値
   * @return ll 出現回数
   */
  ll count_closed(ll l, ll r, T x) const {
    return count(l, r + 1, x);
  }
};
