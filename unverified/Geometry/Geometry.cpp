#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

using ll = long long;

namespace geometry {

/**
 * @brief 任意精度（オーバーフローを除き）有理数型
 *
 * 分子・分母を __int128_t で保持することで、一般的な幾何クエリにおいて
 * 浮動小数点数（double）による誤差を完全に排除した厳密な計算を行います。
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
    if (num == 0 && den == 0) {
      // 0/0
    } else if (den == 0) {
      num = (num > 0 ? 1 : -1);
    } else if (num == 0) {
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

struct Point {
  Real x, y;
  Point() : x(0), y(0) {}
  Point(Real x, Real y) : x(x), y(y) {}

  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  Point operator*(Real k) const { return Point(x * k, y * k); }
  Point operator/(Real k) const { return Point(x / k, y / k); }

  bool operator<(const Point& p) const {
    return x == p.x ? y < p.y : x < p.x;
  }
  bool operator==(const Point& p) const {
    return x == p.x && y == p.y;
  }
  bool operator!=(const Point& p) const {
    return !(*this == p);
  }
};

using Vector = Point;

struct Line {
  Point a, b;
  Line() = default;
  Line(Point a, Point b) : a(a), b(b) {}

  // 傾きを Rational で取得する (垂直な場合は分母 0 の無限大を返す)
  Real slope() const {
    return (b.y - a.y) / (b.x - a.x);
  }

  // 傾きを double で取得する (垂直な場合は inf / -inf を返す)
  double slope_double() const {
    return (double)slope();
  }

  // 垂直（Y軸に平行）かどうか
  bool is_vertical() const {
    return b.x - a.x == 0;
  }

  // 水平（X軸に平行）かどうか
  bool is_horizontal() const {
    return b.y - a.y == 0;
  }
};

struct Segment : Line {
  Segment() = default;
  using Line::Line;
};

struct Circle {
  Point c;
  Real r;
  Circle() : c(Point()), r(0) {}
  Circle(Point c, Real r) : c(c), r(r) {}
};

using Polygon = std::vector<Point>;

inline Real dot(const Vector& a, const Vector& b) {
  return a.x * b.x + a.y * b.y;
}

inline Real cross(const Vector& a, const Vector& b) {
  return a.x * b.y - a.y * b.x;
}

inline Real norm(const Vector& a) {
  return a.x * a.x + a.y * a.y;
}

// 距離は無理数になり得るため double を返します
inline double abs(const Vector& a) {
  return std::sqrt((double)norm(a));
}

/**
 * @brief 射影 (点 p から直線 l に下ろした垂線の足)
 */
inline Point projection(const Line& l, const Point& p) {
  Real t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
  return l.a + (l.b - l.a) * t;
}

/**
 * @brief 反射 (直線 l を対称軸として点 p と線対称な点)
 */
inline Point reflection(const Line& l, const Point& p) {
  return p + (projection(l, p) - p) * 2;
}

/**
 * @brief 3点の位置関係 (Counter Clock Wise)
 * @return 1: 反時計回り, -1: 時計回り, 2: c-a-b の順で一直線上, -2: a-b-c の順で一直線上, 0: a-c-b の順で一直線上
 */
inline ll ccw(const Point& a, Point b, Point c) {
  b = b - a;
  c = c - a;
  Real cp = cross(b, c);
  if (cp > 0) return 1;              // COUNTER_CLOCKWISE
  if (cp < 0) return -1;             // CLOCKWISE
  if (dot(b, c) < 0) return 2;       // ONLINE_BACK (c-a-b)
  if (norm(b) < norm(c)) return -2;  // ONLINE_FRONT (a-b-c)
  return 0;                          // ON_SEGMENT (a-c-b)
}

/**
 * @brief 点 p と直線 l の距離を求める
 */
inline double distance_lp(const Line& l, const Point& p) {
  return std::abs((double)cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
}

/**
 * @brief 点 p と線分 s の距離を求める
 */
inline double distance_sp(const Segment& s, const Point& p) {
  if (dot(s.b - s.a, p - s.a) < 0) return abs(p - s.a);
  if (dot(s.a - s.b, p - s.b) < 0) return abs(p - s.b);
  return distance_lp(s, p);
}

/**
 * @brief 線分 s1 と s2 の交差判定を行う
 */
inline bool intersect_ss(const Segment& s1, const Segment& s2) {
  return (ccw(s1.a, s1.b, s2.a) * ccw(s1.a, s1.b, s2.b) <= 0 &&
          ccw(s2.a, s2.b, s1.a) * ccw(s2.a, s2.b, s1.b) <= 0);
}

/**
 * @brief 線分 s1 と s2 の距離を求める
 */
inline double distance_ss(const Segment& s1, const Segment& s2) {
  if (intersect_ss(s1, s2)) return 0.0;
  return std::min({distance_sp(s1, s2.a), distance_sp(s1, s2.b),
                   distance_sp(s2, s1.a), distance_sp(s2, s1.b)});
}

/**
 * @brief 直線 l1 と l2 の交点を求める (平行でないことが前提)
 */
inline Point crosspoint_ll(const Line& l1, const Line& l2) {
  Real d1 = cross(l1.b - l1.a, l2.b - l2.a);
  Real d2 = cross(l1.b - l1.a, l1.b - l2.a);
  if (d1 == 0 && d2 == 0) return l2.a;
  assert(d1 != 0);  // 平行でないこと
  return l2.a + (l2.b - l2.a) * (d2 / d1);
}

/**
 * @brief 三角形の重心 (Centroid) を求める
 */
inline Point centroid(const Point& a, const Point& b, const Point& c) {
  return (a + b + c) / 3;
}

/**
 * @brief 有理数座標とは限らない（実数型の）点
 */
struct PointDouble {
  double x, y;
  PointDouble() : x(0), y(0) {}
  PointDouble(double x, double y) : x(x), y(y) {}
};

/**
 * @brief 三角形の内心 (Incenter) を求める (距離計算を含むため実数を返します)
 */
inline PointDouble incenter(const Point& a, const Point& b, const Point& c) {
  double bc = abs(b - c);
  double ca = abs(c - a);
  double ab = abs(a - b);
  double ax = (double)a.x, ay = (double)a.y;
  double bx = (double)b.x, by = (double)b.y;
  double cx = (double)c.x, cy = (double)c.y;
  return PointDouble(
      (ax * bc + bx * ca + cx * ab) / (bc + ca + ab),
      (ay * bc + by * ca + cy * ab) / (bc + ca + ab));
}

/**
 * @brief 三角形の外心 (Circumcenter) を求める
 */
inline Point circumcenter(const Point& a, const Point& b, const Point& c) {
  Real d1 = dot(a - b, a - c);
  Real d2 = dot(b - a, b - c);
  Real d3 = dot(c - a, c - b);
  Real c1 = d2 * d3;
  Real c2 = d3 * d1;
  Real c3 = d1 * d2;
  Real sum = c1 + c2 + c3;
  if (sum == 0) {
    return centroid(a, b, c);  // 一直線上の場合のフォールバック
  }
  Point p1 = (b + c) / 2;
  Point p2 = (c + a) / 2;
  Point p3 = (a + b) / 2;
  return (p1 * c1 + p2 * c2 + p3 * c3) / sum;
}

/**
 * @brief 三角形の垂心 (Orthocenter) を求める
 */
inline Point orthocenter(const Point& a, const Point& b, const Point& c) {
  return a + b + c - circumcenter(a, b, c) * 2;
}

/**
 * @brief 三角形の傍心 (Excenter) を3つすべて求める (距離計算を含むため実数を返します)
 * @return std::vector<PointDouble> サイズ3の傍心配列 (0: Aの対面, 1: Bの対面, 2: Cの対面)
 */
inline std::vector<PointDouble> excenter(const Point& a, const Point& b, const Point& c) {
  double bc = abs(b - c);
  double ca = abs(c - a);
  double ab = abs(a - b);
  double ax = (double)a.x, ay = (double)a.y;
  double bx = (double)b.x, by = (double)b.y;
  double cx = (double)c.x, cy = (double)c.y;
  std::vector<PointDouble> res(3);
  res[0] = PointDouble(
      (ax * (-bc) + bx * ca + cx * ab) / (-bc + ca + ab),
      (ay * (-bc) + by * ca + cy * ab) / (-bc + ca + ab));
  res[1] = PointDouble(
      (ax * bc + bx * (-ca) + cx * ab) / (bc - ca + ab),
      (ay * bc + by * (-ca) + cy * ab) / (bc - ca + ab));
  res[2] = PointDouble(
      (ax * bc + bx * ca + cx * (-ab)) / (bc + ca - ab),
      (ay * bc + by * ca + cy * (-ab)) / (bc + ca - ab));
  return res;
}

/**
 * @brief 多角形の面積を求める
 */
inline Real polygon_area(const Polygon& poly) {
  Real area = 0;
  ll n = poly.size();
  for (ll i = 0; i < n; i++) {
    area += cross(poly[i], poly[(i + 1) % n]);
  }
  if (area < 0) area = -area;
  return area / 2;
}

/**
 * @brief 点群の凸包 (Convex Hull) を求める (Andrew's Monotone Chain)
 */
inline Polygon convex_hull(Polygon ps) {
  ll n = ps.size(), k = 0;
  if (n <= 2) return ps;
  std::sort(ps.begin(), ps.end());
  Polygon ch(2 * n);
  for (ll i = 0; i < n; ch[k++] = ps[i++]) {
    while (k >= 2 && cross(ch[k - 1] - ch[k - 2], ps[i] - ch[k - 1]) <= 0) k--;
  }
  for (ll i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--]) {
    while (k >= t && cross(ch[k - 1] - ch[k - 2], ps[i] - ch[k - 1]) <= 0) k--;
  }
  ch.resize(k - 1);
  return ch;
}

}  // namespace geometry
using namespace geometry;
