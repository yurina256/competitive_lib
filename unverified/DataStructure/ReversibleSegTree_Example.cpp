#include <cassert>
#include <iostream>
#include <vector>
#include "ReversibleSegTree.cpp"

using namespace std;
using ll = long long;

// 例: 区間アフィン変換・区間和 (非可換な合成も含む汎用デモ)
// ここではシンプルに「区間加算・区間和」と「非可換な一次関数合成」の2つをテスト

namespace RangeAddRangeSum {
struct S {
  ll sum;
  ll sz;
};
using F = ll;
S op(S a, S b) { return {a.sum + b.sum, a.sz + b.sz}; }
S e() { return {0, 0}; }
S mapping(F f, S s) { return {s.sum + f * s.sz, s.sz}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }
}  // namespace RangeAddRangeSum

int main() {
  cout << "=== ReversibleSegTree Example ===" << endl;

  using namespace RangeAddRangeSum;
  // 初期配列: {1, 2, 3, 4, 5}
  vector<S> init = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}};
  ReversibleSegTree<S, op, e, F, mapping, composition, id> seg(init);

  // 区間 [1, 4) を反転 -> {1, 4, 3, 2, 5}
  seg.reverse(1, 4);
  cout << "reverse(1, 4) 後の [0, 3) の和: " << seg.prod(0, 3).sum << " (期待値: 1+4+3 = 8)" << endl;
  assert(seg.prod(0, 3).sum == 8);
  assert(seg.get(1).sum == 4);
  assert(seg.get(3).sum == 2);

  // 区間 [2, 5) に +10 を加算 -> {1, 4, 13, 12, 15}
  seg.apply(2, 5, 10);
  cout << "apply(2, 5, 10) 後の全体の和: " << seg.all_prod().sum << " (期待値: 45)" << endl;
  assert(seg.all_prod().sum == 45);

  // さらに区間 [0, 4) を反転 -> {12, 13, 4, 1, 15}
  seg.reverse(0, 4);
  cout << "reverse(0, 4) 後の [0, 2) の和: " << seg.prod(0, 2).sum << " (期待値: 12+13 = 25)" << endl;
  assert(seg.prod(0, 2).sum == 25);

  // 位置 2 に {100, 1} を挿入 -> {12, 13, 100, 4, 1, 15}
  seg.insert(2, {100, 1});
  assert(seg.size() == 6);
  assert(seg.get(2).sum == 100);

  // 位置 0 を削除 -> {13, 100, 4, 1, 15}
  seg.erase(0);
  assert(seg.size() == 5);
  assert(seg.get(0).sum == 13);

  cout << "ReversibleSegTree example passed." << endl;
  return 0;
}

/*
出力結果:
=== ReversibleSegTree Example ===
reverse(1, 4) 後の [0, 3) の和: 8 (期待値: 1+4+3 = 8)
apply(2, 5, 10) 後の全体の和: 45 (期待値: 45)
reverse(0, 4) 後の [0, 2) の和: 25 (期待値: 12+13 = 25)
ReversibleSegTree example passed.
*/
