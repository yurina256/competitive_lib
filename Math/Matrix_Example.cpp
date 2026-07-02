#include <iostream>
#include "Matrix.cpp"

using namespace std;

int main() {
    cout << "=== Matrix Operations Example ===" << endl;

    // 1. 行列積のテスト
    // A = {{1, 2}, {3, 4}}
    // B = {{2, 0}, {1, 2}}
    // A * B = {{4, 4}, {10, 8}}
    vector<vector<mint>> A = {{1, 2}, {3, 4}};
    vector<vector<mint>> B = {{2, 0}, {1, 2}};
    auto AB = mat_mul(A, B);

    cout << "A * B:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << AB[i][j].val() << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 2. 行列累乗によるフィボナッチ数の計算
    // F_0 = 0, F_1 = 1
    // [F_{n+1}, F_n]^T = [[1, 1], [1, 0]]^n * [F_1, F_0]^T
    // n = 10 のとき、 F_10 = 55
    long long n = 10;
    vector<vector<mint>> T = {{1, 1}, {1, 0}}; // 遷移行列
    auto T_n = mat_pow(T, n - 1); // T^(n-1)

    vector<mint> F_init = {1, 0}; // [F_1, F_0]
    auto F_n = mat_vec_mul(T_n, F_init);

    cout << "Fibonacci F_" << n << " = " << F_n[0].val() << " (Expected: 55)" << endl;

    return 0;
}

/*
出力結果:
=== Matrix Operations Example ===
A * B:
4 4 
10 8 

Fibonacci F_10 = 55 (Expected: 55)
*/
