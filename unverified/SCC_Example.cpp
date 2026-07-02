#include <iostream>
#include <vector>
#include "SCC.cpp"

using namespace std;

int main() {
    cout << "=== SCC Example ===" << endl;
    // 0 -> 1 -> 2 -> 0
    // 2 -> 3
    int n = 4;
    SCC scc(n);
    scc.add_edge(0, 1);
    scc.add_edge(1, 2);
    scc.add_edge(2, 0);
    scc.add_edge(2, 3);

    scc.build();
    cout << "Component of 0: " << scc[0] << endl;
    cout << "Component of 1: " << scc[1] << endl;
    cout << "Component of 2: " << scc[2] << endl;
    cout << "Component of 3: " << scc[3] << endl;
    cout << "scc[0] == scc[2]: " << (scc[0] == scc[2] ? "true" : "false") << " (Expected: true)" << endl;
    cout << "scc[2] == scc[3]: " << (scc[2] == scc[3] ? "true" : "false") << " (Expected: false)" << endl;

    return 0;
}
