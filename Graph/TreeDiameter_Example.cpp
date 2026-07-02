#include <iostream>
#include <vector>
#include "TreeDiameter.cpp"

using namespace std;

int main() {
    cout << "=== Tree Diameter Example ===" << endl;

    int n = 4;
    // 1. 重み付き無向木の作成
    // 0 - 1 (cost 10)
    // 1 - 2 (cost 20)
    // 2 - 3 (cost 5)
    // 木のパス: 0-1-2-3 (直径 = 10 + 20 + 5 = 35)
    vector<vector<pair<long long, long long>>> graph_weighted(n);
    graph_weighted[0].push_back({1, 10});
    graph_weighted[1].push_back({0, 10});
    graph_weighted[1].push_back({2, 20});
    graph_weighted[2].push_back({1, 20});
    graph_weighted[2].push_back({3, 5});
    graph_weighted[3].push_back({2, 5});

    long long diameter_w = tree_diameter_weighted(graph_weighted);
    cout << "Weighted Tree Diameter: " << diameter_w << " (Expected: 35)" << endl;

    // 2. 重みなし無向木の作成
    // 0 - 1
    // 1 - 2
    // 2 - 3
    // 木のパス: 0-1-2-3 (直径 = 3)
    vector<vector<long long>> graph_unweighted(n);
    graph_unweighted[0].push_back(1);
    graph_unweighted[1].push_back(0);
    graph_unweighted[1].push_back(2);
    graph_unweighted[2].push_back(1);
    graph_unweighted[2].push_back(3);
    graph_unweighted[3].push_back(2);

    long long diameter_u = tree_diameter(graph_unweighted);
    cout << "Unweighted Tree Diameter: " << diameter_u << " (Expected: 3)" << endl;

    return 0;
}

/*
出力結果:
=== Tree Diameter Example ===
Weighted Tree Diameter: 35 (Expected: 35)
Unweighted Tree Diameter: 3 (Expected: 3)
*/
