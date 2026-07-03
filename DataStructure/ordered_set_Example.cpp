#include <iostream>
#include "ordered_set.cpp"

using namespace std;

int main() {
    cout << "=== ordered_set Example ===" << endl;

    // 1. 基本的な使用方法 (一意な要素の管理)
    ordered_set<int> s;

    // 要素の挿入
    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(50);
    s.insert(40);

    cout << "Set elements: ";
    for (auto x : s) cout << x << " ";
    cout << endl; // 昇順にソートされている: 10 20 30 40 50

    // find_by_order(k) : k番目に小さい要素のイテレータを取得 (0-indexed)
    cout << "\n--- find_by_order (0-indexed) ---" << endl;
    cout << "0th smallest: " << *s.find_by_order(0) << endl; // 10
    cout << "2nd smallest: " << *s.find_by_order(2) << endl; // 30
    cout << "4th smallest: " << *s.find_by_order(4) << endl; // 50
    if (s.find_by_order(5) == s.end()) {
        cout << "5th smallest: Not found (out of range)" << endl;
    }

    // order_of_key(x) : x 未満の要素の数を取得 (xの0-indexedでの位置に相当)
    cout << "\n--- order_of_key ---" << endl;
    cout << "Number of elements < 25: " << s.order_of_key(25) << endl; // 2 (10, 20)
    cout << "Number of elements < 10: " << s.order_of_key(10) << endl; // 0
    cout << "Number of elements < 60: " << s.order_of_key(60) << endl; // 5 (10, 20, 30, 40, 50)
    cout << "Number of elements < 30: " << s.order_of_key(30) << endl; // 2 (10, 20)

    // 要素の削除
    cout << "\n--- Erase elements ---" << endl;
    s.erase(20);
    cout << "After erasing 20, set elements: ";
    for (auto x : s) cout << x << " ";
    cout << endl; // 10 30 40 50

    cout << "New 1st smallest (0-indexed): " << *s.find_by_order(1) << endl; // 30
    cout << "Number of elements < 30: " << s.order_of_key(30) << endl; // 1 (10)


    // 2. 重複要素を管理する安全な方法 (pair<値, ユニークID> を使用)
    cout << "\n=== Multiset behavior using pair<int, int> ===" << endl;
    ordered_set<pair<int, int>> ms;
    int id = 0;

    auto ms_insert = [&](int val) {
        ms.insert({val, id++});
    };

    auto ms_erase = [&](int val) {
        // 特定の値を1つ削除するため、lower_bound を用いて該当する要素を探す
        auto it = ms.lower_bound({val, 0});
        if (it != ms.end() && it->first == val) {
            ms.erase(it);
        }
    };

    ms_insert(30);
    ms_insert(10);
    ms_insert(30); // 重複
    ms_insert(20);
    ms_insert(30); // 重複

    cout << "Multiset elements: ";
    for (auto p : ms) cout << p.first << " ";
    cout << endl; // 10 20 30 30 30

    // k番目に小さい要素
    cout << "2nd smallest in multiset (0-indexed): " << ms.find_by_order(2)->first << endl; // 30
    cout << "3rd smallest in multiset (0-indexed): " << ms.find_by_order(3)->first << endl; // 30

    // x 未満の要素数
    cout << "Number of elements < 30: " << ms.order_of_key({30, 0}) << endl; // 2 (10, 20)
    cout << "Number of elements <= 30: " << ms.order_of_key({30, 1e9}) << endl; // 5

    // 値を1つ削除
    ms_erase(30);
    cout << "After erasing one 30: ";
    for (auto p : ms) cout << p.first << " ";
    cout << endl; // 10 20 30 30

    return 0;
}

/*
出力結果:
=== ordered_set Example ===
Set elements: 10 20 30 40 50 

--- find_by_order (0-indexed) ---
0th smallest: 10
2nd smallest: 30
4th smallest: 50
5th smallest: Not found (out of range)

--- order_of_key ---
Number of elements < 25: 2
Number of elements < 10: 0
Number of elements < 60: 5
Number of elements < 30: 2

--- Erase elements ---
After erasing 20, set elements: 10 30 40 50 
New 1st smallest (0-indexed): 30
Number of elements < 30: 1

=== Multiset behavior using pair<int, int> ===
Multiset elements: 10 20 30 30 30 
2nd smallest in multiset (0-indexed): 30
3rd smallest in multiset (0-indexed): 30
Number of elements < 30: 2
Number of elements <= 30: 5
After erasing one 30: 10 20 30 30 
*/
