#include <iostream>
#include <iomanip>
#include "Geometry3D.cpp"

using namespace std;
using namespace geometry3d;

int main() {
    cout << "=== 3D Geometry Library Example (Rational exact arithmetic) ===" << endl;
    cout << fixed << setprecision(6);

    // 平面 Z=0 を3点 (0,0,0), (1,0,0), (0,1,0) で定義
    Point3D p1(0, 0, 0);
    Point3D p2(1, 0, 0);
    Point3D p3(0, 1, 0);
    Plane xy_plane(p1, p2, p3);

    // テスト点 P(2, 3, 5)
    Point3D P(2, 3, 5);

    // 1. 平面への射影・距離
    Point3D proj_p = projection_plane(xy_plane, P);
    cout << "Plane Normal Vector (exact): (" << xy_plane.n.x << ", " << xy_plane.n.y << ", " << xy_plane.n.z << ")" << endl;
    cout << "Projection of P(2,3,5) onto XY-plane exact: (" << proj_p.x << ", " << proj_p.y << ", " << proj_p.z << ") (Expected: (2, 3, 0))" << endl;
    cout << "Distance from P(2,3,5) to XY-plane: " << distance_pp(xy_plane, P) << " (Expected: 5.000000)" << endl;
    cout << endl;

    // 2. 直線への射影・距離
    // 直線 L: A(0,0,0) と B(1,1,1) を通る
    Point3D A(0, 0, 0);
    Point3D B(1, 1, 1);
    Line3D L(A, B);
    
    // 点 C(1, 0, 0)
    Point3D C(1, 0, 0);
    Point3D proj_l = projection_line(L, C);
    cout << "Projection of C(1,0,0) onto Line L exact: (" << proj_l.x << ", " << proj_l.y << ", " << proj_l.z << ") (Expected: (1/3, 1/3, 1/3))" << endl;
    cout << "Distance from C(1,0,0) to Line L: " << distance_lp(L, C) << " (Expected: 0.816497)" << endl;

    return 0;
}

/*
出力結果:
=== 3D Geometry Library Example (Rational exact arithmetic) ===
Plane Normal Vector (exact): (0, 0, 1)
Projection of P(2,3,5) onto XY-plane exact: (2, 3, 0) (Expected: (2, 3, 0))
Distance from P(2,3,5) to XY-plane: 5.000000 (Expected: 5.000000)

Projection of C(1,0,0) onto Line L exact: (1/3, 1/3, 1/3) (Expected: (1/3, 1/3, 1/3))
Distance from C(1,0,0) to Line L: 0.816497 (Expected: 0.816497)
*/
