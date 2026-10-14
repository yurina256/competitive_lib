#include <iostream>
#include "Dinic.cpp"

using namespace std;

int main() {
    cout << "=== Dinic Maximum Flow Example ===" << endl;
    // 0 -> 1 (cap 10), 0 -> 2 (cap 10)
    // 1 -> 2 (cap 1), 1 -> 3 (cap 10)
    // 2 -> 3 (cap 10)
    Dinic<int> dinic(4);
    dinic.add_edge(0, 1, 10);
    dinic.add_edge(0, 2, 10);
    dinic.add_edge(1, 2, 1);
    dinic.add_edge(1, 3, 10);
    dinic.add_edge(2, 3, 10);

    int flow = dinic.max_flow(0, 3);
    cout << "Max Flow from 0 to 3: " << flow << " (Expected: 20)" << endl;

    return 0;
}

/*
出力結果:
=== Dinic Maximum Flow Example ===
Max Flow from 0 to 3: 20 (Expected: 20)
*/
