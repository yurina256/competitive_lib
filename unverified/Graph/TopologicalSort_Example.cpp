#include <iostream>
#include <vector>
#include "TopologicalSort.cpp"

using namespace std;

int main() {
    cout << "=== Topological Sort Example ===" << endl;
    // 0 -> 1 -> 3
    // 0 -> 2 -> 3
    int n = 4;
    vector<vector<ll>> g(n);
    g[0].push_back(1);
    g[0].push_back(2);
    g[1].push_back(3);
    g[2].push_back(3);

    vector<ll> order;
    bool success = topological_sort(g, order);
    cout << "Topological Sort possible: " << (success ? "yes" : "no") << " (Expected: yes)" << endl;
    cout << "Order: ";
    for (ll x : order) cout << x << " ";
    cout << endl;

    return 0;
}

/*
出力結果:
=== Topological Sort Example ===
Topological Sort possible: yes (Expected: yes)
Order: 0 1 2 3 
*/
