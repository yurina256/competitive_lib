#include <iostream>
#include <vector>
#include "Mo.cpp"

using namespace std;

int main() {
    cout << "=== Mo's Algorithm Example (Range Sum Query) ===" << endl;

    // 1-indexedでのサンプル配列
    int n = 5;
    vector<long long> A = {0, 10, 20, 30, 40, 50}; 

    // 各端点移動時の更新関数
    // sigma は参照渡しで渡される現在の計算結果、x, y は更新後のポインタ位置
    auto rplus  = [&](long long &sigma, int x, int y) { sigma += A[y]; }; // 右端拡張: 値を加算
    auto lminus = [&](long long &sigma, int x, int y) { sigma += A[x]; }; // 左端拡張: 値を加算
    auto lplus  = [&](long long &sigma, int x, int y) { sigma -= A[x]; }; // 左端縮小: 値を減算
    auto rminus = [&](long long &sigma, int x, int y) { sigma -= A[y]; }; // 右端縮小: 値を減算

    Mo mo(n, rplus, lminus, lplus, rminus);

    // 初期状態として、区間 [1, 1]、値 A[1] を設定
    mo.set(1, 1, A[1]);

    // クエリを登録
    mo.insert(1, 3); // A[1]+A[2]+A[3] = 10+20+30 = 60
    mo.insert(2, 5); // A[2]+A[3]+A[4]+A[5] = 20+30+40+50 = 140
    mo.insert(1, 5); // 10+20+30+40+50 = 150
    mo.insert(4, 4); // A[4] = 40

    // 実行
    auto ans = mo.solve();

    // 結果出力
    cout << "Query results:" << endl;
    cout << "Query [1, 3]: " << ans[0] << endl;
    cout << "Query [2, 5]: " << ans[1] << endl;
    cout << "Query [1, 5]: " << ans[2] << endl;
    cout << "Query [4, 4]: " << ans[3] << endl;

    return 0;
}

/*
出力結果:
=== Mo's Algorithm Example (Range Sum Query) ===
Query results:
Query [1, 3]: 60
Query [2, 5]: 140
Query [1, 5]: 150
Query [4, 4]: 40
*/
