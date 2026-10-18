# 二分探索 (`bs`) 網羅テンプレート・チートシート

`main.cpp` の二分探索テンプレート関数 `bs` を用いて、昇順ソート済み配列 `v`（要素数 `n`）に対して **「$k$ 以上 / $k$ を超える / $k$ 以下 / $k$ 未満」** の **「境界値（最小・最大）・個数・参照・存在判定」** を求める網羅的なガイドです。

---

## 0. 前提となるテンプレート (`main.cpp`)

```cpp
ll bs(ll l, ll r, function<bool(ll)> f) {  // l-> true, r->false
  while (r - l > 1) {
    ll mid = l + (r - l) / 2;
    if (f(mid)) l = mid;
    else
      r = mid;
  }
  return l;
}
```

### 重要な仕様と注意点
- `bs(l, r, f)` は **左側 `l` が `true`、右側 `r` が `false`** となる単調な条件 `f` に対して、**`f(x) == true` を満たす最大の `x`（境界の左端）** を返します。
- そのすぐ右隣である **`ans + 1` が `f(x) == false` を満たす最小の `x`（境界の右端）** になります。
- 昇順ソート済み配列 `v` では、左が小さく右が大きいため、判定関数 `f` には必ず **`v[val] < k` または `v[val] <= k`**（左側で `true` になる条件）を渡します。
  - **「$k$ 未満 (`< k`)」と「$k$ 以上 (`>= k`)」は表裏一体**なので、どちらも `return v[val] < k;` で求まります。
  - **「$k$ 以下 (`<= k`)」と「$k$ を超える (`> k`)」は表裏一体**なので、どちらも `return v[val] <= k;` で求まります。

```
インデックス:  -1    0    1   ...  ans | ans+1 ...  n-1    n
判定 f(val):   T    T    T   ...   T  |   F   ...   F     F
                                   ↑      ↑
                           左側の最大(ans) 右側の最小(ans+1)
```

---

## 1. 早見表（チートシート）

配列 `v`（サイズ `n`、昇順ソート済み）に対し、`ll ans = bs(-1, n, func);` を実行した後の対応表です。

| 求めたい条件 | `func` の条件式 | 求めるインデックス `idx` | 同じ値が複数あるときの `idx` の位置 | 値がない判定 | 境界の値（最大 / 最小） | 要素への参照 | 条件を満たす要素の個数 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **$k$ 未満** (`< k`) で**最大** | `v[val] < k` | `ans` | 同値の中で **index 最大（右端）** | `ans == -1` | `v[ans]` | `v[ans]` | `ans + 1` |
| **$k$ 以下** (`<= k`) で**最大** | `v[val] <= k` | `ans` | 同値の中で **index 最大（右端）** | `ans == -1` | `v[ans]` | `v[ans]` | `ans + 1` |
| **$k$ 以上** (`>= k`) で**最小** | `v[val] < k` | `ans + 1` | 同値の中で **index 最小（左端）** | `ans + 1 == n` | `v[ans + 1]` | `v[ans + 1]` | `n - (ans + 1)` |
| **$k$ を超える** (`> k`) で**最小** | `v[val] <= k` | `ans + 1` | 同値の中で **index 最小（左端）** | `ans + 1 == n` | `v[ans + 1]` | `v[ans + 1]` | `n - (ans + 1)` |

> [!IMPORTANT]
> - **`>= k` や `> k` を求めたいときも、`func` の不等号は `< k` や `<= k` のままにしておき、結果のインデックスとして `ans + 1` を使う**のがポイントです（`bs` は左側が `true`・右側が `false` であることを前提としているため）。
> - **同じ値が複数回出現する場合の挙動**：
>   - `ans`（`< k` / `<= k` の最大）は `true` 領域の右端なので、該当する最大値が複数ある場合は **最も大きい index（一番右）** を指します。
>   - 逆に `ans + 1`（`>= k` / `> k` の最小）は `false` 領域の左端なので、該当する最小値が複数ある場合は **最も小さい index（一番左）** を指します。
>   - もし逆側の端（例：「$k$ 以下で最大の値のうち **index 最小（一番左）**」）が欲しい場合は、まず値 `ll m = v[ans];` を求めてから `bs(-1, n, [&](ll i) { return v[i] < m; }) + 1`（`m` 以上の左端）を取れば求まります。

---

## 2. 条件別・コピペ用コード例

