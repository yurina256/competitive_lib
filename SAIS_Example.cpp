#include <iostream>
#include <string>
#include <vector>
#include "SAIS.cpp"

using namespace std;

int main() {
    // ====================================================
    // 1. 文字列に対する Suffix Array
    // ====================================================
    cout << "=== 1. 文字列 (abracadabra) ===" << endl;
    string s = "abracadabra";
    
    // SuffixArray の構築 (Sparse Table による LCP クエリを有効化するため true を指定)
    SuffixArray sa_str(s, true);

    cout << "index: sa[i] | suffix" << endl;
    for (int i = 0; i < sa_str.n; ++i) {
        cout << i << ": " << sa_str.sa[i] << " | " << s.substr(sa_str.sa[i]) << endl;
    }
    cout << endl;

    cout << "LCP Array:" << endl;
    for (int i = 0; i < sa_str.n - 1; ++i) {
        cout << "LCP between sa[" << i << "] and sa[" << i+1 << "]: " << sa_str.lcp[i] << endl;
    }
    cout << endl;

    // 任意の2つの接尾辞の最長共通接頭辞 (LCP) を O(1) で取得
    int i = 0, j = 7; // "abracadabra" (i=0) と "abra" (j=7)
    cout << "LCP of s[" << i << "..] and s[" << j << "..]: " 
         << sa_str.get_lcp(i, j) << " (Expected: 4)" << endl;
    
    int i2 = 1, j2 = 8; // "bracadabra" (i2=1) と "bra" (j2=8)
    cout << "LCP of s[" << i2 << "..] and s[" << j2 << "..]: " 
         << sa_str.get_lcp(i2, j2) << " (Expected: 3)" << endl;
    cout << endl;

    // ====================================================
    // 2. 数値配列 (vector) に対する Suffix Array
    // ====================================================
    cout << "=== 2. 数値配列 ({2, 1, 3, 1, 2}) ===" << endl;
    vector<int> v = {2, 1, 3, 1, 2};
    SuffixArray<int> sa_vec(v, true);

    cout << "index: sa[i] | suffix array elements" << endl;
    for (int idx = 0; idx < sa_vec.n; ++idx) {
        cout << idx << ": " << sa_vec.sa[idx] << " | {";
        for (int k = sa_vec.sa[idx]; k < sa_vec.n; ++k) {
            cout << v[k] << (k == sa_vec.n - 1 ? "" : ", ");
        }
        cout << "}" << endl;
    }
    cout << endl;

    cout << "LCP of v[0..] ({2, 1, 3, 1, 2}) and v[4..] ({2}): " 
         << sa_vec.get_lcp(0, 4) << " (Expected: 1)" << endl;

    return 0;
}
