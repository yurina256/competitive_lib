#pragma once
#include <vector>
#include <cassert>
#include <stdexcept>

/**
 * @brief 1次元いもす法 (1D Imos Method)
 * 
 * 区間加算クエリを O(1)、最終値の取得を累積和構築後に O(1) で行うデータ構造。
 * 半開区間 [l, r) に対する加算をサポートする。
 */
struct Imos {
  std::vector<long long> v;
  bool is_built = false;

  /**
   * @brief コンストラクタ
   * @param n 管理する配列のサイズ (インデックス 0 から n-1 まで)
   */
  Imos(long long n) {
    assert(n >= 0);
    v.resize(n + 1, 0);
  }

  /**
   * @brief 半開区間 [l, r) に値 a を加算する
   */
  void add(long long l, long long r, long long a) {
    if (is_built) throw std::runtime_error("Cannot call add() after build()");
    assert(0 <= l && l <= r && r < (long long)v.size());
    v[l] += a;
    v[r] -= a;
  }

  /**
   * @brief 累積和を計算して各インデックスの値を確定させる
   */
  void build() {
    if (is_built) throw std::runtime_error("Cannot call build() multiple times");
    is_built = true;
    for (size_t i = 0; i < v.size() - 1; i++) {
      v[i + 1] += v[i];
    }
  }

  /**
   * @brief インデックス p の現在の値を取得する (0-indexed)
   */
  long long get(long long p) const {
    if (!is_built) throw std::runtime_error("Cannot call get() before build()");
    assert(0 <= p && p < (long long)v.size() - 1);
    return v[p];
  }
};