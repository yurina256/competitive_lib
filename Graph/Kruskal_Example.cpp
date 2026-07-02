#include <iostream>
#include <vector>
#include "Kruskal.cpp"

using namespace std;

int main() {
    cout << "=== Kruskal's Algorithm Example ===" << endl;

    int n = 4;
    vector<vector<pair<long long, long long>>> graph(n);
    // 無向グラフの作成
    // 0 - 1 (cost 10)
    graph[0].push_back({1, 10}); graph[1].push_back({0, 10});
    // 0 - 2 (cost 6)
    graph[0].push_back({2, 6});  graph[2].push_back({0, 6});
    // 0 - 3 (cost 5)
    graph[0].push_back({3, 5});  graph[3].push_back({0, 5});
    // 1 - 3 (cost 15)
    graph[1].push_back({3, 15}); graph[3].push_back({1, 15});
    // 2 - 3 (cost 4)
    graph[2].push_back({3, 4});  graph[3].push_back({2, 4});

    // 1. 最小全域木 (MST)
    vector<vector<pair<long long, long long>>> mst;
    long long mst_cost = kruskal(mst, graph, true);
    cout << "Minimum Spanning Tree Cost: " << mst_cost << " (Expected: 19)" << endl;
    cout << "Chosen edges in MST:" << endl;
    for (int u = 0; u < n; ++u) {
        for (auto [v, cost] : mst[u]) {
            if (u < v) { // 重複出力を防ぐ
                cout << u << " - " << v << " (cost " << cost << ")" << endl;
            }
        }
    }
    cout << endl;

    // 2. 最大全域木 (Maximum Spanning Tree)
    vector<vector<pair<long long, long long>>> max_st;
    long long max_st_cost = kruskal(max_st, graph, false);
    cout << "Maximum Spanning Tree Cost: " << max_st_cost << " (Expected: 31)" << endl;
    cout << "Chosen edges in Maximum Spanning Tree:" << endl;
    for (int u = 0; u < n; ++u) {
        for (auto [v, cost] : max_st[u]) {
            if (u < v) {
                cout << u << " - " << v << " (cost " << cost << ")" << endl;
            }
        }
    }

    return 0;
}

/*
出力結果:
=== Kruskal's Algorithm Example ===
Minimum Spanning Tree Cost: 19 (Expected: 19)
Chosen edges in MST:
0 - 1 (cost 10)
0 - 3 (cost 5)
2 - 3 (cost 4)

Maximum Spanning Tree Cost: 31 (Expected: 31)
Chosen edges in Maximum Spanning Tree:
0 - 1 (cost 10)
0 - 2 (cost 6)
1 - 3 (cost 15)
*/
