#include <iostream>
#include <algorithm>
#include "SegTree2D.cpp"

using namespace std;

int main() {
    cout << "=== SegTree2D (Range Maximum Query) Example ===" << endl;

    int h = 4, w = 4;
    // 単位元は -1 (負の値を持たないと仮定)
    // 演算 f は max
    auto f = [](int a, int b) { return max(a, b); };
    SegTree2D<int> seg(h, w, -1, f);

    // 点更新
    seg.update(1, 1, 5);
    seg.update(2, 2, 8);
    seg.update(0, 3, 3);

    // クエリ取得
    cout << "Max in [0, 2) x [0, 2): " << seg.query(0, 0, 2, 2) << " (Expected: 5)" << endl;
    cout << "Max in [0, 3) x [0, 3): " << seg.query(0, 0, 3, 3) << " (Expected: 8)" << endl;
    cout << "Max in [0, 1) x [0, 2): " << seg.query(0, 0, 1, 2) << " (Expected: -1)" << endl;
    cout << "Max in [0, 4) x [2, 4): " << seg.query(0, 2, 4, 4) << " (Expected: 8)" << endl;

    return 0;
}

/*
出力結果:
=== SegTree2D (Range Maximum Query) Example ===
Max in [0, 2) x [0, 2): 5 (Expected: 5)
Max in [0, 3) x [0, 3): 8 (Expected: 8)
Max in [0, 1) x [0, 2): -1 (Expected: -1)
Max in [0, 4) x [2, 4): 8 (Expected: 8)
*/
