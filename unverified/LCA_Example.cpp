#include <iostream>
#include <vector>
#include "LCA.cpp"

using namespace std;

int main() {
    cout << "=== LCA Example ===" << endl;
    // 0 - 1
    // 0 - 2
    // 2 - 3
    // 2 - 4
    int n = 5;
    vector<vector<long long>> g(n);
    g[0].push_back(1); g[1].push_back(0);
    g[0].push_back(2); g[2].push_back(0);
    g[2].push_back(3); g[3].push_back(2);
    g[2].push_back(4); g[4].push_back(2);

    LCA lca(g, 0);
    cout << "LCA of 3 and 4: " << lca.query(3, 4) << " (Expected: 2)" << endl;
    cout << "LCA of 1 and 3: " << lca.query(1, 3) << " (Expected: 0)" << endl;
    cout << "Distance between 1 and 3: " << lca.distance(1, 3) << " (Expected: 3)" << endl;

    return 0;
}
