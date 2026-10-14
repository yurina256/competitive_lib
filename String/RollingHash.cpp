#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>

using ll = long long;

/**
 * @brief 安全な Rolling Hash (ローリングハッシュ)
 *
 * 2^61 - 1 (メルセンヌ素数) を法とするローリングハッシュ。
 * 実行ごとにランダムな基数 (base) を安全に生成するため、狙い撃ちケース (ハックケース) に非常に強い。
 *
 * 計算量:
 *   - 構築: O(N)
 *   - 区間ハッシュ取得 (get): O(1)
 *   - ハッシュ結合 (connect): O(1)
 *   - LCP (最長共通接頭辞): O(log N)
 *
 * 空間計算量: O(N)
 * <:AI Gen:>
 * @date 2026.6.23 03:16
 */
struct RollingHash {
  using ull = unsigned long long;
  static const ull mod = (1ULL << 61) - 1;

  /**
   * @brief 実行ごとに一意かつ安全な基数 (base) を生成する
   *
   * リンクエラー (ODR違反) を防ぐため、static メソッド経由で取得します。
   * ASLR によるアドレス揺らぎ、random_device、高精度クロックを混ぜることで、
   * ジャッジ環境ごとの決定論的な起動時間をハックされるリスクを回避します。
   */
  static ull get_base() {
    static ull base = 0;
    if (base == 0) {
      std::random_device rd;
      // アドレスのポインタ(&base)と時間を混ぜてシード値を作る (ASLR対策)
      ull seed = rd() ^ (ull)&base ^ std::chrono::steady_clock::now().time_since_epoch().count();
      std::mt19937_64 rng(seed);
      std::uniform_int_distribution<ull> dist(257, mod - 2);
      base = dist(rng);
      // 偶数の base はハッシュの感度（下位ビットの情報損失）を招くため、奇数に調整
      if (base % 2 == 0) base++;
    }
    return base;
  }

  ll len;
  std::vector<ull> hashed, power;

  static constexpr ull mask(ll a) { return (1ULL << a) - 1; }

  /**
   * @brief a * b % (2^61 - 1) を行う高速な剰余乗算
   */
  inline ull mul(ull a, ull b) const {
    __uint128_t ans = (__uint128_t)a * b;
    ans = (ans >> 61) + (ans & mod);
    if (ans >= mod) ans -= mod;
    return ans;
  }

  RollingHash() : len(0) {
    hashed.push_back(0);
    power.push_back(1);
  }

  /**
   * @brief 文字列 s からハッシュテーブルを構築する (O(N))
   * @param s 対象の文字列
   */
  RollingHash(const std::string& s) : len(s.size()) {
    ull base = get_base();
    hashed.assign(len + 1, 0);
    power.assign(len + 1, 0);
    power[0] = 1;
    for (ll i = 0; i < len; i++) {
      power[i + 1] = mul(power[i], base);
      hashed[i + 1] = mul(hashed[i], base) + s[i];
      if (hashed[i + 1] >= mod) hashed[i + 1] -= mod;
    }
  }

  /**
   * @brief 半開区間 s[l, r) のハッシュ値を取得する (O(1))
   * @param l 左端インデックス (0-indexed, 閉)
   * @param r 右端インデックス (0-indexed, 開)
   */
  ull get(ll l, ll r) const {
    if (l >= r) return 0;
    ull ret = hashed[r] + mod - mul(hashed[l], power[r - l]);
    if (ret >= mod) ret -= mod;
    return ret;
  }

  /**
   * @brief 2つのハッシュ値 h1 (長さ不明) と h2 (長さ h2len) を連結したハッシュ値を得る (O(1))
   */
  ull connect(ull h1, ull h2, ll h2len) const {
    ull ret = mul(h1, power[h2len]) + h2;
    if (ret >= mod) ret -= mod;
    return ret;
  }

  /**
   * @brief 他の RollingHash オブジェクトを自身に連結した新しい RollingHash を作成する
   */
  RollingHash connect(const RollingHash& other) const {
    if (other.len == 0) return *this;
    if (this->len == 0) return other;

    RollingHash result = *this;
    ull base = get_base();

    ll original_len = result.len;
    result.len += other.len;

    result.power.resize(result.len + 1);
    for (ll i = original_len; i < result.len; i++) {
      result.power[i + 1] = result.mul(result.power[i], base);
    }

    ull h1 = result.get(0, original_len);
    result.hashed.resize(result.len + 1);
    for (ll i = 1; i <= other.len; i++) {
      ull h2 = other.get(0, i);
      ull connected_hash = result.mul(h1, result.power[i]) + h2;
      if (connected_hash >= mod) connected_hash -= mod;
      result.hashed[original_len + i] = connected_hash;
    }
    return result;
  }

  /**
   * @brief 自身と b の指定した区間同士の最長共通接頭辞 (LCP) の長さを求める (O(log N))
   * @return ll LCPの長さ
   */
  ll LCP(const RollingHash& b, ll l1, ll r1, ll l2, ll r2) const {
    ll max_len = std::min(r1 - l1, r2 - l2);
    ll low = 0, high = max_len + 1;
    while (high - low > 1) {
      ll mid = (low + high) / 2;
      if (get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
      else
        high = mid;
    }
    return low;
  }
};