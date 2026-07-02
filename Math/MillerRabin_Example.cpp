#include <iostream>
#include "MillerRabin.cpp"

using namespace std;

int main() {
    cout << "=== Miller-Rabin Primality Test Example ===" << endl;

    // 1. 通常の素数
    unsigned long long p1 = 998244353ULL;
    cout << p1 << " is prime: " << (MillerRabin::is_prime(p1) ? "true" : "false") << " (Expected: true)" << endl;

    // 2. 大きな素数 (10^18 + 9 に近い素数)
    unsigned long long p2 = 1000000000000000003ULL;
    cout << p2 << " is prime: " << (MillerRabin::is_prime(p2) ? "true" : "false") << " (Expected: true)" << endl;

    // 3. 大きな合成数 (5 の倍数)
    unsigned long long c1 = 1000000000000000005ULL;
    cout << c1 << " is prime: " << (MillerRabin::is_prime(c1) ? "true" : "false") << " (Expected: false)" << endl;

    // 4. 小さな合成数
    unsigned long long c2 = 4ULL;
    cout << c2 << " is prime: " << (MillerRabin::is_prime(c2) ? "true" : "false") << " (Expected: false)" << endl;

    return 0;
}

/*
出力結果:
=== Miller-Rabin Primality Test Example ===
998244353 is prime: true (Expected: true)
1000000000000000003 is prime: true (Expected: true)
1000000000000000005 is prime: false (Expected: false)
4 is prime: false (Expected: false)
*/
