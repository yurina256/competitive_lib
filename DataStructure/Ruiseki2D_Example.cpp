#include <iostream>
#include <vector>
#include "Ruiseki2D.cpp"

using namespace std;

int main() {
    cout << "=== 2D Cumulative Sum Example ===" << endl;

    // 3 x 3 grid
    // 1 2 3
    // 4 5 6
    // 7 8 9
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 型推論 (CTAD) または 明示的型指定 Ruiseki2D<long long>
    Ruiseki2D<long long> r2d(A);

    // 領域 [0, 2) x [0, 2) (値は {1, 2, 4, 5}) の総和 = 12
    cout << "query(0, 0, 2, 2): " << r2d.query(0, 0, 2, 2) << " (Expected: 12)" << endl;
    cout << "operator()(0, 0, 2, 2): " << r2d(0, 0, 2, 2) << " (Expected: 12)" << endl;

    // 領域 [1, 3) x [1, 3) (値は {5, 6, 8, 9}) の総和 = 28
    cout << "get(1, 1, 3, 3): " << r2d.get(1, 1, 3, 3) << " (Expected: 28)" << endl;

    // 全体 [0, 3) x [0, 3) の総和 = 45
    cout << "All sum [0, 3) x [0, 3): " << r2d(0, 0, 3, 3) << " (Expected: 45)" << endl;

    // 1点取得
    cout << "Point (1, 2): " << r2d(1, 2) << " (Expected: 6)" << endl;

    // 空区間 (例: h1 >= h2)
    cout << "Empty range [2, 1) x [0, 2): " << r2d(2, 0, 1, 2) << " (Expected: 0)" << endl;

    // CTADのテスト (int型として推論)
    Ruiseki2D r_int(A);
    cout << "CTAD inferred sum: " << r_int(0, 0, 2, 2) << endl;

    cout << endl;

    // to_2druiseki のテスト
    vector<vector<int>> B = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    to_2druiseki(B);
    cout << "to_2druiseki result (accumulated grid):" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
出力結果:
=== 2D Cumulative Sum Example ===
query(0, 0, 2, 2): 12 (Expected: 12)
operator()(0, 0, 2, 2): 12 (Expected: 12)
get(1, 1, 3, 3): 28 (Expected: 28)
All sum [0, 3) x [0, 3): 45 (Expected: 45)
Point (1, 2): 6 (Expected: 6)
Empty range [2, 1) x [0, 2): 0 (Expected: 0)
CTAD inferred sum: 12

to_2druiseki result (accumulated grid):
1 3 6 
5 12 21 
12 27 45 
*/
