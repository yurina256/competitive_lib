#include <iostream>
#include <vector>
#include "LIS.cpp"

using namespace std;

int main() {
    cout << "=== Longest Increasing Subsequence Example ===" << endl;

    // 1. 狭義単調増加 (strict = true)
    // {1, 3, 5, 2, 4, 6} -> LIS: {1, 3, 5, 6} または {1, 2, 4, 6} で長さ 4
    vector<int> a1 = {1, 3, 5, 2, 4, 6};
    cout << "Array 1: ";
    for (int x : a1) cout << x << " ";
    cout << endl;
    cout << "Strict LIS length: " << get_lis(a1, true) << " (Expected: 4)" << endl;
    cout << endl;

    // 2. 重複を含む場合の狭義 vs 広義の比較
    // {2, 2, 3, 1, 3} 
    // 狭義 (strict = true) -> LIS: {2, 3} で長さ 2
    // 広義 (strict = false) -> LIS: {2, 2, 3, 3} で長さ 4
    vector<int> a2 = {2, 2, 3, 1, 3};
    cout << "Array 2: ";
    for (int x : a2) cout << x << " ";
    cout << endl;
    cout << "Strict LIS length: " << get_lis(a2, true) << " (Expected: 2)" << endl;
    cout << "Non-strict LIS length: " << get_lis(a2, false) << " (Expected: 4)" << endl;

    return 0;
}

/*
出力結果:
=== Longest Increasing Subsequence Example ===
Array 1: 1 3 5 2 4 6 
Strict LIS length: 4 (Expected: 4)

Array 2: 2 2 3 1 3 
Strict LIS length: 2 (Expected: 2)
Non-strict LIS length: 4 (Expected: 4)
*/
