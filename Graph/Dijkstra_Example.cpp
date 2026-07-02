#include <iostream>
#include <vector>
#include "Dijkstra.cpp"

using namespace std;

int main() {
    cout << "=== Dijkstra Example ===" << endl;

    int n = 4;
    // 1. 重み付きダイクストラ用グラフの作成
    vector<vector<pair<long long, long long>>> graph_weighted(n);
    graph_weighted[0].push_back({1, 1}); // 0 -> 1 (cost 1)
    graph_weighted[1].push_back({2, 2}); // 1 -> 2 (cost 2)
    graph_weighted[0].push_back({2, 5}); // 0 -> 2 (cost 5)
    graph_weighted[2].push_back({3, 1}); // 2 -> 3 (cost 1)

    // 0 を始点として実行
    auto dist_w = dijkstra(graph_weighted, 0);

    cout << "Weighted shortest paths from 0:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "To " << i << ": " << dist_w[i] << endl;
    }
    cout << endl;

    // 2. 重みなしダイクストラ用グラフの作成
    vector<vector<long long>> graph_unweighted(n);
    graph_unweighted[0].push_back(1); // 0 -> 1
    graph_unweighted[1].push_back(2); // 1 -> 2
    graph_unweighted[0].push_back(2); // 0 -> 2
    graph_unweighted[2].push_back(3); // 2 -> 3

    // 0 を始点として実行
    auto dist_u = dijkstra_unweighted(graph_unweighted, 0);

    cout << "Unweighted shortest paths from 0 (all edge weights are 1):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "To " << i << ": " << dist_u[i] << endl;
    }

    return 0;
}

/*
出力結果:
=== Dijkstra Example ===
Weighted shortest paths from 0:
To 0: 0
To 1: 1
To 2: 3
To 3: 4

Unweighted shortest paths from 0 (all edge weights are 1):
To 0: 0
To 1: 1
To 2: 1
To 3: 2
*/
