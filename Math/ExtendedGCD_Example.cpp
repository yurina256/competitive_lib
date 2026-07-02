#include <iostream>
#include <numeric>
#include "ExtendedGCD.cpp"

using namespace std;

int main() {
    cout << "=== Extended Euclidean Algorithm Example ===" << endl;

    // 1. 4x + 11y = gcd(4, 11) = 1
    long long a1 = 4, b1 = 11;
    auto [x1, y1] = extgcd(a1, b1);
    cout << a1 << "*(" << x1 << ") + " << b1 << "*(" << y1 << ") = " << (a1 * x1 + b1 * y1) << " (gcd = " << std::gcd(a1, b1) << ")" << endl;

    // 2. 6x + 15y = gcd(6, 15) = 3
    long long a2 = 6, b2 = 15;
    auto [x2, y2] = extgcd(a2, b2);
    cout << a2 << "*(" << x2 << ") + " << b2 << "*(" << y2 << ") = " << (a2 * x2 + b2 * y2) << " (gcd = " << std::gcd(a2, b2) << ")" << endl;

    return 0;
}

/*
出力結果:
=== Extended Euclidean Algorithm Example ===
4*(3) + 11*(-1) = 1 (gcd = 1)
6*(3) + 15*(-1) = 3 (gcd = 3)
*/
