#include <iostream>
#include <vector>
#include "MergeSortTree.cpp"

using namespace std;

int main() {
    cout << "=== Merge Sort Tree Example ===" << endl;

    vector<int> a = {1, 5, 2, 4, 3};
    MergeSortTree<int> mst(a);

    // インデックス範囲 [1, 4) は要素 {5, 2, 4} を指します。
    int l = 1, r = 4;
    cout << "Array slice [1, 4): {5, 2, 4}" << endl;

    // 1. x 以下の要素数
    // 3 以下 -> {2} で 1 個
    cout << "Count <= 3: " << mst.count_le(l, r, 3) << endl;

    // 2. x 未満の要素数
    // 3 未満 -> {2} で 1 個
    cout << "Count < 3: " << mst.count_lt(l, r, 3) << endl;

    // 3. x 以上の要素数
    // 3 以上 -> {5, 4} で 2 個
    cout << "Count >= 3: " << mst.count_ge(l, r, 3) << endl;

    // 4. x より大きい要素数
    // 3 より大きい -> {5, 4} で 2 個
    cout << "Count > 3: " << mst.count_gt(l, r, 3) << endl;

    // 5. 範囲 [x_min, x_max] 内の要素数
    // [2, 5] に含まれる要素 -> {5, 2, 4} で 3 個
    cout << "Count in range [2, 5]: " << mst.count_range(l, r, 2, 5) << endl;

    return 0;
}

/*
出力結果:
=== Merge Sort Tree Example ===
Array slice [1, 4): {5, 2, 4}
Count <= 3: 1
Count < 3: 1
Count >= 3: 2
Count > 3: 2
Count in range [2, 5]: 3
*/
