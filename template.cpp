#include <bits/stdc++.h>
#include <atcoder/all>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define int long long
#define ll long long
#define double long double
#define ull unsigned long long
#define ALL(v) (v).begin(), (v).end()
#define NP next_permutation
#define PLL pair<long long, long long>
#define VL vector<long long>
#define VVL vector<vector<long long>>
#define VVVL vector<vector<vector<long long>>>
#define VPLL vector<pair<long long, long long>>
#define STL set<long long>
#define MPLL map<long long, long long>
#define SP fixed << setprecision(12)
#define hashmap unordered_set

constexpr ll inf = 4001001001001001001ll;
constexpr ll mod = /* 1000000007; //*/ 998244353;
constexpr double pi = 3.141592653589793;
constexpr double eps = 0.00000000001;
vector<ll> d8x = {1, 1, 0, -1, -1, -1, 0, 1};
vector<ll> d8y = {0, 1, 1, 1, 0, -1, -1, -1};
vector<ll> d4x = {1, 0, -1, 0};
vector<ll> d4y = {0, 1, 0, -1};
// 小数出力
// cout << setprecision(12);
// struct
typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
struct Ruiseki {
  vector<ll> v;
  Ruiseki(vector<ll>& vec) {
    ll n = vec.size();
    v.resize(n + 1);
    rep(i, n) v[i + 1] = v[i] + vec[i];
  }
  ll get(ll l, ll r) {  // 開区間になりました
    return v[r] - v[l];
  }
};
// max
template <typename T1, typename T2>
inline bool chmax(T1& a, T2 b) { return a < b && (a = b, true); }
// min
template <typename T1, typename T2>
inline bool chmin(T1& a, T2 b) { return a > b && (a = b, true); }
// join
template <typename T>
string join(vector<T>& vec, const string& sp = " ") {
  int si = vec.size();
  if (si == 0) {
    return "";
  } else {
    stringstream ss;
    rep(i, si - 1) {
      ss << vec[i] << sp;
    }
    ss << vec[si - 1];
    return ss.str();
  }
}
// print
template <typename T>
void pr_single(const T& x) {
  if constexpr (requires { x.val(); }) cout << x.val();
  else if constexpr (requires { typename T::value_type; } && !requires { x.substr(0); }) {
    for (int i = 0; i < (int)x.size(); i++) {
      pr_single(x[i]);
      if (i != (int)x.size() - 1) cout << " ";
    }
  } else if constexpr (requires { x.first; x.second; }) {
    pr_single(x.first);
    cout << " ";
    pr_single(x.second);
  } else
    cout << x;
}
void pr() { cout << endl; }
template <typename Head, typename... Tail>
void pr(const Head& head, const Tail&... tail) {
  pr_single(head);
  if constexpr (sizeof...(tail) > 0) {
    cout << " ";
    pr(tail...);
  } else
    cout << endl;
}
// Yes
string Yes(bool x) {
  if (x) return "Yes\n";
  return "No\n";
}
string YES(bool x) {
  if (x) return "YES\n";
  return "NO\n";
}
bool in_range(int l, int x, int r) {  // 閉区間
  return ((l <= x) && (x <= r)) || ((r <= x) && (x <= l));
}
int div_ceil(int x, int y) {
  return (x + y - 1) / y;
}
void yakubun(ll& a, ll& b) {
  ll g = gcd(a, b);
  a /= g;
  b /= g;
}
void swap(pair<ll, ll>& p) {
  auto [a, b] = p;
  p = {b, a};
}
ll _sqrt(ll x) {
  ll a = sqrt(x);
  while ((a + 1) * (a + 1) <= x) a++;
  while (a * a > x) a--;
  return a;
}
ll _pow(ll x, ll n) {
  ll res = 1;
  while (n > 0) {
    if (n & 1) res *= x;
    x *= x;
    n >>= 1;
  }
  return res;
}
signed main(void) {
}