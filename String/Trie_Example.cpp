#include <iostream>
#include "Trie.cpp"

using namespace std;

int main() {
    cout << "=== Trie (Trie Tree) Example ===" << endl;

    Trie trie;

    // 単語の挿入
    cout << "Inserting: 'apple', 'app', 'banana'" << endl;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    // 完全一致検索
    cout << "\nExact counts:" << endl;
    cout << "Exact count of 'apple': " << trie.count_exact("apple") << " (Expected: 1)" << endl;
    cout << "Exact count of 'app': " << trie.count_exact("app") << " (Expected: 1)" << endl;
    cout << "Exact count of 'ap': " << trie.count_exact("ap") << " (Expected: 0)" << endl;

    // 接頭辞検索
    cout << "\nPrefix counts:" << endl;
    cout << "Prefix count of 'ap' (starts with 'ap'): " << trie.count_prefix("ap") << " (Expected: 2, 'apple' and 'app')" << endl;
    cout << "Prefix count of 'b' (starts with 'b'): " << trie.count_prefix("b") << " (Expected: 1, 'banana')" << endl;
    cout << "Prefix count of 'cat' (starts with 'cat'): " << trie.count_prefix("cat") << " (Expected: 0)" << endl;

    return 0;
}

/*
出力結果:
=== Trie (Trie Tree) Example ===
Inserting: 'apple', 'app', 'banana'

Exact counts:
Exact count of 'apple': 1 (Expected: 1)
Exact count of 'app': 1 (Expected: 1)
Exact count of 'ap': 0 (Expected: 0)

Prefix counts:
Prefix count of 'ap' (starts with 'ap'): 2 (Expected: 2, 'apple' and 'app')
Prefix count of 'b' (starts with 'b'): 1 (Expected: 1, 'banana')
Prefix count of 'cat' (starts with 'cat'): 0 (Expected: 0)
*/
