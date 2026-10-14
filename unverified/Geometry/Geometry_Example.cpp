#include <iostream>
#include <iomanip>
#include <cassert>
#include "Geometry.cpp"

using namespace std;
using namespace geometry;

int main() {
    cout << "=== Geometry Library Example (Rational exact arithmetic) ===" << endl;
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
    Point cen = centroid(A, B, C); // 有理数
    PointDouble inc = incenter(A, B, C); // 実数
    Point cc = circumcenter(A, B, C); // 有理数
    Point orth = orthocenter(A, B, C); // 有理数
    auto exc = excenter(A, B, C); // 実数

    cout << "Centroid:     (" << (double)cen.x << ", " << (double)cen.y << ") (Expected: (1.333333, 1.000000))" << endl;
    cout << "Centroid exact: " << cen.x << ", " << cen.y << " (Expected: 4/3, 1)" << endl;
    cout << "Incenter:     (" << inc.x << ", " << inc.y << ") (Expected: (1.000000, 1.000000))" << endl;
    cout << "Circumcenter: (" << (double)cc.x << ", " << (double)cc.y << ") (Expected: (2.000000, 1.500000))" << endl;
    cout << "Circumcenter exact: " << cc.x << ", " << cc.y << " (Expected: 2, 3/2)" << endl;
    cout << "Orthocenter:  (" << (double)orth.x << ", " << (double)orth.y << ") (Expected: (0.000000, 0.000000))" << endl;
    cout << "Excenters: " << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "  Excenter " << i << ": (" << exc[i].x << ", " << exc[i].y << ")" << endl;
    }
    cout << endl;

    // 3. 多角形の面積
    Polygon poly = {A, B, C};
    cout << "Area of Triangle ABC (exact): " << polygon_area(poly) << " (Expected: 6)" << endl;
    cout << endl;

    // 4. 凸包
    Polygon points = {Point(0,0), Point(2,0), Point(1,1), Point(0,2), Point(2,2), Point(1, Rational(1, 2))};
    Polygon hull = convex_hull(points);
    cout << "Convex Hull Vertices:" << endl;
    for (const auto& pt : hull) {
        cout << "  (" << pt.x << ", " << pt.y << ")" << endl;
    }
    cout << endl;

    // 5. 傾きの検証 (追加された機能のテスト)
    cout << "=== 5. 傾き (Slope) の検証 ===" << endl;
    
    // (1, 1) から (4, 3) への線分 -> 傾き dy/dx = 2/3
    Segment seg1(Point(1, 1), Point(4, 3));
    // (0, 0) から (0, 5) への線分 -> 垂直（傾き無限大）
    Segment seg2(Point(0, 0), Point(0, 5));
    // (0, 0) から (5, 0) への線分 -> 水平（傾き 0）
    Segment seg3(Point(0, 0), Point(5, 0));
    // (0, 0) から (2, -3) への線分 -> 傾き -3/2
    Segment seg4(Point(0, 0), Point(2, -3));

    cout << "Slope 1 (2/3): " << seg1.slope() << " (double: " << seg1.slope_double() << ")" << endl;
    cout << "Slope 2 (inf): " << seg2.slope() << " (double: " << seg2.slope_double() << ")" << endl;
    cout << "Slope 3 (0):   " << seg3.slope() << " (double: " << seg3.slope_double() << ")" << endl;
    cout << "Slope 4 (-1.5):" << seg4.slope() << " (double: " << seg4.slope_double() << ")" << endl;

    cout << "is seg1 vertical?   " << (seg1.is_vertical() ? "Yes" : "No") << endl;
    cout << "is seg2 vertical?   " << (seg2.is_vertical() ? "Yes" : "No") << endl;
    cout << "is seg3 horizontal? " << (seg3.is_horizontal() ? "Yes" : "No") << endl;

    // 傾きの大小比較テスト (有理数として正しく比較されるか)
    // 期待される順序: -3/2 (seg4) < 0 (seg3) < 2/3 (seg1) < inf (seg2)
    assert(seg4.slope() < seg3.slope());
    assert(seg3.slope() < seg1.slope());
    assert(seg1.slope() < seg2.slope());
    
    cout << "Slope comparison assert checks passed!" << endl;

    return 0;
}

/*
出力結果:
=== Geometry Library Example (Rational exact arithmetic) ===
Distance (Line AB to P(2,5)): 5.000000 (Expected: 5.000000)
Distance (Segment AB to Q(6,0)): 2.000000 (Expected: 2.000000)

Centroid:     (1.333333, 1.000000) (Expected: (1.333333, 1.000000))
Centroid exact: 4/3, 1 (Expected: 4/3, 1)
Incenter:     (1.000000, 1.000000) (Expected: (1.000000, 1.000000))
Circumcenter: (2.000000, 1.500000) (Expected: (2.000000, 1.500000))
Circumcenter exact: 2, 3/2 (Expected: 2, 3/2)
Orthocenter:  (0.000000, 0.000000) (Expected: (0.000000, 0.000000))
Excenters: 
  Excenter 0: (6.000000, 6.000000)
  Excenter 1: (-2.000000, 2.000000)
  Excenter 2: (3.000000, -3.000000)

Area of Triangle ABC (exact): 6 (Expected: 6)

Convex Hull Vertices:
  (0, 0)
  (2, 0)
  (2, 2)
  (0, 2)

=== 5. 傾き (Slope) の検証 ===
Slope 1 (2/3): 2/3 (double: 0.666667)
Slope 2 (inf): 1/0 (double: inf)
Slope 3 (0):   0 (double: 0.000000)
Slope 4 (-1.5):-3/2 (double: -1.500000)
is seg1 vertical?   No
is seg2 vertical?   Yes
is seg3 horizontal? Yes
Slope comparison assert checks passed!
*/
