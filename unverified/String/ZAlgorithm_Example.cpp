#include <iostream>
#include <vector>
#include <string>
#include "ZAlgorithm.cpp"

using namespace std;

int main() {
    cout << "=== Z-algorithm Example ===" << endl;
    string s = "ababa";
    auto z = z_algorithm(s);
    cout << "String: " << s << endl;
    cout << "Z-array: ";
    for (int x : z) cout << x << " ";
    cout << endl;

    return 0;
}
