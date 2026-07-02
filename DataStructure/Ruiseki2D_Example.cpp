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
    vector<vector<long long>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Ruiseki2D r2d(A);

    // 領域 [0, 2) x [0, 2) (値は {1, 2, 4, 5}) の総和 = 12
    cout << "Sum of [0, 2) x [0, 2): " << r2d.query(0, 0, 2, 2) << " (Expected: 12)" << endl;

    // 領域 [1, 3) x [1, 3) (値は {5, 6, 8, 9}) の総和 = 28
    cout << "Sum of [1, 3) x [1, 3): " << r2d.query(1, 1, 3, 3) << " (Expected: 28)" << endl;
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
Sum of [0, 2) x [0, 2): 12 (Expected: 12)
Sum of [1, 3) x [1, 3): 28 (Expected: 28)

to_2druiseki result (accumulated grid):
1 3 6 
5 12 21 
12 27 45 
*/
