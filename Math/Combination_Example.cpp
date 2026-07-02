#include <iostream>
#include "Combination.cpp"

using namespace std;

int main() {
    cout << "=== Combination Example ===" << endl;

    // 二項係数のテーブルを初期化
    COMinit();

    // いくつかの二項係数（組み合わせ）を計算
    // 5C2 = 10
    cout << "5 C 2 = " << COM(5, 2).val() << endl;

    // 5C0 = 1
    cout << "5 C 0 = " << COM(5, 0).val() << endl;

    // 5C5 = 1
    cout << "5 C 5 = " << COM(5, 5).val() << endl;

    // 5C6 = 0 (n < k のため 0)
    cout << "5 C 6 = " << COM(5, 6).val() << endl;

    // 大きな値での計算
    // 100000 C 50000
    cout << "100000 C 50000 = " << COM(100000, 50000).val() << endl;

    return 0;
}

/*
出力結果:
=== Combination Example ===
5 C 2 = 10
5 C 0 = 1
5 C 5 = 1
5 C 6 = 0
100000 C 50000 = 14903301
*/
