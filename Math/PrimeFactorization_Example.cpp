#include <iostream>
#include "PrimeFactorization.cpp"

using namespace std;

int main() {
    cout << "=== Prime Factorization Example ===" << endl;

    // 360 の素因数分解 (2^3 * 3^2 * 5^1)
    long long n1 = 360;
    auto res1 = p_fact(n1);
    cout << n1 << " = ";
    for (size_t i = 0; i < res1.size(); ++i) {
        cout << res1[i].first << "^" << res1[i].second;
        if (i + 1 < res1.size()) cout << " * ";
    }
    cout << endl;

    // 素数 1000000007 の素因数分解 (1000000007^1)
    long long n2 = 1000000007;
    auto res2 = p_fact(n2);
    cout << n2 << " = ";
    for (size_t i = 0; i < res2.size(); ++i) {
        cout << res2[i].first << "^" << res2[i].second;
        if (i + 1 < res2.size()) cout << " * ";
    }
    cout << endl;

    // 1 の素因数分解 (空のリストが返る)
    long long n3 = 1;
    auto res3 = p_fact(n3);
    cout << n3 << " size: " << res3.size() << endl;

    return 0;
}

/*
出力結果:
=== Prime Factorization Example ===
360 = 2^3 * 3^2 * 5^1
1000000007 = 1000000007^1
1 size: 0
*/
