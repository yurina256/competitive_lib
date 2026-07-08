#pragma once
#include <vector>
#include <cassert>
#include <stdexcept>

/**
 * @brief 2次元いもす法 (2D Imos Method)
 * 
 * 二次元グリッド上の矩形領域に対する加算クエリを O(1)、
 * 最終的なグリッド値の取得を累積和構築後に O(1) で行うデータ構造。
 * 半開区間 [h1, h2) x [w1, w2) に対する加算をサポートする。
 */
struct Imos2D {
  int h = 0, w = 0;
  std::vector<std::vector<long long>> v;
  bool is_built = false;

  Imos2D() = default;

  /**
   * @brief コンストラクタ
   * @param H グリッドの行数 (0 から H-1 まで)
   * @param W グリッドの列数 (0 から W-1 まで)
   */
  Imos2D(int H, int W) : h(H), w(W) {
    assert(H >= 0 && W >= 0);
    v.assign(H + 1, std::vector<long long>(W + 1, 0));
  }

  /**
   * @brief 矩形領域 [h1, h2) x [w1, w2) に値 a を加算する (0-indexed, 半開区間)
   */
  void add(int h1, int w1, int h2, int w2, long long a) {
    if (is_built) throw std::runtime_error("Cannot call add() after build()");
    assert(0 <= h1 && h1 <= h2 && h2 <= h);
    assert(0 <= w1 && w1 <= w2 && w2 <= w);
    if (h1 == h2 || w1 == w2) return;
    v[h1][w1] += a;
    v[h1][w2] -= a;
    v[h2][w1] -= a;
    v[h2][w2] += a;
  }

  /**
   * @brief 累積和を計算してグリッドの各セルの値を確定させる
   */
  void build() {
    if (is_built) throw std::runtime_error("Cannot call build() multiple times");
    is_built = true;
    // 行方向の累積和
    for (int i = 0; i <= h; i++) {
      for (int j = 0; j < w; j++) {
        v[i][j + 1] += v[i][j];
      }
    }
    // 列方向の累積和
    for (int i = 0; i < h; i++) {
      for (int j = 0; j <= w; j++) {
        v[i + 1][j] += v[i][j];
      }
    }
  }

  /**
   * @brief セル (r, c) の現在の値を取得する (0-indexed)
   */
  long long get(int r, int c) const {
    if (!is_built) throw std::runtime_error("Cannot call get() before build()");
    assert(0 <= r && r < h && 0 <= c && c < w);
    return v[r][c];
  }
};
