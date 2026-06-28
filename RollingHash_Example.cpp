#include <iostream>
#include <string>
#include <cassert>
#include "RollingHash.cpp"

using namespace std;

int main() {
    string s = "abracadabra";
    cout << "String: " << s << " (Length: " << s.size() << ")" << endl;

    // Rolling Hash 構築
    RollingHash rh(s);

    // s[0, 4) は "abra", s[7, 11) も "abra"
    // これらが等しいかハッシュで確認
    auto h1 = rh.get(0, 4);
    auto h2 = rh.get(7, 11);
    cout << "Hash of s[0, 4) ('abra'): " << h1 << endl;
    cout << "Hash of s[7, 11) ('abra'): " << h2 << endl;
    if (h1 == h2) {
        cout << "-> Same hash! (Correct)" << endl;
    } else {
        cout << "-> Different hash! (Error)" << endl;
    }
    cout << endl;

    // 最長共通接頭辞 (LCP) のデモ
    // s[0, 11) は "abracadabra", s[7, 11) は "abra"
    // LCP("abracadabra", "abra") を求める
    int lcp_len = rh.LCP(rh, 0, 11, 7, 11);
    cout << "LCP of s[0, 11) and s[7, 11): " << lcp_len << " (Expected: 4, since 'abra' is prefix of 'abracadabra')" << endl;
    cout << endl;

    // ハッシュの結合 (connect) デモ
    string s_part1 = "abc";
    string s_part2 = "def";
    string s_full = "abcdef";

    RollingHash rh1(s_part1);
    RollingHash rh2(s_part2);
    RollingHash rh_full(s_full);

    // rh1 に rh2 を結合する
    RollingHash rh_connected = rh1.connect(rh2);
    cout << "Hash of connected 'abc' + 'def': " << rh_connected.get(0, 6) << endl;
    cout << "Hash of constructed 'abcdef':   " << rh_full.get(0, 6) << endl;
    if (rh_connected.get(0, 6) == rh_full.get(0, 6)) {
        cout << "-> Connection hashes match successfully!" << endl;
    } else {
        cout << "-> Connection hashes mismatch!" << endl;
    }

    return 0;
}
