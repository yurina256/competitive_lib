#include <iostream>
#include <vector>
#include <string>
#include "SetPartition.cpp"

using namespace std;

int main() {
    cout << "=== Set Partition Enumeration Example (N=3) ===" << endl;

    int n = 3;
    auto partitions = enumerate_set_partitions(n);

    cout << "Total partitions: " << partitions.size() << " (Expected Bell(3) = 5)" << endl;
    cout << "Partitions:" << endl;
    for (const auto& p : partitions) {
        // インデックス配列として出力
        cout << "[ ";
        for (int x : p) cout << x << " ";
        cout << "] -> ";

        // 文字列表現として出力 (Panasonic 2020 D 形式)
        string s = "";
        for (int x : p) s += (char)('a' + x);
        cout << s << endl;
    }

    return 0;
}

/*
出力結果:
=== Set Partition Enumeration Example (N=3) ===
Total partitions: 5 (Expected Bell(3) = 5)
Partitions:
[ 0 0 0 ] -> aaa
[ 0 0 1 ] -> aab
[ 0 1 0 ] -> aba
[ 0 1 1 ] -> abb
[ 0 1 2 ] -> abc
*/
