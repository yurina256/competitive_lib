#pragma once
#include <vector>
#include <cassert>
#include <type_traits>

/**
 * @brief 2次元累積和 (2D Cumulative Sum)
 * 
 * グリッド上の任意の矩形領域の総和を O(1) で取得するための構造体。
 * 宣言時に2次元配列を与えることで、O(H * W) で累積和テーブルを前計算します。
 * 
 * @tparam T 累積和の計算・保持に用いる型 (デフォルト: long long)
 */
template <typename T = long long>
struct Ruiseki2D {
  long long h = 0, w = 0;
  std::vector<std::vector<T>> sum;

  Ruiseki2D() = default;

  /**
   * @brief H x W のサイズでゼロ初期化
   */
  Ruiseki2D(long long H, long long W) : h(H), w(W), sum(H + 1, std::vector<T>(W + 1, T{})) {}

  /**
   * @brief 元の2次元配列から累積和を構築する
   * @param A H x W の元データ
   */
  template <typename U>
  Ruiseki2D(const std::vector<std::vector<U>>& A) {
    if (A.empty() || A[0].empty()) return;
    h = static_cast<long long>(A.size());
    w = static_cast<long long>(A[0].size());
    sum.assign(h + 1, std::vector<T>(w + 1, T{}));
    for (long long i = 0; i < h; i++) {
      for (long long j = 0; j < w; j++) {
        sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + static_cast<T>(A[i][j]);
      }
    }
  }

  /**
   * @brief 矩形領域 [h1, h2) x [w1, w2) の総和を O(1) で取得する (0-indexed, 半開区間)
   * 
   * @param h1 左上セルの行インデックス (始点, 含む)
   * @param w1 左上セルの列インデックス (始点, 含む)
   * @param h2 右下セルの行インデックス (終点, 含まない)
   * @param w2 右下セルの列インデックス (終点, 含まない)
   * @return T 矩形領域の総和 (空区間または不正な順序の場合は 0 を返す)
   */
  T query(long long h1, long long w1, long long h2, long long w2) const {
    if (h1 >= h2 || w1 >= w2) return T{};
    assert(0 <= h1 && h2 <= h && 0 <= w1 && w2 <= w);
    return sum[h2][w2] - sum[h1][w2] - sum[h2][w1] + sum[h1][w1];
  }

  // 呼び出しのエイリアス (get, sum, operator())
  T get(long long h1, long long w1, long long h2, long long w2) const {
    return query(h1, w1, h2, w2);
  }

  T sum_query(long long h1, long long w1, long long h2, long long w2) const {
    return query(h1, w1, h2, w2);
  }

  T operator()(long long h1, long long w1, long long h2, long long w2) const {
    return query(h1, w1, h2, w2);
  }

  /**
   * @brief 1点 (r, c) の元の値を取得する (0-indexed)
   */
  T get(long long r, long long c) const {
    return query(r, c, r + 1, c + 1);
  }

  T operator()(long long r, long long c) const {
    return get(r, c);
  }
};

// クラステンプレート引数推論 (CTAD) ガイド
template <typename U>
Ruiseki2D(const std::vector<std::vector<U>>&) -> Ruiseki2D<U>;

// 別名エイリアス (CumulativeSum2D)
template <typename T = long long>
using CumulativeSum2D = Ruiseki2D<T>;

/**
 * @brief 2次元配列をインプレースで累積和に変換する (元のScrapbox互換)
 */
template <typename T>
inline void to_2druiseki(std::vector<std::vector<T>>& vec) {
  if (vec.empty() || vec[0].empty()) return;
  size_t h = vec.size();
  size_t w = vec[0].size();
  for (size_t i = 0; i < h; i++) {
    for (size_t j = 0; j < w; j++) {
      T s = T{};
      if (i != 0) s += vec[i - 1][j];
      if (j != 0) s += vec[i][j - 1];
      if (i != 0 && j != 0) s -= vec[i - 1][j - 1];
      s += vec[i][j];
      vec[i][j] = s;
    }
  }
}
