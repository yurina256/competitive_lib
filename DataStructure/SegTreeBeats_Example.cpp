#include <cassert>
#include <iostream>
#include <vector>
#include "SegTreeBeats.cpp"

using namespace std;

int main() {
  cout << "=== SegTreeBeats Example ===" << endl;

  // 初期配列: {2, 7, 1, 8, 2, 8}
  vector<ll> init = {2, 7, 1, 8, 2, 8};
  SegTreeBeats seg(init);

  // [0, 6) の各要素を min(a[i], 5) に更新 -> {2, 5, 1, 5, 2, 5}
  seg.range_chmin(0, 6, 5);
  cout << "chmin(0, 6, 5) 後の総和: " << seg.prod_sum(0, 6) << " (期待値: 20)" << endl;
  assert(seg.prod_sum(0, 6) == 20);
  assert(seg.prod_max(0, 6) == 5);
  assert(seg.prod_min(0, 6) == 1);

  // [1, 5) の各要素を max(a[i], 3) に更新 -> {2, 5, 3, 5, 3, 5}
  seg.range_chmax(1, 5, 3);
  cout << "chmax(1, 5, 3) 後の総和: " << seg.prod_sum(0, 6) << " (期待値: 23)" << endl;
  assert(seg.prod_sum(0, 6) == 23);
  assert(seg.prod_min(1, 5) == 3);

  // [2, 6) に +4 を加算 -> {2, 5, 7, 9, 7, 9}
  seg.range_add(2, 6, 4);
  cout << "add(2, 6, 4) 後の総和: " << seg.prod_sum(0, 6) << " (期待値: 39)" << endl;
  assert(seg.prod_sum(0, 6) == 39);
  assert(seg.prod_max(0, 6) == 9);
  assert(seg.prod_min(0, 6) == 2);

  // [0, 3) を 10 に更新 -> {10, 10, 10, 9, 7, 9}
  seg.range_update(0, 3, 10);
  cout << "update(0, 3, 10) 後の総和: " << seg.prod_sum(0, 6) << " (期待値: 55)" << endl;
  assert(seg.prod_sum(0, 6) == 55);
  assert(seg.get(2) == 10);

  cout << "SegTreeBeats example passed." << endl;
  return 0;
}

/*
出力結果:
=== SegTreeBeats Example ===
chmin(0, 6, 5) 後の総和: 20 (期待値: 20)
chmax(1, 5, 3) 後の総和: 23 (期待値: 23)
add(2, 6, 4) 後の総和: 39 (期待値: 39)
update(0, 3, 10) 後の総和: 55 (期待値: 55)
SegTreeBeats example passed.
*/
