#pragma once
#include <set>

constexpr long long GETKTH_INF = 4001001001001001001ll;

/**
 * @brief 動的に要素を追加・削除しながら、常にK番目に小さい値を取得する構造体
 * 
 * 計算量:
 *   - 挿入 (insert): O(log N)
 *   - 削除 (erase): O(log N)
 *   - 取得 (get): O(1)
 */
struct GetKth {
  std::multiset<long long> lower;
  std::multiset<long long> upper;
  long long k;

  /**
   * @brief コンストラクタ
   * @param a 取得したい順位 K (1-indexed)
   */
  GetKth(long long a) : k(a) {}

  /**
   * @brief 要素 n を追加する (O(log N))
   */
  void insert(long long n) {
    lower.insert(n);
    if ((long long)lower.size() > k) {
      long long a = *lower.rbegin();
      lower.erase(lower.find(a));
      upper.insert(a);
    }
  }

  /**
   * @brief K 番目に小さい値を取得する (O(1))
   * 要素数が K 未満の場合は GETKTH_INF を返す。
   */
  long long get() {
    if ((long long)lower.size() < k) return GETKTH_INF;
    return *lower.rbegin();
  }

  /**
   * @brief 要素 n を1つ削除する (O(log N))
   */
  void erase(long long n) {
    if (n <= get()) {
      lower.erase(lower.find(n));
      if ((long long)upper.size() > 0) {
        long long a = *upper.begin();
        upper.erase(upper.find(a));
        lower.insert(a);
      }
    } else {
      upper.erase(upper.find(n));
    }
  }

  /**
   * @brief 現在の総要素数を返す
   */
  long long size() {
    return upper.size() + lower.size();
  }
};
