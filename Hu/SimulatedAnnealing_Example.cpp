#include "SimulatedAnnealing.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>

struct Point {
    double x, y;
    double dist(const Point& other) const {
        return std::hypot(x - other.x, y - other.y);
    }
};

// TSPの総距離を計算
double calc_total_distance(const std::vector<int>& order, const std::vector<Point>& pts) {
    double d = 0.0;
    int n = order.size();
    for (int i = 0; i < n; ++i) {
        d += pts[order[i]].dist(pts[order[(i + 1) % n]]);
    }
    return d;
}

int main() {
    std::cout << "=== TSP 2-opt による山登り法 & 焼きなまし法の比較 ===" << std::endl;

    // 1. 都市データの生成 (50都市)
    const int N = 50;
    Hu::XorShift rng(12345);
    std::vector<Point> pts(N);
    for (int i = 0; i < N; ++i) {
        pts[i] = {rng.next_double() * 100.0, rng.next_double() * 100.0};
    }

    // 初期解: 0, 1, 2, ..., N-1
    std::vector<int> initial_order(N);
    std::iota(initial_order.begin(), initial_order.end(), 0);
    double initial_dist = calc_total_distance(initial_order, pts);
    std::cout << "初期経路長: " << std::fixed << std::setprecision(2) << initial_dist << std::endl;

    // ---------------------------------------------------------
    // A. 山登り法 (Hill Climbing)
    // ---------------------------------------------------------
    {
        std::vector<int> order = initial_order;
        double current_dist = initial_dist;
        Hu::Timer timer(0.2); // 0.2秒
        auto hc = Hu::AnnealingAcceptor::create_hill_climbing(Hu::AnnealingAcceptor::Objective::Minimize);

        while (!timer.is_time_over()) {
            int i = rng.next_int(N);
            int j = rng.next_int(N);
            if (i > j) std::swap(i, j);
            if (i == j || (i == 0 && j == N - 1)) continue;

            // 2-opt による差分計算
            int u1 = order[i], v1 = order[(i + 1) % N];
            int u2 = order[j], v2 = order[(j + 1) % N];
            double old_edges = pts[u1].dist(pts[v1]) + pts[u2].dist(pts[v2]);
            double new_edges = pts[u1].dist(pts[u2]) + pts[v1].dist(pts[v2]);
            double next_dist = current_dist - old_edges + new_edges;

            if (hc.accept(current_dist, next_dist, timer.progress())) {
                // 遷移を受理: [i+1, j] の区間を反転
                std::reverse(order.begin() + i + 1, order.begin() + j + 1);
                current_dist = next_dist;
            }
        }

        std::cout << "\n[山登り法 結果]" << std::endl;
        std::cout << "最終経路長: " << current_dist << std::endl;
        std::cout << hc.summary();
    }

    // ---------------------------------------------------------
    // B. 焼きなまし法 (Simulated Annealing)
    // ---------------------------------------------------------
    {
        std::vector<int> order = initial_order;
        std::vector<int> best_order = order;
        double current_dist = initial_dist;
        double best_dist = initial_dist;

        Hu::Timer timer(0.2); // 0.2秒
        // 初期温度 20.0 -> 終了温度 0.01 で最小化
        Hu::AnnealingAcceptor sa(20.0, 0.01, Hu::AnnealingAcceptor::Objective::Minimize);

        while (!timer.is_time_over()) {
            int i = rng.next_int(N);
            int j = rng.next_int(N);
            if (i > j) std::swap(i, j);
            if (i == j || (i == 0 && j == N - 1)) continue;

            // 2-opt 差分計算
            int u1 = order[i], v1 = order[(i + 1) % N];
            int u2 = order[j], v2 = order[(j + 1) % N];
            double old_edges = pts[u1].dist(pts[v1]) + pts[u2].dist(pts[v2]);
            double new_edges = pts[u1].dist(pts[u2]) + pts[v1].dist(pts[v2]);
            double next_dist = current_dist - old_edges + new_edges;

            if (sa.accept(current_dist, next_dist, timer.progress())) {
                std::reverse(order.begin() + i + 1, order.begin() + j + 1);
                current_dist = next_dist;

                if (current_dist < best_dist) {
                    best_dist = current_dist;
                    best_order = order;
                }
            }
        }

        std::cout << "\n[焼きなまし法 結果]" << std::endl;
        std::cout << "最良経路長: " << best_dist << std::endl;
        std::cout << sa.summary();
    }

    return 0;
}
