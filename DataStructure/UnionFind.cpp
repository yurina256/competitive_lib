#pragma once
#include <vector>
#include <utility>

/**
 * @brief Union-Find (Disjoint Set Union / DSU)
 * 
 * グループの併合と、同一グループに属するかどうかの判定を高速に行うデータ構造。
 */
struct UnionFind {
  std::vector<int> data;  // 負ならサイズ、正なら親ノード

  UnionFind(int sz) {
    data.assign(sz, -1);
  }

  /**
   * @brief 要素 x と要素 y の属するグループを併合する
   * @return true 併合された場合
   * @return false すでに同じグループだった場合
   */
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (data[x] > data[y]) std::swap(x, y);  // Xの方が大きい（サイズが大きい＝負の値がより小さい）状態にする
    data[x] += data[y];
    data[y] = x;
    return true;
  }

  /**
   * @brief 要素 k の属するグループの代表元（根）を返す
   */
  int find(int k) {
    if (data[k] < 0) return k;
    return data[k] = find(data[k]);
  }

  /**
   * @brief 要素 k の属するグループのサイズを返す
   */
  int size(int k) {
    return -data[find(k)];
  }

  /**
   * @brief 要素 x と要素 y が同じグループに属するか判定する
   */
  bool same(int x, int y) {
    return find(x) == find(y);
  }
};
