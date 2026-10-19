#include <iostream>
#include <vector>
#include "BellmanFord.cpp"

using namespace std;

int main() {
    cout << "=== Bellman-Ford Example ===" << endl;

    // 1. 負辺はあるが負閉路はないグラフ
    int n = 4;
    vector<vector<pair<long long, long long>>> g1(n);
    g1[0].push_back({1, 4});
    g1[0].push_back({2, 5});
    g1[1].push_back({2, -2}); // 負辺: 0 -> 1 -> 2 のコストが 4 + (-2) = 2 になる
    g1[2].push_back({3, 3});

    auto dist1 = bellman_ford(g1, 0);
    cout << "1. Graph without negative cycle (from 0):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "To " << i << ": " << dist1[i] << endl;
    }
    cout << "Has negative cycle anywhere? " << (has_negative_cycle(g1) ? "Yes" : "No") << endl;
    cout << endl;

    // 2. 負閉路があり、一部の頂点のみがその影響を受けるグラフ
    // 0 -> 1 -> 2 -> 1 (1と2でコスト -1 の負閉路)、2 -> 3、0 -> 4 (4は負閉路の影響を受けない)
    int n2 = 5;
    vector<vector<pair<long long, long long>>> g2(n2);
    g2[0].push_back({1, 2});
    g2[1].push_back({2, -3});
    g2[2].push_back({1, 2});  // 1 -> 2 -> 1 の合計コストが -1 (負閉路)
    g2[2].push_back({3, 5});  // 負閉路から到達可能
    g2[0].push_back({4, 10}); // 負閉路を通らず到達可能

    auto dist2 = bellman_ford(g2, 0);
    cout << "2. Graph with negative cycle (from 0):" << endl;
    for (int i = 0; i < n2; ++i) {
        cout << "To " << i << ": ";
        if (dist2[i] == BF_INF) cout << "INF (Unreachable)" << endl;
        else if (dist2[i] == -BF_INF) cout << "-INF (Negative cycle)" << endl;
        else cout << dist2[i] << endl;
    }
    cout << "Has negative cycle anywhere? " << (has_negative_cycle(g2) ? "Yes" : "No") << endl;

    return 0;
}

/*
出力結果:
=== Bellman-Ford Example ===
1. Graph without negative cycle (from 0):
To 0: 0
To 1: 4
To 2: 2
To 3: 5
Has negative cycle anywhere? No

2. Graph with negative cycle (from 0):
To 0: 0
To 1: -INF (Negative cycle)
To 2: -INF (Negative cycle)
To 3: -INF (Negative cycle)
To 4: 10
Has negative cycle anywhere? Yes
*/
