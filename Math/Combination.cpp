#pragma once
#include <vector>
#include <atcoder/modint>

using mint = atcoder::modint998244353;
using ll = long long;

constexpr ll COM_MAX = 510000;
inline mint fac[COM_MAX], finv[COM_MAX], inv[COM_MAX];

/**
 * @brief 二項係数のテーブルを前処理する (O(MAX))
 */
inline void COMinit() {
  const ll MOD = mint::mod();
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for (ll i = 2; i < COM_MAX; i++) {
    fac[i] = fac[i - 1] * i;
    inv[i] = MOD - inv[MOD % i] * (MOD / i);
    finv[i] = finv[i - 1] * inv[i];
  }
}

/**
 * @brief 二項係数 nCr を計算する (O(1))
 */
inline mint COM(ll n, ll k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * finv[k] * finv[n - k];
}
