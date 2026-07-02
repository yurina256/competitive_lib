#include <iostream>
#include <string>
#include "RunLengthEncoding.cpp"

using namespace std;

int main() {
    cout << "=== Run Length Encoding Example ===" << endl;

    string s = "aaabbcccca";
    auto res = rle(s);

    cout << "Original string: " << s << endl;
    cout << "RLE Compressed: ";
    for (const auto& p : res) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;

    return 0;
}

/*
出力結果:
=== Run Length Encoding Example ===
Original string: aaabbcccca
RLE Compressed: (a, 3) (b, 2) (c, 4) (a, 1) 
*/
