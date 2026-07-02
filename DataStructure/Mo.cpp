#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <functional>

/**
 * @brief Mo's Algorithm (クエリ平方分割)
 * 
 * 範囲 [L, R] に対するクエリが、ポインタを1つずつ進める（要素の追加・削除）ことで
 * 高速に遷移できる場合に、クエリを並び替えて高速化する構造体。
 * 
 * 計算量: O(N√Q + Q log Q)
 */
struct Mo {
  int n;
  std::vector<std::pair<int, int>> query;
  std::vector<int> ord;
  std::vector<long long> ans;
  int q = 0;
  int bs = 0;
  int x = 0, y = 0;       // 現在の区間ポインタ [x, y]
  long long sigma = 0;    // 現在の区間の計算結果

  std::function<void(long long&, int, int)> rplus;   // 右端を広げる (y++)
  std::function<void(long long&, int, int)> lminus;  // 左端を広げる (x--)
  std::function<void(long long&, int, int)> lplus;   // 左端を縮める (x++)
  std::function<void(long long&, int, int)> rminus;  // 右端を縮める (y--)

  /**
   * @brief コンストラクタ
   * 
   * @param n 配列のサイズ
   * @param rplus (sigma, x, y) 右端拡張時の更新関数
   * @param lminus (sigma, x, y) 左端拡張時の更新関数
   * @param lplus (sigma, x, y) 左端縮小時の更新関数
   * @param rminus (sigma, x, y) 右端縮小時の更新関数
   */
  Mo(int n,
     std::function<void(long long&, int, int)> rplus,
     std::function<void(long long&, int, int)> lminus,
     std::function<void(long long&, int, int)> lplus,
     std::function<void(long long&, int, int)> rminus)
      : n(n), rplus(rplus), lminus(lminus), lplus(lplus), rminus(rminus) {}

  /**
   * @brief 走査開始位置の初期状態を設定する
   * 
   * @param sx 初期左端
   * @param sy 初期右端
   * @param sv 初期状態の値
   */
  void set(int sx, int sy, long long sv) {
    x = sx;
    y = sy;
    sigma = sv;
  }

  /**
   * @brief クエリを登録する (0-indexed または 1-indexed)
   */
  void insert(int l, int r) {
    query.push_back({l, r});
  }

  /**
   * @brief クエリをソートし、Moのアルゴリズムを実行する
   * @return std::vector<long long> 各クエリに対する答えの配列
   */
  std::vector<long long> solve() {
    q = query.size();
    bs = n / std::max<int>(1, std::min<int>(n, std::sqrt(q)));
    ord.resize(q);
    std::iota(ord.begin(), ord.end(), 0);
    ans.resize(q);
    
    std::sort(ord.begin(), ord.end(), [&](int a, int b) {
      int ablock = query[a].first / bs;
      int bblock = query[b].first / bs;
      if (ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? query[a].second > query[b].second : query[a].second < query[b].second;
    });

    for (int i = 0; i < q; i++) {
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
