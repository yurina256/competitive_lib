#include <iostream>
#include "GetKth.cpp"

using namespace std;

int main() {
    cout << "=== GetKth Example (K = 3) ===" << endl;

    // 常に3番目に小さい数を追跡する構造体を作成
    GetKth gk(3);

    // 値を挿入
    cout << "Inserting: 10" << endl;
    gk.insert(10);
    cout << "Current 3rd smallest: " << gk.get() << " (INF because size < 3)" << endl;

    cout << "Inserting: 50, 20" << endl;
    gk.insert(50);
    gk.insert(20);
    // ソート順: {10, 20, 50} -> 3rd: 50
    cout << "Current 3rd smallest: " << gk.get() << endl;

    cout << "Inserting: 30, 40" << endl;
    gk.insert(30);
    gk.insert(40);
    // ソート順: {10, 20, 30, 40, 50} -> 3rd: 30
    cout << "Current 3rd smallest: " << gk.get() << endl;

    // 20 を削除
    cout << "\nErasing: 20" << endl;
    gk.erase(20);
    // ソート順: {10, 30, 40, 50} -> 3rd: 40
    cout << "Current 3rd smallest: " << gk.get() << endl;

    // 10 を削除
    cout << "\nErasing: 10" << endl;
    gk.erase(10);
    // ソート順: {30, 40, 50} -> 3rd: 50
    cout << "Current 3rd smallest: " << gk.get() << endl;

    return 0;
}

/*
出力結果:
=== GetKth Example (K = 3) ===
Inserting: 10
Current 3rd smallest: 4001001001001001001 (INF because size < 3)
Inserting: 50, 20
Current 3rd smallest: 50
Inserting: 30, 40
Current 3rd smallest: 30

Erasing: 20
Current 3rd smallest: 40

Erasing: 10
Current 3rd smallest: 50
*/
