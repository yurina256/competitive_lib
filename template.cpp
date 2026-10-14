// AI Gen Lib -> https://github.com/yurina256/competitive_lib
#include <bits/stdc++.h>
#include <atcoder/all>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using namespace atcoder;
// using mint = modint1000000007;
// constexpr ll mod = 1000000007;
using mint = modint998244353;
constexpr long long mod = 998244353;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = (int)(n) - 1; i >= 1; i--)
#define ll long long
#define double long double
#define ull unsigned long long
#define sll __int128_t
#define sull __uint128_t
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
#define popcount __builtin_popcountll
template <class T>
using rev_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
constexpr ll inf = 4001001001001001001ll;
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
    using elem_type = typename T::value_type;
    constexpr bool is_container_of_container =
        requires { typename elem_type::value_type; } &&
        !requires(elem_type e) { e.substr(0); };
    for (int i = 0; i < (int)x.size(); i++) {
      pr_single(x[i]);
      if (i != (int)x.size() - 1) {
        if constexpr (is_container_of_container) {
          cout << "\n";
        } else {
          cout << " ";
        }
      }
    }
  } else if constexpr (requires { x.first; x.second; }) {
    pr_single(x.first);
    cout << " ";
    pr_single(x.second);
  } else if constexpr (is_same_v<T, __int128_t> || is_same_v<T, __uint128_t>) {
    using unsigned_type = __uint128_t;
    unsigned_type value;
    bool negative = false;
    if constexpr (is_same_v<T, __int128_t>) {
      negative = x < 0;
      value = negative ? static_cast<unsigned_type>(-(x + 1)) + 1
                       : static_cast<unsigned_type>(x);
    } else {
      value = x;
    }

    string digits;
    do {
      digits.push_back('0' + static_cast<int>(value % 10));
      value /= 10;
    } while (value > 0);
    if (negative) digits.push_back('-');
    reverse(ALL(digits));
    cout << digits;
  } else if constexpr (requires { cout << x; }) {
    cout << x;
  }
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
ll Digit(ll n) {
  ll ans = 0;
  while (n > 0) {
    n /= 10;
    ans++;
  }
  return ans;
}
bool in_range(int l, int x, int r) {  // 閉区間
  return ((l <= x) && (x <= r)) || ((r <= x) && (x <= l));
}
int div_ceil(int x, int y) {
  return (x + y - 1) / y;
}
void yakubun(ll& a, ll& b) {
  if (a < 0) {
    a = -a;
    b = -b;
  }
  if (a == 0) {
    b = 1;
    return;
  }
  if (b == 0) {
    a = 1;
    return;
  }
  ll g = gcd(abs(a), abs(b));
  a /= g;
  b /= g;
  // pr(a, b);
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
ll bs(ll l, ll r, function<bool(ll)> f) {  // l-> false, r->true
  while (r - l > 1) {
    ll mid = l + (r - l) / 2;
    if (f(mid)) r = mid;
    else
      l = mid;
  }
  return r;
}
vector<pair<ll, ll>> p_fact(int N) {  // {素因数,指数}
  vector<pair<ll, ll>> res;
  for (int a = 2; a * a <= N; ++a) {
    if (N % a != 0) continue;
    int ex = 0;  // 指数

    // 割れる限り割り続ける
    while (N % a == 0) {
      ++ex;
      N /= a;
    }

    // その結果を push
    res.push_back({a, ex});
  }

  // 最後に残った数について
  if (N != 1) res.push_back({N, 1});
  return res;
}
template <typename T>
std::vector<std::vector<T>> flip(const std::vector<std::vector<T>>& v) {
  if (v.empty() || v[0].empty()) return {};

  size_t rows = v.size();
  size_t cols = v[0].size();

  // 縦横のサイズを入れ替えた二次元配列を初期化
  std::vector<std::vector<T>> transposed(cols, std::vector<T>(rows));

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      transposed[j][i] = v[i][j];
    }
  }

  return transposed;
}
//==================Template END===========================
signed main() {
}