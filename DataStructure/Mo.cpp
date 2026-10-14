#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <functional>

using ll = long long;

/**
 * @brief Mo's Algorithm (クエリ平方分割)
 * 
 * 範囲 [L, R] に対するクエリが、ポインタを1つずつ進める（要素の追加・削除）ことで
 * 高速に遷移できる場合に、クエリを並び替えて高速化する構造体。
 * 
 * 計算量: O(N√Q + Q log Q)
 */
struct Mo {
  ll n;
  std::vector<std::pair<ll, ll>> query;
  std::vector<ll> ord;
  std::vector<ll> ans;
  ll q = 0;
  ll bs = 0;
  ll x = 0, y = 0;       // 現在の区間ポインタ [x, y]
  ll sigma = 0;          // 現在の区間の計算結果

  std::function<void(ll&, ll, ll)> rplus;   // 右端を広げる (y++)
  std::function<void(ll&, ll, ll)> lminus;  // 左端を広げる (x--)
  std::function<void(ll&, ll, ll)> lplus;   // 左端を縮める (x++)
  std::function<void(ll&, ll, ll)> rminus;  // 右端を縮める (y--)

  /**
   * @brief コンストラクタ
   * 
   * @param n 配列のサイズ
   * @param rplus (sigma, x, y) 右端拡張時の更新関数
   * @param lminus (sigma, x, y) 左端拡張時の更新関数
   * @param lplus (sigma, x, y) 左端縮小時の更新関数
   * @param rminus (sigma, x, y) 右端縮小時の更新関数
   */
  Mo(ll n,
     std::function<void(ll&, ll, ll)> rplus,
     std::function<void(ll&, ll, ll)> lminus,
     std::function<void(ll&, ll, ll)> lplus,
     std::function<void(ll&, ll, ll)> rminus)
      : n(n), rplus(rplus), lminus(lminus), lplus(lplus), rminus(rminus) {}

  /**
   * @brief 走査開始位置の初期状態を設定する
   * 
   * @param sx 初期左端
   * @param sy 初期右端
   * @param sv 初期状態の値
   */
  void set(ll sx, ll sy, ll sv) {
    x = sx;
    y = sy;
    sigma = sv;
  }

  /**
   * @brief クエリを登録する (0-indexed または 1-indexed)
   */
  void insert(ll l, ll r) {
    query.push_back({l, r});
  }

  /**
   * @brief クエリをソートし、Moのアルゴリズムを実行する
   * @return std::vector<ll> 各クエリに対する答えの配列
   */
  std::vector<ll> solve() {
    q = query.size();
    bs = n / std::max<ll>(1, std::min<ll>(n, std::sqrt(q)));
    ord.resize(q);
    std::iota(ord.begin(), ord.end(), 0);
    ans.resize(q);
    
    std::sort(ord.begin(), ord.end(), [&](ll a, ll b) {
      ll ablock = query[a].first / bs;
      ll bblock = query[b].first / bs;
      if (ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? query[a].second > query[b].second : query[a].second < query[b].second;
    });

    for (ll i = 0; i < q; i++) {
      auto [tagl, tagr] = query[ord[i]];
      while (y < tagr) {
        y++;
        rplus(sigma, x, y);
      }
      while (x > tagl) {
        x--;
        lminus(sigma, x, y);
      }
      while (x < tagl) {
        lplus(sigma, x, y);
        x++;
      }
      while (y > tagr) {
        rminus(sigma, x, y);
        y--;
      }
      ans[ord[i]] = sigma;
    }
    return ans;
  }
};
