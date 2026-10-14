#pragma once
#include <vector>
#include <cassert>
#include <stdexcept>

using ll = long long;

/**
 * @brief 多次元いもす法 (Multi-dimensional Imos Method)
 * 
 * 任意の次元数 D における超長方形領域への加算クエリを O(2^D) で行い、
 * 累積和構築後に各点の値を O(1) で取得するデータ構造。
 * 各次元の半開区間 [L_i, R_i) に対する加算をサポートする。
 */
struct ImosND {
  ll dims = 0;
  std::vector<ll> shape;
  std::vector<ll> stride;
  std::vector<ll> v;
  bool is_built = false;

  ImosND() = default;

  /**
   * @brief コンストラクタ
   * @param shape 各次元のサイズ指定 (shape[i] は第 i 次元のサイズ)
   */
  ImosND(const std::vector<ll>& shape) : shape(shape), dims(shape.size()) {
    for (ll s : shape) {
      assert(s >= 0);
    }
    stride.resize(dims);
    ll total_size = 1;
    for (ll i = dims - 1; i >= 0; i--) {
      stride[i] = total_size;
      total_size *= (shape[i] + 1);
    }
    v.assign(total_size, 0);
  }

  /**
   * @brief 超長方形領域 [L_0, R_0) x [L_1, R_1) x ... に値 a を加算する (半開区間)
   */
  void add(const std::vector<ll>& L, const std::vector<ll>& R, ll a) {
    if (is_built) throw std::runtime_error("Cannot call add() after build()");
    assert(L.size() == (size_t)dims && R.size() == (size_t)dims);

    // 範囲チェックと、空領域なら早期リターン
    for (ll i = 0; i < dims; i++) {
      assert(0 <= L[i] && L[i] <= R[i] && R[i] <= shape[i]);
      if (L[i] == R[i]) return;
    }

    ll num_corners = 1LL << dims;
    std::vector<ll> cur_idx(dims);
    for (ll mask = 0; mask < num_corners; mask++) {
      ll flat_idx = 0;
      ll popcount = 0;
      for (ll i = 0; i < dims; i++) {
        if ((mask >> i) & 1) {
          cur_idx[i] = R[i];
          popcount++;
        } else {
          cur_idx[i] = L[i];
        }
        flat_idx += cur_idx[i] * stride[i];
      }
      ll sign = (popcount & 1) ? -1 : 1;
      v[flat_idx] += a * sign;
    }
  }

  /**
   * @brief 累積和を計算して各セルの値を確定させる
   */
  void build() {
    if (is_built) throw std::runtime_error("Cannot call build() multiple times");
    is_built = true;

    ll total_size = v.size();
    for (ll d = 0; d < dims; d++) {
      ll K = stride[d];
      ll S = shape[d] + 1;
      ll A = total_size / (S * K);
      for (ll a = 0; a < A; a++) {
        ll base = a * S * K;
        for (ll s = 0; s < S - 1; s++) {
          ll offset = base + s * K;
          for (ll k = 0; k < K; k++) {
            v[offset + k + K] += v[offset + k];
          }
        }
      }
    }
  }

  /**
   * @brief 指定した座標の現在の値を取得する (0-indexed)
   */
  ll get(const std::vector<ll>& idx) const {
    if (!is_built) throw std::runtime_error("Cannot call get() before build()");
    assert(idx.size() == (size_t)dims);
    ll flat_idx = 0;
    for (ll i = 0; i < dims; i++) {
      assert(0 <= idx[i] && idx[i] < shape[i]);
      flat_idx += idx[i] * stride[i];
    }
    return v[flat_idx];
  }
};