### ① $k$ 未満 (`< k`) で最も大きい値・個数・参照

`v[val] < k` が `true` となる最大のインデックス `ans` をそのまま使います（同じ値が複数ある場合は **index 最大** を指します）。

```cpp
auto func = [&](ll val) {
  return v[val] < k;
};
ll ans = bs(-1, n, func);

// 1. k未満の値の個数
ll cnt = ans + 1;

// 2. 値がない場合の判定・最も大きい値・参照
if (ans == -1) {
  // k未満の値が存在しない場合の処理
} else {
  ll val = v[ans];     // k未満で最も大きい値
  ll& ref = v[ans];    // k未満で最も大きい要素への参照 (同値ならindex最大)
}
```

---

### ② $k$ 以下 (`<= k`) で最も大きい値・個数・参照

`v[val] <= k` が `true` となる最大のインデックス `ans` をそのまま使います（同じ値が複数ある場合は **index 最大** を指します）。

```cpp
auto func = [&](ll val) {
  return v[val] <= k;
};
ll ans = bs(-1, n, func);

// 1. k以下の値の個数
ll cnt = ans + 1;

// 2. 値がない場合の判定・最も大きい値・参照
if (ans == -1) {
  // k以下の値が存在しない場合の処理
} else {
  ll val = v[ans];     // k以下で最も大きい値
  ll& ref = v[ans];    // k以下で最も大きい要素への参照 (同値ならindex最大)
}
```

---

### ③ $k$ 以上 (`>= k`) で最も小さい値・個数・参照

`v[val] < k`（$k$ 未満）が `false` に切り替わる最初の位置 **`idx = ans + 1`** が「$k$ 以上で最小の要素」になります（同じ値が複数ある場合は **index 最小** を指します）。

```cpp
auto func = [&](ll val) {
  return v[val] < k;  // 「k未満」の境界を探し、その1つ右(ans + 1)を取る
};
ll ans = bs(-1, n, func);
ll idx = ans + 1;

// 1. k以上の値の個数
ll cnt = n - idx;

// 2. 値がない場合の判定・最も小さい値・参照
if (idx == n) {
  // k以上の値が存在しない場合の処理
} else {
  ll val = v[idx];     // k以上で最も小さい値
  ll& ref = v[idx];    // k以上で最も小さい要素への参照 (同値ならindex最小)
}
```

---

### ④ $k$ を超える (`> k`) で最も小さい値・個数・参照

`v[val] <= k`（$k$ 以下）が `false` に切り替わる最初の位置 **`idx = ans + 1`** が「$k$ を超える最小の要素」になります（同じ値が複数ある場合は **index 最小** を指します）。

```cpp
auto func = [&](ll val) {
  return v[val] <= k;  // 「k以下」の境界を探し、その1つ右(ans + 1)を取る
};
ll ans = bs(-1, n, func);
ll idx = ans + 1;

// 1. kを超える値の個数
ll cnt = n - idx;

// 2. 値がない場合の判定・最も小さい値・参照
if (idx == n) {
  // kを超える値が存在しない場合の処理
} else {
  ll val = v[idx];     // kを超える最も小さい値
  ll& ref = v[idx];    // kを超える最も小さい要素への参照 (同値ならindex最小)
}
```

---

## 3. 区間内の個数（全4パターン）と $k$ ちょうどの個数

「$x$ 未満の個数 (`< x`)」と「$x$ 以下の個数 (`<= x`)」の引き算で、あらゆる区間の要素数を $O(\log N)$ で求められます。
（※ `bs(...) + 1` 同士の引き算になるため、`+ 1` は相殺されて `bs(...) - bs(...)` だけで書けます）

| 区間の種類 | 条件式 | 考え方 | `bs` での計算式（`+1` 相殺済み） |
| :--- | :--- | :--- | :--- |
| **閉区間 $[L, R]$** | $L \le v[i] \le R$ | (`R` 以下) $-$ (`L` 未満) | `bs(-1, n, [&](ll i){ return v[i] <= R; }) - bs(-1, n, [&](ll i){ return v[i] < L; })` |
| **半開区間 $[L, R)$** | $L \le v[i] < R$ | (`R` 未満) $-$ (`L` 未満) | `bs(-1, n, [&](ll i){ return v[i] < R; }) - bs(-1, n, [&](ll i){ return v[i] < L; })` |
| **半開区間 $(L, R]$** | $L < v[i] \le R$ | (`R` 以下) $-$ (`L` 以下) | `bs(-1, n, [&](ll i){ return v[i] <= R; }) - bs(-1, n, [&](ll i){ return v[i] <= L; })` |
| **開区間 $(L, R)$** | $L < v[i] < R$ | (`R` 未満) $-$ (`L` 以下) | `bs(-1, n, [&](ll i){ return v[i] < R; }) - bs(-1, n, [&](ll i){ return v[i] <= L; })` |
| **$k$ ちょうど** | $v[i] == k$ | (`k` 以下) $-$ (`k` 未満) | `bs(-1, n, [&](ll i){ return v[i] <= k; }) - bs(-1, n, [&](ll i){ return v[i] < k; })` |

