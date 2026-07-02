#include <iostream>
#include "Eratosthenes.cpp"

using namespace std;

int main() {
    cout << "=== Eratosthenes Sieve Example ===" << endl;

    // 30 までの素数を前計算
    Eratosthenes sieve(30);

    // 素数判定のテスト
    cout << "Prime checks:" << endl;
    for (int x : {0, 1, 2, 3, 4, 17, 29, 30, 31}) {
        cout << x << " is prime? " << (sieve.get(x) ? "Yes" : "No") << endl;
    }
    cout << endl;

    // 区間内の素数の個数を取得 (半開区間 [l, r))
    cout << "Interval prime counts:" << endl;
    // [1, 10) の素数: {2, 3, 5, 7} -> 4個
    cout << "Primes in [1, 10): " << sieve.prod(1, 10) << endl;
    // [10, 20) の素数: {11, 13, 17, 19} -> 4個
    cout << "Primes in [10, 20): " << sieve.prod(10, 20) << endl;
    // [2, 30) の素数: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29} -> 10個
    cout << "Primes in [2, 30): " << sieve.prod(2, 30) << endl;

    return 0;
}

/*
出力結果:
=== Eratosthenes Sieve Example ===
Prime checks:
0 is prime? No
1 is prime? No
2 is prime? Yes
3 is prime? Yes
4 is prime? No
17 is prime? Yes
29 is prime? Yes
30 is prime? No
31 is prime? No

Interval prime counts:
Primes in [1, 10): 4
Primes in [10, 20): 4
Primes in [2, 30): 10
*/
