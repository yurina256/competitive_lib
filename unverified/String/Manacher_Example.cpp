#include <iostream>
#include <vector>
#include <string>
#include "Manacher.cpp"

using namespace std;

int main() {
    cout << "=== Manacher's Algorithm Example ===" << endl;
    string s = "abaaab";
    auto r = manacher(s);
    cout << "String: " << s << endl;
    cout << "Manacher R-array: ";
    for (int x : r) cout << x << " ";
    cout << endl;

    // 偶数長の回文も検出するためのダミー文字挿入例
    string dummy_s = "$";
    for (char c : s) {
        dummy_s += c;
        dummy_s += "$";
    }
    auto r_dummy = manacher(dummy_s);
    cout << "Dummy String: " << dummy_s << endl;
    cout << "Manacher R-array with dummy: ";
    for (int x : r_dummy) cout << x << " ";
    cout << endl;

    return 0;
}

/*
出力結果:
=== Manacher's Algorithm Example ===
String: abaaab
Manacher R-array: 1 2 1 3 1 1 
Dummy String: $a$b$a$a$a$b$
Manacher R-array with dummy: 1 2 1 4 1 2 3 6 3 2 1 2 1 
*/
