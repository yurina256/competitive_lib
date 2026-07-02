#include <iostream>
#include <vector>
#include "InversionNumber.cpp"

using namespace std;

int main() {
    cout << "=== Inversion Number Example ===" << endl;

    // {3, 1, 2} の転倒数
    // 転倒ペア: (3, 1), (3, 2) -> 計 2
    vector<long long> v1 = {3, 1, 2};
    cout << "inv_num({3, 1, 2}) = " << inv_num(v1) << endl;

    // {1, 2, 3} (昇順ソート済み) の転倒数 -> 0
    vector<long long> v2 = {1, 2, 3};
    cout << "inv_num({1, 2, 3}) = " << inv_num(v2) << endl;

    // {3, 2, 1} (降順ソート済み) の転倒数 -> 3
    vector<long long> v3 = {3, 2, 1};
    cout << "inv_num({3, 2, 1}) = " << inv_num(v3) << endl;

    // 重複値を含む場合 {10, 50, 20, 20}
    // 転倒ペア: (50, 20), (50, 20) -> 計 2
    vector<long long> v4 = {10, 50, 20, 20};
    cout << "inv_num({10, 50, 20, 20}) = " << inv_num(v4) << endl;

    return 0;
}

/*
出力結果:
=== Inversion Number Example ===
inv_num({3, 1, 2}) = 2
inv_num({1, 2, 3}) = 0
inv_num({3, 2, 1}) = 3
inv_num({10, 50, 20, 20}) = 2
*/
