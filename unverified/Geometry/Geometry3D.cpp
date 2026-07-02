#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>

namespace geometry3d {

using Real = double;
const Real EPS = 1e-9;

inline bool eq(Real a, Real b) { return std::abs(a - b) < EPS; }

struct Point3D {
  Real x, y, z;
  Point3D() : x(0), y(0), z(0) {}
  Point3D(Real x, Real y, Real z) : x(x), y(y), z(z) {}

  Point3D operator+(const Point3D& p) const { return Point3D(x + p.x, y + p.y, z + p.z); }
  Point3D operator-(const Point3D& p) const { return Point3D(x - p.x, y - p.y, z - p.z); }
  Point3D operator*(Real k) const { return Point3D(x * k, y * k, z * k); }
  Point3D operator/(Real k) const { return Point3D(x / k, y / k, z / k); }

  bool operator==(const Point3D& p) const {
    return eq(x, p.x) && eq(y, p.y) && eq(z, p.z);
  }
};

using Vector3D = Point3D;

struct Line3D {
  Point3D a, b;
  Line3D() = default;
  Line3D(Point3D a, Point3D b) : a(a), b(b) {}
};

struct Segment3D : Line3D {
  Segment3D() = default;
  using Line3D::Line3D;
};

/**
 * @brief 平面を表す構造体 (ax + by + cz + d = 0)
 */
struct Plane {
  Vector3D n; // 法線ベクトル
  Real d;     // 原点との距離に関する定数 (d = -dot(n, p))
  Plane() = default;
  Plane(Vector3D n, Real d) : n(n), d(d) {}
  
  /**
   * @brief 一直線上にない3点 p1, p2, p3 から平面を決定する
   */
  Plane(Point3D p1, Point3D p2, Point3D p3) {
    Vector3D v1 = p2 - p1;
    Vector3D v2 = p3 - p1;
    Vector3D cross_v = Vector3D(v1.y * v2.z - v1.z * v2.y,
                                v1.z * v2.x - v1.x * v2.z,
                                v1.x * v2.y - v1.y * v2.x);
    Real len = std::sqrt(cross_v.x * cross_v.x + cross_v.y * cross_v.y + cross_v.z * cross_v.z);
    assert(!eq(len, 0)); // 3点が一直線上にないこと
    n = cross_v / len;
    d = -(n.x * p1.x + n.y * p1.y + n.z * p1.z);
  }
};

inline Real dot(const Vector3D& a, const Vector3D& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief 3次元ベクトルの外積を求める (結果はベクトル)
 */
inline Vector3D cross(const Vector3D& a, const Vector3D& b) {
  return Vector3D(a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x);
}

inline Real norm(const Vector3D& a) {
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

inline Real abs(const Vector3D& a) {
  return std::sqrt(norm(a));
}

/**
 * @brief 点 p から直線 l に下ろした垂線の足 (投影) を求める
 */
inline Point3D projection_line(const Line3D& l, const Point3D& p) {
  Real t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
  return l.a + (l.b - l.a) * t;
}

/**
 * @brief 点 p から平面 plane に下ろした垂線の足 (投影) を求める
 */
inline Point3D projection_plane(const Plane& plane, const Point3D& p) {
  Real dist = dot(plane.n, p) + plane.d;
  return p - plane.n * dist;
}

/**
 * @brief 点 p と直線 l の最短距離を求める
 */
inline Real distance_lp(const Line3D& l, const Point3D& p) {
  return abs(cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
}

/**
 * @brief 点 p と線分 s の最短距離を求める
 */
inline Real distance_sp(const Segment3D& s, const Point3D& p) {
  if (dot(s.b - s.a, p - s.a) < 0) return abs(p - s.a);
  if (dot(s.a - s.b, p - s.b) < 0) return abs(p - s.b);
  return distance_lp(s, p);
}

/**
 * @brief 点 p と平面 plane の最短距離を求める
 */
inline Real distance_pp(const Plane& plane, const Point3D& p) {
  return std::abs(dot(plane.n, p) + plane.d);
}

} // namespace geometry3d
