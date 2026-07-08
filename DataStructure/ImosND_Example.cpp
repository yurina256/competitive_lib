#include <iostream>
#include "ImosND.cpp"

using namespace std;

int main() {
    // 3次元グリッド (形状: 3 x 3 x 3) を管理する多次元いもす法オブジェクトを作成
    ImosND imos({3, 3, 3});

    // 領域 [1, 3) x [0, 2) x [1, 3) に 5 を加算
    imos.add({1, 0, 1}, {3, 2, 3}, 5);

    // 領域 [0, 2) x [1, 3) x [0, 2) に -3 を加算
    imos.add({0, 1, 0}, {2, 3, 2}, -3);

    // 累積和を計算して値を確定させる
    imos.build();

    // 結果の出力
    cout << "=== 多次元いもす法 (3次元) の結果 ===" << endl;
    for (int x = 0; x < 3; x++) {
        cout << "slice x = " << x << ":" << endl;
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                cout << imos.get({x, y, z}) << (z == 2 ? "" : " ");
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

/*
出力結果:
=== 多次元いもす法 (3次元) の結果 ===
slice x = 0:
0 0 0
-3 -3 0
-3 -3 0

slice x = 1:
0 5 5
-3 2 5
-3 -3 0

slice x = 2:
0 5 5
0 5 5
0 0 0
*/
