#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

namespace geometry3d {

/**
 * @brief 任意精度（オーバーフローを除き）有理数型
 * 
 * 分子・分母を __int128_t で保持し、浮動小数点数（double）による誤差を完全に排除した厳密な計算を行います。
 */
struct Rational {
  using int128 = __int128_t;
  int128 num, den;

  Rational() : num(0), den(1) {}
  Rational(int128 num) : num(num), den(1) {}
  Rational(int128 num, int128 den) : num(num), den(den) { normalize(); }

  static int128 gcd(int128 a, int128 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
      a %= b;
      std::swap(a, b);
    }
    return a;
  }

  void normalize() {
    if (den < 0) {
      num = -num;
      den = -den;
    }
    if (num == 0) {
      den = 1;
    } else {
      int128 g = gcd(num, den);
      num /= g;
      den /= g;
    }
  }

  Rational operator+(const Rational& r) const { return Rational(num * r.den + r.num * den, den * r.den); }
  Rational operator-(const Rational& r) const { return Rational(num * r.den - r.num * den, den * r.den); }
  Rational operator*(const Rational& r) const { return Rational(num * r.num, den * r.den); }
  Rational operator/(const Rational& r) const { return Rational(num * r.den, den * r.num); }

  Rational& operator+=(const Rational& r) { return *this = *this + r; }
  Rational& operator-=(const Rational& r) { return *this = *this - r; }
  Rational& operator*=(const Rational& r) { return *this = *this * r; }
  Rational& operator/=(const Rational& r) { return *this = *this / r; }

  Rational operator-() const { return Rational(-num, den); }

  bool operator<(const Rational& r) const { return num * r.den < r.num * den; }
  bool operator>(const Rational& r) const { return r < *this; }
  bool operator<=(const Rational& r) const { return !(r < *this); }
  bool operator>=(const Rational& r) const { return !(*this < r); }
  bool operator==(const Rational& r) const { return num == r.num && den == r.den; }
  bool operator!=(const Rational& r) const { return !(*this == r); }

  explicit operator double() const { return (double)num / (double)den; }

  friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.den == 1) return os << (long long)r.num;
    return os << (long long)r.num << "/" << (long long)r.den;
  }
};

using Real = Rational;

struct Point3D {
  Real x, y, z;
  Point3D() : x(0), y(0), z(0) {}
  Point3D(Real x, Real y, Real z) : x(x), y(y), z(z) {}

  Point3D operator+(const Point3D& p) const { return Point3D(x + p.x, y + p.y, z + p.z); }
  Point3D operator-(const Point3D& p) const { return Point3D(x - p.x, y - p.y, z - p.z); }
  Point3D operator*(Real k) const { return Point3D(x * k, y * k, z * k); }
  Point3D operator/(Real k) const { return Point3D(x / k, y / k, z / k); }

  bool operator==(const Point3D& p) const {
    return x == p.x && y == p.y && z == p.z;
  }
  bool operator!=(const Point3D& p) const {
    return !(*this == p);
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
 * 
 * 法線ベクトル n は有理数で厳密に管理するため、正規化（単位ベクトル化）は行いません。
 */
struct Plane {
  Vector3D n; // 法線ベクトル (正規化されていない)
  Real d;     // 原点との距離に関する定数 (d = -dot(n, p))
  Plane() = default;
  Plane(Vector3D n, Real d) : n(n), d(d) {}
  
  /**
   * @brief 一直線上にない3点 p1, p2, p3 から平面を決定する (有理数で完結)
   */
  Plane(Point3D p1, Point3D p2, Point3D p3) {
    Vector3D v1 = p2 - p1;
    Vector3D v2 = p3 - p1;
    Vector3D cross_v = Vector3D(v1.y * v2.z - v1.z * v2.y,
                                v1.z * v2.x - v1.x * v2.z,
                                v1.x * v2.y - v1.y * v2.x);
    assert(cross_v.x != 0 || cross_v.y != 0 || cross_v.z != 0); // 3点が一直線上にないこと
    n = cross_v;
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

// 距離は無理数になり得るため double を返します
inline double abs(const Vector3D& a) {
  return std::sqrt((double)norm(a));
}

/**
 * @brief 点 p から直線 l に下ろした垂線の足 (投影) を求める (有理数で完結)
 */
inline Point3D projection_line(const Line3D& l, const Point3D& p) {
  Real t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
  return l.a + (l.b - l.a) * t;
}

/**
 * @brief 点 p から平面 plane に下ろした垂線の足 (投影) を求める (有理数で完結)
 */
inline Point3D projection_plane(const Plane& plane, const Point3D& p) {
  Real dist_factor = (dot(plane.n, p) + plane.d) / norm(plane.n);
  return p - plane.n * dist_factor;
}

/**
 * @brief 点 p と直線 l の最短距離を求める
 */
inline double distance_lp(const Line3D& l, const Point3D& p) {
  return abs(cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
}

/**
 * @brief 点 p と線分 s の最短距離を求める
 */
inline double distance_sp(const Segment3D& s, const Point3D& p) {
  if (dot(s.b - s.a, p - s.a) < 0) return abs(p - s.a);
  if (dot(s.a - s.b, p - s.b) < 0) return abs(p - s.b);
  return distance_lp(s, p);
}

/**
 * @brief 点 p と平面 plane の最短距離を求める
 */
inline double distance_pp(const Plane& plane, const Point3D& p) {
  return std::abs((double)(dot(plane.n, p) + plane.d)) / std::sqrt((double)norm(plane.n));
}

} // namespace geometry3d
