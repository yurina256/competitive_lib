#include <iostream>
#include <vector>
#include "WarshallFloyd.cpp"

using namespace std;

int main() {
    cout << "=== Warshall-Floyd Example ===" << endl;

    int n = 4;
    vector<vector<pair<long long, long long>>> graph(n);
    // 0 -> 1 (cost 1)
    graph[0].push_back({1, 1});
    // 1 -> 2 (cost 2)
    graph[1].push_back({2, 2});
    // 0 -> 2 (cost 5)
    graph[0].push_back({2, 5});
    // 2 -> 3 (cost 1)
    graph[2].push_back({3, 1});

    vector<vector<long long>> dist(n, vector<long long>(n, WF_INF));
    vector<vector<long long>> prev(n, vector<long long>(n, -1));

    // 初期化
    warshall_floyd_init(dist, graph, prev);

    // 実行
    warshall_floyd(dist, prev);

    // 最短距離の出力
    cout << "Shortest distances:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == WF_INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    // 0 -> 3 への経路復元
    cout << "Path reconstruction (0 -> 3):" << endl;
    int start = 0, goal = 3;
    if (dist[start][goal] == WF_INF) {
        cout << "No path found." << endl;
    } else {
        vector<int> path;
        for (int cur = goal; cur != start; cur = prev[start][cur]) {
            path.push_back(cur);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}

/*
出力結果:
=== Warshall-Floyd Example ===
Shortest distances:
0 1 3 4 
INF 0 2 3 
INF INF 0 1 
INF INF INF 0 

Path reconstruction (0 -> 3):
0 -> 1 -> 2 -> 3
*/
