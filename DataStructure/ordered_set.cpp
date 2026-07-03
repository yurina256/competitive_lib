#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

/**
 * @brief ordered_set (Policy-Based Data Structure)
 * 
 * std::set と同様の機能に加え、以下の操作を O(log N) で行えるデータ構造。
 * 1. find_by_order(k): 小さい方から k 番目 (0-indexed) の要素のイテレータを返す。
 *                      (存在しない場合は end() を返す)
 * 2. order_of_key(x) : 値が x 未満の要素の数を返す (x が何番目に小さいか、0-indexed)。
 * 
 * 注意:
 * - 重複要素を管理したい場合は、要素の型を std::pair<T, int> (値と一意なID) にするか、
 *   比較関数を std::less_equal<T> に変更して ordered_multiset として使用します。
 *   ただし less_equal を使う場合、erase などの挙動に注意が必要です (詳しくは Example を参照)。
 */

template <typename T>
using ordered_set = __gnu_pbds::tree<
    T,
    __gnu_pbds::null_type,
    std::less<T>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;
