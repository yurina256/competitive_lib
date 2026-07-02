#include <iostream>
#include <vector>
#include "EulerTour.cpp"

using namespace std;

int main() {
    cout << "=== Euler Tour Example ===" << endl;

    // 木構造の作成
    // 0 - 1
    // 0 - 2
    // 2 - 3
    int n = 4;
    vector<vector<long long>> g(n);
    g[0].push_back(1); g[1].push_back(0);
    g[0].push_back(2); g[2].push_back(0);
    g[2].push_back(3); g[3].push_back(2);

    EulerTour et(g, 0);

    cout << "Vertex | In Index (index) | Out Index (rev_index) | Depth" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << "      | " << et.index[i] << "                | " << et.rev_index[i] << "                    | " << et.d[i] << endl;
    }
    cout << endl;

    // 部分木クエリは [index[v], rev_index[v]) の区間クエリに対応します
    cout << "Subtree query range for vertex 2:" << endl;
    cout << "Range: [" << et.index[2] << ", " << et.rev_index[2] << ")" << endl;
    cout << "Expected elements in subtree 2 (by index range): ";
    for (int i = 0; i < n; ++i) {
        if (et.index[i] >= et.index[2] && et.index[i] < et.rev_index[2]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}

/*
出力結果:
=== Euler Tour Example ===
Vertex | In Index (index) | Out Index (rev_index) | Depth
--------------------------------------------------------
0      | 0                | 7                    | 1
1      | 5                | 6                    | 2
2      | 1                | 4                    | 2
3      | 2                | 3                    | 3

Subtree query range for vertex 2:
Range: [1, 4)
Expected elements in subtree 2 (by index range): 2 3 
*/
