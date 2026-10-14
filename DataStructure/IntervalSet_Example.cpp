#include <iostream>
#include "IntervalSet.cpp"

using namespace std;

int main() {
  // long long 型のキーと、char 型の値を保持する IntervalMap を作成
  IntervalMap<char> im;

  // [10, 20] を 'A' で塗りつぶす
  im.add(10, 20, 'A');
  // [15, 25] を 'B' で塗りつぶす (一部重複するため、[10, 14] が 'A'、[15, 25] が 'B' になる)
  im.add(15, 25, 'B');
  // [5, 8] を 'C' で塗りつぶす
  im.add(5, 8, 'C');

  cout << "=== 1. 点クエリの確認 ===" << endl;
  for (int x : {4, 5, 8, 9, 10, 14, 15, 20, 25, 26}) {
    auto it = im.find(x);
    if (it != im.st.end()) {
      cout << "x = " << x << " belongs to interval [" << it->l << ", " << it->r << "] with val = '" << it->val << "'" << endl;
    } else {
      cout << "x = " << x << " does not belong to any interval." << endl;
    }
  }
  cout << endl;

  cout << "=== 2. 全ての区間の出力 ===" << endl;
  for (const auto& node : im.st) {
    cout << "[" << node.l << ", " << node.r << "] -> '" << node.val << "'" << endl;
  }
  cout << endl;

  // [12, 18] の区間を削除する (彫り込み)
  // 元々: [5, 8]->'C', [10, 14]->'A', [15, 25]->'B'
  // 削除後: [5, 8]->'C', [10, 11]->'A', [19, 25]->'B'
  cout << "=== 3. [12, 18] を削除後の全区間 ===" << endl;
  im.remove(12, 18);
  for (const auto& node : im.st) {
    cout << "[" << node.l << ", " << node.r << "] -> '" << node.val << "'" << endl;
  }

  return 0;
}

/*
出力結果:
=== 1. 点クエリの確認 ===
x = 4 does not belong to any interval.
x = 5 belongs to interval [5, 8] with val = 'C'
x = 8 belongs to interval [5, 8] with val = 'C'
x = 9 does not belong to any interval.
x = 10 belongs to interval [10, 14] with val = 'A'
x = 14 belongs to interval [10, 14] with val = 'A'
x = 15 belongs to interval [15, 25] with val = 'B'
x = 20 belongs to interval [15, 25] with val = 'B'
x = 25 belongs to interval [15, 25] with val = 'B'
x = 26 does not belong to any interval.

=== 2. 全ての区間の出力 ===
[5, 8] -> 'C'
[10, 14] -> 'A'
[15, 25] -> 'B'

=== 3. [12, 18] を削除後の全区間 ===
[5, 8] -> 'C'
[10, 11] -> 'A'
[19, 25] -> 'B'
*/
