#include <iostream>
#include "MinCostFlow.cpp"

using namespace std;

int main() {
    cout << "=== Min Cost Flow Example ===" << endl;
    // 0 -> 1 (cap 2, cost 1)
    // 0 -> 2 (cap 1, cost 2)
    // 1 -> 2 (cap 1, cost 1)
    // 1 -> 3 (cap 1, cost 3)
    // 2 -> 3 (cap 2, cost 1)
    MinCostFlow<int, int> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 1);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    // 流量 2 を送る最小コスト
    // 合計コスト = 6
    int cost = mcf.min_cost_flow(0, 3, 2);
    cout << "Min Cost for flow 2: " << cost << " (Expected: 6)" << endl;

    return 0;
}

/*
出力結果:
=== Min Cost Flow Example ===
Min Cost for flow 2: 6 (Expected: 6)
*/