```cpp
// ラムダを2つ用意しておくと全パターンを綺麗に書ける
auto cnt_lt = [&](ll x) { return bs(-1, n, [&](ll i) { return v[i] < x; }) + 1; };   // x未満 (< x) の個数
auto cnt_le = [&](ll x) { return bs(-1, n, [&](ll i) { return v[i] <= x; }) + 1; };  // x以下 (<= x) の個数

ll cnt_eq   = cnt_le(k) - cnt_lt(k);                  // v[i] == k の個数
ll cnt_cc   = max(0LL, cnt_le(R) - cnt_lt(L));        // [L, R]  (L以上 R以下)
ll cnt_co   = max(0LL, cnt_lt(R) - cnt_lt(L));        // [L, R)  (L以上 R未満)
ll cnt_oc   = max(0LL, cnt_le(R) - cnt_le(L));        // (L, R]  (L超え R以下)
ll cnt_oo   = max(0LL, cnt_lt(R) - cnt_le(L));        // (L, R)  (L超え R未満)
```

---

## 4. 実数（小数）の二分探索テンプレート

実数（`double` / `long double`）で境界値を求める場合は、`while (r - l > eps)` を使うと浮動小数点の丸め誤差で無限ループになる危険があるため、**`rep(_, 100)` で固定回数ループを回す**のが定石です（100回で区間幅が $2^{-100} \approx 10^{-30}$ 倍になるため十分収束します）。

```cpp
double bs_double(double l, double r, function<bool(double)> f) {  // l-> true, r->false
  rep(_, 100) {
    double mid = (l + r) / 2.0;
    if (f(mid)) l = mid;
    else r = mid;
  }
  return l;
}
```

### 使用例（例：$\sqrt{2}$ を求める）
```cpp
auto func = [&](double val) {
  return val * val <= 2.0;  // l側(0.0)がtrue, r側(2.0)がfalse
};
double ans = bs_double(0.0, 2.0, func);
pr(SP, ans);  // 1.414213562373
```

---

## 5. （参考）逆向きの条件（左が `false`、右が `true`）をそのまま書きたい場合

もし `v[val] >= k` のように **「左側が `false`、右側が `true`」** の条件式をそのまま書きたい場合は、`bs` の `while` 条件を `abs(r - l) > 1` に変えて `bs(n, -1, func)` と呼ぶ（めぐる式）か、関数内で `!` で反転させます。

```cpp
// main.cpp の bs をそのまま使う場合：条件全体を !() で囲むか、不等号を反転する
// 「k以上で最小」を求めたいとき、!(v[val] >= k) すなわち v[val] < k として ans + 1 を取るのが最も安全です。

// もし bs の while 条件を while (abs(r - l) > 1) に変更した場合：
// bs(ok, ng, func) として「常に第1引数に true 側の初期値、第2引数に false 側の初期値」を渡せます。
ll bs_meguru(ll ok, ll ng, function<bool(ll)> f) {
  while (abs(ng - ok) > 1) {
    ll mid = (ok + ng) / 2;
    if (f(mid)) ok = mid;
    else ng = mid;
  }
  return ok;
}
// この場合:
// k以上で最小のインデックス -> bs_meguru(n, -1, [&](ll val) { return v[val] >= k; }) (存在しないなら n)
// kを超える最小のインデックス -> bs_meguru(n, -1, [&](ll val) { return v[val] > k; })  (存在しないなら n)
// k以下で最大のインデックス   -> bs_meguru(-1, n, [&](ll val) { return v[val] <= k; }) (存在しないなら -1)
// k未満で最大のインデックス   -> bs_meguru(-1, n, [&](ll val) { return v[val] < k; })  (存在しないなら -1)
```
