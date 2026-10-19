#include <iostream>
#include "UnionFind.cpp"

using namespace std;

int main() {
    cout << "=== UnionFind Example ===" << endl;
    
    // 5要素のUnionFindを作成 (0, 1, 2, 3, 4)
    UnionFind uf(5);

    cout << "Initial checks:" << endl;
    cout << "Same(0, 1)? " << (uf.same(0, 1) ? "Yes" : "No") << endl;
    cout << "Size of 0: " << uf.size(0) << endl;

    // 0 と 1 を併合
    cout << "\nUnite 0 and 1:" << endl;
    uf.unite(0, 1);
    cout << "Same(0, 1)? " << (uf.same(0, 1) ? "Yes" : "No") << endl;
    cout << "Size of 0: " << uf.size(0) << endl;

    // 1 と 2 を併合
    cout << "\nUnite 1 and 2:" << endl;
    uf.unite(1, 2);
    cout << "Same(0, 2)? " << (uf.same(0, 2) ? "Yes" : "No") << endl;
    cout << "Size of 2: " << uf.size(2) << endl;

    // 3 と 4 を併合
    cout << "\nUnite 3 and 4:" << endl;
    uf.unite(3, 4);
    cout << "Same(0, 3)? " << (uf.same(0, 3) ? "Yes" : "No") << endl;

    // 現在のグループ一覧を取得
    cout << "\nGroups:" << endl;
    for (const auto& g : uf.groups()) {
        cout << "{ ";
        for (ll v : g) cout << v << " ";
        cout << "}" << endl;
    }

    // 全体を併合
    cout << "\nUnite 2 and 3:" << endl;
    uf.unite(2, 3);
    cout << "Same(0, 4)? " << (uf.same(0, 4) ? "Yes" : "No") << endl;
    cout << "Size of 0: " << uf.size(0) << endl;

    return 0;
}

/*
出力結果:
=== UnionFind Example ===
Initial checks:
Same(0, 1)? No
Size of 0: 1

Unite 0 and 1:
Same(0, 1)? Yes
Size of 0: 2

Unite 1 and 2:
Same(0, 2)? Yes
Size of 2: 3

Unite 3 and 4:
Same(0, 3)? No

Groups:
{ 0 1 2 }
{ 3 4 }

Unite 2 and 3:
Same(0, 4)? Yes
Size of 0: 5
*/
