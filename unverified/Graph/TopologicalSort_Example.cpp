#include <iostream>
#include <vector>
#include "TopologicalSort.cpp"

using namespace std;

int main() {
    cout << "=== Topological Sort Example ===" << endl;
    // 0 -> 1 -> 3
    // 0 -> 2 -> 3
    int n = 4;
    vector<vector<int>> g(n);
    g[0].push_back(1);
    g[0].push_back(2);
    g[1].push_back(3);
    g[2].push_back(3);

    vector<int> order;
    bool success = topological_sort(g, order);
    cout << "Topological Sort possible: " << (success ? "yes" : "no") << " (Expected: yes)" << endl;
    cout << "Order: ";
    for (int x : order) cout << x << " ";
    cout << endl;

    return 0;
}
