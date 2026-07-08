#include <iostream>
#include "Imos.cpp"

using namespace std;

int main() {
    // サイズ 10 の配列を管理するいもす法オブジェクトを作成 (インデックス 0 から 9 まで)
    Imos imos(10);

    // [1, 5) の範囲に 3 を加算 (対象インデックス: 1, 2, 3, 4)
    imos.add(1, 5, 3);

    // [3, 8) の範囲に 2 を加算 (対象インデックス: 3, 4, 5, 6, 7)
    imos.add(3, 8, 2);

    // [6, 7) の範囲に -1 を加算 (対象インデックス: 6)
    imos.add(6, 7, -1);

    // 累積和を計算して値を確定させる
    imos.build();

    // 結果の出力
    cout << "=== 1次元いもす法の結果 ===" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "index " << i << ": " << imos.get(i) << endl;
    }

    return 0;
}

/*
出力結果:
=== 1次元いもす法の結果 ===
index 0: 0
index 1: 3
index 2: 3
index 3: 5
index 4: 5
index 5: 2
index 6: 1
index 7: 2
index 8: 0
index 9: 0
*/
