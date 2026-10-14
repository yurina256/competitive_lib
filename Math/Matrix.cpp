#pragma once
#include <vector>
#include <cassert>
#include <atcoder/modint>

using mint = atcoder::modint998244353;
using ll = long long;

/**
 * @brief 行列積 A * B を計算する (O(N^3))
 */
inline std::vector<std::vector<mint>> mat_mul(const std::vector<std::vector<mint>>& A, 
                                               const std::vector<std::vector<mint>>& B) {
  ll n = A.size();
  ll m = A[0].size();
  ll l = B[0].size();
  assert(m == (ll)B.size());

  std::vector<std::vector<mint>> C(n, std::vector<mint>(l, 0));
  for (ll i = 0; i < n; i++) {
    for (ll k = 0; k < m; k++) {
      if (A[i][k].val() == 0) continue;
      for (ll j = 0; j < l; j++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

/**
 * @brief 行列とベクトルの積 A * v を計算する (O(N^2))
 */
inline std::vector<mint> mat_vec_mul(const std::vector<std::vector<mint>>& A, 
                                     const std::vector<mint>& v) {
  ll n = A.size();
  ll m = A[0].size();
  assert(m == (ll)v.size());

  std::vector<mint> res(n, 0);
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      res[i] += A[i][j] * v[j];
    }
  }
  return res;
}

/**
 * @brief 正方行列の累乗 A^n を繰り返し二乗法で計算する (O(N^3 log n))
 */
inline std::vector<std::vector<mint>> mat_pow(std::vector<std::vector<mint>> A, ll n) {
  ll sz = A.size();
  assert(sz == (ll)A[0].size()); // 正方行列であること

  // 単位行列で初期化
  std::vector<std::vector<mint>> res(sz, std::vector<mint>(sz, 0));
  for (ll i = 0; i < sz; i++) {
    res[i][i] = 1;
  }

  while (n > 0) {
    if (n & 1) {
      res = mat_mul(res, A);
    }
    A = mat_mul(A, A);
    n >>= 1;
  }
  return res;
}
