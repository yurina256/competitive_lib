#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cassert>

using ll = long long;

namespace sais_impl {

inline std::vector<ll> sa_naive(const std::vector<ll>& s) {
    ll n = ll(s.size());
    std::vector<ll> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](ll l, ll r) {
        if (l == r) return false;
        while (l < n && r < n) {
            if (s[l] != s[r]) return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

inline std::vector<ll> sa_doubling(const std::vector<ll>& s) {
    ll n = ll(s.size());
    std::vector<ll> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (ll k = 1; k < n; k *= 2) {
        auto cmp = [&](ll x, ll y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
            ll rx = x + k < n ? rnk[x + k] : -1;
            ll ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (ll i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}

// SA-IS, linear-time suffix array construction
// Reference:
// G. Nong, S. Zhang, and W. H. Chan,
// Two Efficient Algorithms for Linear Time Suffix Array Construction
template <ll THRESHOLD_NAIVE = 10, ll THRESHOLD_DOUBLING = 40>
std::vector<ll> sa_is(const std::vector<ll>& s, ll upper) {
    ll n = ll(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }

    std::vector<ll> sa(n);
    std::vector<bool> ls(n);
    for (ll i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<ll> sum_l(upper + 1), sum_s(upper + 1);
    for (ll i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (ll i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<ll>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<ll> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (ll i = 0; i < n; i++) {
            ll v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (ll i = n - 1; i >= 0; i--) {
            ll v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<ll> lms_map(n + 1, -1);
    ll m = 0;
    for (ll i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<ll> lms;
    lms.reserve(m);
    for (ll i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<ll> sorted_lms;
        sorted_lms.reserve(m);
        for (ll v : sa) {
            if (lms_map[v] != -1) sorted_lms.push_back(v);
        }
        std::vector<ll> rec_s(m);
        ll rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (ll i = 1; i < m; i++) {
            ll l = sorted_lms[i - 1], r = sorted_lms[i];
            ll end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            ll end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (ll i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

} // namespace sais_impl

/**
 * @brief SA-ISによる接尾辞配列 (Suffix Array) および LCP配列の構築構造体
 *
 * 文字列または配列に対して、接尾辞配列 (Suffix Array) を O(N) で構築します。
 * また、Kasaiのアルゴリズムを用いて LCP配列を O(N) で構築し、
 * オプションで Sparse Table を用いた O(1) LCP クエリを提供します。
 *
 * 計算量:
 *   - 構築: O(N) (Sparse Table を構築する場合は O(N log N))
 *   - LCPクエリ: O(1)
 *
 * <:AI Gen:>
 * @date 2026.6.27
 * @tparam T 配列の要素の型 (文字列の場合は自動的に std::string から構築可能)
 */
template <typename T = ll>
struct SuffixArray {
    ll n;
    std::vector<ll> sa;    // 接尾辞配列 (sa[i] は辞書順で i 番目の接尾辞の開始インデックス)
    std::vector<ll> rnk;   // ランク配列 (rnk[i] は元の文字列 of i 文字目から始まる接尾辞の辞書順順位)
    std::vector<ll> lcp;   // LCP配列 (lcp[i] は sa[i] と sa[i+1] から始まる接尾辞の最長共通接頭辞の長さ。サイズは N-1)

    // LCPクエリ高速化のための Sparse Table
    std::vector<std::vector<ll>> st;
    std::vector<ll> lookup;

    SuffixArray() : n(0) {}

    /**
     * @brief 文字列から接尾辞配列・LCP配列を構築する
     * 
     * @param s 対象の文字列
     * @param build_rmq LCPクエリを高速に行うための Sparse Table を構築するかどうか
     */
    SuffixArray(const std::string& s, bool build_rmq = false) {
        n = s.size();
        if (n == 0) return;
        std::vector<ll> s_int(n);
        for (ll i = 0; i < n; ++i) {
            s_int[i] = (unsigned char)s[i];
        }
        sa = sais_impl::sa_is(s_int, 255);
        build_rnk_lcp(s_int);
        if (build_rmq) build_sparse_table();
    }

    /**
     * @brief 配列 (std::vector) から接尾辞配列・LCP配列を構築する
     * 
     * @param s 対象の配列
     * @param build_rmq LCPクエリを高速に行うための Sparse Table を構築するかどうか
     */
    SuffixArray(const std::vector<T>& s, bool build_rmq = false) {
        n = s.size();
        if (n == 0) return;
        std::vector<ll> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](ll l, ll r) { return s[l] < s[r]; });
        std::vector<ll> s_int(n);
        ll now = 0;
        for (ll i = 0; i < n; i++) {
            if (i && s[idx[i - 1]] != s[idx[i]]) now++;
            s_int[idx[i]] = now;
        }
        sa = sais_impl::sa_is(s_int, now);
        build_rnk_lcp(s);
        if (build_rmq) build_sparse_table();
    }

    /**
     * @brief 元の配列におけるインデックス i から始まる接尾辞と j から始まる接尾辞の最長共通接頭辞 (LCP) の長さを O(1) で取得する
     * 
     * @note この関数を呼ぶには、コンストラクタで build_rmq を true にしておく必要があります。
     * @param i 接尾辞の開始インデックス1
     * @param j 接尾辞の開始インデックス2
     * @return ll LCPの長さ
     */
    ll get_lcp(ll i, ll j) const {
        assert(!st.empty() && "Sparse Table is not initialized. Pass build_rmq = true in constructor.");
        if (i == j) return n - i;
        ll r1 = rnk[i], r2 = rnk[j];
        if (r1 > r2) std::swap(r1, r2);
        // 区間 [r1, r2) における LCP の最小値を取得
        ll len = r2 - r1;
        ll k = lookup[len];
        return std::min(st[k][r1], st[k][r2 - (1LL << k)]);
    }

private:
    template <typename Container>
    void build_rnk_lcp(const Container& s) {
        rnk.resize(n);
        for (ll i = 0; i < n; ++i) {
            rnk[sa[i]] = i;
        }
        lcp.assign(n - 1, 0);
        ll h = 0;
        for (ll i = 0; i < n; ++i) {
            if (h > 0) h--;
            if (rnk[i] == 0) continue;
            ll j = sa[rnk[i] - 1];
            for (; j + h < n && i + h < n; ++h) {
                if (s[j + h] != s[i + h]) break;
            }
            lcp[rnk[i] - 1] = h;
        }
    }

    void build_sparse_table() {
        if (n <= 1) return;
        ll max_log = 0;
        while ((1LL << max_log) <= n - 1) max_log++;
        st.assign(max_log, std::vector<ll>(n - 1));
        for (ll i = 0; i < n - 1; ++i) {
            st[0][i] = lcp[i];
        }
        for (ll k = 1; k < max_log; ++k) {
            for (ll i = 0; i + (1LL << k) <= n - 1; ++i) {
                st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1LL << (k - 1))]);
            }
        }
        lookup.assign(n, 0);
        for (ll i = 2; i < n; ++i) {
            lookup[i] = lookup[i >> 1] + 1;
        }
    }
};
