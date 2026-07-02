#include <iostream>
#include <iomanip>
#include "Geometry.cpp"

using namespace std;
using namespace geometry;

int main() {
    cout << "=== Geometry Library Example ===" << endl;
    cout << fixed << setprecision(6);

    // 3頂点：(0, 0), (4, 0), (0, 3) の直角三角形
    Point A(0, 0);
    Point B(4, 0);
    Point C(0, 3);

    // 1. 点と直線・線分の距離
    Line AB_line(A, B);
    Point P(2, 5);
    cout << "Distance (Line AB to P(2,5)): " << distance_lp(AB_line, P) << " (Expected: 5.000000)" << endl;

    Segment AB_seg(A, B);
    Point Q(6, 0);
    cout << "Distance (Segment AB to Q(6,0)): " << distance_sp(AB_seg, Q) << " (Expected: 2.000000)" << endl;
    cout << endl;

    // 2. 三角形の五心
    Point cen = centroid(A, B, C);
    Point inc = incenter(A, B, C);
    Point cc = circumcenter(A, B, C);
    Point orth = orthocenter(A, B, C);
    auto exc = excenter(A, B, C);

    cout << "Centroid:     (" << cen.x << ", " << cen.y << ") (Expected: (1.333333, 1.000000))" << endl;
    cout << "Incenter:     (" << inc.x << ", " << inc.y << ") (Expected: (1.000000, 1.000000))" << endl;
    cout << "Circumcenter: (" << cc.x << ", " << cc.y << ") (Expected: (2.000000, 1.500000))" << endl;
    cout << "Orthocenter:  (" << orth.x << ", " << orth.y << ") (Expected: (0.000000, 0.000000))" << endl;
    cout << "Excenters: " << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "  Excenter " << i << ": (" << exc[i].x << ", " << exc[i].y << ")" << endl;
    }
    cout << endl;

    // 3. 多角形の面積
    Polygon poly = {A, B, C};
    cout << "Area of Triangle ABC: " << polygon_area(poly) << " (Expected: 6.000000)" << endl;
    cout << endl;

    // 4. 凸包
    Polygon points = {Point(0,0), Point(2,0), Point(1,1), Point(0,2), Point(2,2), Point(1,0.5)};
    Polygon hull = convex_hull(points);
    cout << "Convex Hull Vertices:" << endl;
    for (const auto& pt : hull) {
        cout << "  (" << pt.x << ", " << pt.y << ")" << endl;
    }

    return 0;
}

/*
出力結果:
=== Geometry Library Example ===
Distance (Line AB to P(2,5)): 5.000000 (Expected: 5.000000)
Distance (Segment AB to Q(6,0)): 2.000000 (Expected: 2.000000)

Centroid:     (1.333333, 1.000000) (Expected: (1.333333, 1.000000))
Incenter:     (1.000000, 1.000000) (Expected: (1.000000, 1.000000))
Circumcenter: (2.000000, 1.500000) (Expected: (2.000000, 1.500000))
Orthocenter:  (0.000000, 0.000000) (Expected: (0.000000, 0.000000))
Excenters: 
  Excenter 0: (-2.000000, 2.000000)
  Excenter 1: (6.000000, 3.000000)
  Excenter 2: (2.000000, -2.000000)

Area of Triangle ABC: 6.000000 (Expected: 6.000000)

Convex Hull Vertices:
  (0.000000, 0.000000)
  (2.000000, 0.000000)
  (2.000000, 2.000000)
  (0.000000, 2.000000)
*/
