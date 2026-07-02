#include <iostream>
#include <vector>
#include "BinarySearch.cpp"

using namespace std;

int main() {
    cout << "=== Binary Search Example ===" << endl;

    vector<long long> A = {1, 3, 5, 7, 9, 11};

    // 例 1: binary_search_tf (True -> False)
    // 条件: A[idx] < 6
    // インデックス: 0, 1, 2 (1, 3, 5) -> True
    // インデックス: 3, 4, 5 (7, 9, 11) -> False
    // 期待値: 2 (値 5)
    long long idx_tf = binary_search_tf(-1, A.size(), [&](long long idx) {
        return A[idx] < 6;
    });
    cout << "binary_search_tf (A[idx] < 6): index = " << idx_tf << ", value = " << A[idx_tf] << endl;

    // 例 2: binary_search_ft (False -> True)
    // 条件: A[idx] >= 6
    // インデックス: 0, 1, 2 (1, 3, 5) -> False
    // インデックス: 3, 4, 5 (7, 9, 11) -> True
    // 期待値: 2 (境界の False 側の最大値。この場合、インデックス 2 (値 5))
    // True となる最初の要素 (インデックス 3, 値 7) を得るには、境界の次のインデックスを取得します
    long long idx_ft = binary_search_ft(-1, A.size(), [&](long long idx) {
        return A[idx] >= 6;
    });
    cout << "binary_search_ft (A[idx] >= 6): border (false) index = " << idx_ft << " (value = " << A[idx_ft] << ")" << endl;
    cout << "First element satisfying A[idx] >= 6: index = " << idx_ft + 1 << ", value = " << A[idx_ft + 1] << endl;

    return 0;
}

/*
出力結果:
=== Binary Search Example ===
binary_search_tf (A[idx] < 6): index = 2, value = 5
binary_search_ft (A[idx] >= 6): border (false) index = 2 (value = 5)
First element satisfying A[idx] >= 6: index = 3, value = 7
*/
