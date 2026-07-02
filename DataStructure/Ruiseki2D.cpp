#pragma once
#include <vector>
#include <cassert>

/**
 * @brief 2次元累積和 (2D Cumulative Sum)
 * 
 * グリッド上の任意の矩形領域の総和を O(1) で取得するための構造体。
 */
struct Ruiseki2D {
  int h = 0, w = 0;
  std::vector<std::vector<long long>> sum;

  Ruiseki2D() = default;

  /**
   * @brief 元の2次元配列から累積和を構築する
   * @param A H x W の元データ
   */
  Ruiseki2D(const std::vector<std::vector<long long>>& A) {
    if (A.empty() || A[0].empty()) return;
    h = A.size();
    w = A[0].size();
    sum.assign(h + 1, std::vector<long long>(w + 1, 0));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + A[i][j];
      }
    }
  }

  /**
   * @brief 矩形領域 [h1, h2) x [w1, w2) の総和を O(1) で取得する (0-indexed, 半開区間)
   * 
   * @param h1 左上セルの行インデックス (始点)
   * @param w1 左上セルの列インデックス (始点)
   * @param h2 右下セルの行インデックス (終点, exclusive)
   * @param w2 右下セルの列インデックス (終点, exclusive)
   */
  long long query(int h1, int w1, int h2, int w2) const {
    if (h1 >= h2 || w1 >= w2) return 0;
    assert(0 <= h1 && h2 <= h && 0 <= w1 && w2 <= w);
    return sum[h2][w2] - sum[h1][w2] - sum[h2][w1] + sum[h1][w1];
  }
};

/**
 * @brief 2次元配列をインプレースで累積和に変換する (元のScrapbox互換)
 */
inline void to_2druiseki(std::vector<std::vector<int>>& vec) {
  if (vec.empty() || vec[0].empty()) return;
  int h = vec.size();
  int w = vec[0].size();
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int s = 0;
      if (i != 0) s += vec[i - 1][j];
      if (j != 0) s += vec[i][j - 1];
      if (i != 0 && j != 0) s -= vec[i - 1][j - 1];
      s += vec[i][j];
      vec[i][j] = s;
    }
  }
}
