#include <cassert>
#include <iostream>
#include <vector>
#include "LinkCutTree.cpp"

long long op_sum(long long a, long long b) {
  return a + b;
}

long long e_sum() {
  return 0;
}

int main() {
  LinkCutTree<long long, op_sum, e_sum> lct(std::vector<long long>{1, 2, 3, 4, 5});

  // 頂点 0(1), 1(2), 2(3), 3(4), 4(5)
  assert(lct.link(0, 1)); // 0-1 連結
  assert(lct.link(1, 2)); // 1-2 連結
  assert(lct.link(2, 3)); // 2-3 連結
  assert(lct.path_query(0, 3) == 10); // パス 0-1-2-3 の合計: 1 + 2 + 3 + 4 = 10
  assert(lct.connected(0, 3));        // 0 と 3 は連結
  assert(!lct.connected(0, 4));       // 0 と 4 は非連結

  lct.set_value(1, 10);               // 頂点 1 の値を 2 から 10 に更新
  assert(lct.path_query(3, 0) == 18); // パス 0-1-2-3 の合計: 1 + 10 + 3 + 4 = 18

  assert(lct.cut(1, 2));              // 辺 1-2 を切断
  assert(!lct.connected(0, 3));       // 切断により 0 と 3 は非連結
  assert(!lct.cut(1, 3));             // 直接の辺がないため cut 失敗

  std::cout << "Link-Cut Tree example passed." << std::endl;
  return 0;
}

/*
出力結果:
Link-Cut Tree example passed.
*/
