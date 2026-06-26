// ===== atcoder::lazy_segtree テンプレート集 =====
// #include <atcoder/lazysegtree>
// using namespace atcoder;
//
// 共通インターフェース:
//   lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
//   lazy_segtree<S, op, e, F, mapping, composition, id> seg(v); // vector<S>で初期化
//   seg.set(i, x)           // 1点代入
//   seg.get(i)              // 1点取得
//   seg.apply(i, f)         // 1点作用
//   seg.apply(l, r, f)      // 区間 [l, r) に作用
//   seg.prod(l, r)          // 区間 [l, r) の積
//   seg.all_prod()          // 全体の積
//   seg.max_right(l, g)     // [l, r) が条件 g を満たす最大の r
//   seg.min_left(r, g)      // [l, r) が条件 g を満たす最小の l
//
// ============================================================
// [1] 区間加算・区間最大値
// ------------------------------------------------------------
// using S = ll;
// using F = ll;
// S op(S a, S b) { return max(a, b); }
// S e() { return -inf; }
// S mapping(F f, S s) { return f + s; }
// F composition(F f, F g) { return f + g; }  // f: 新, g: 旧
// F id() { return 0; }
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
//
// ============================================================
// [2] 区間加算・区間最小値
// ------------------------------------------------------------
// using S = ll;
// using F = ll;
// S op(S a, S b) { return min(a, b); }
// S e() { return inf; }
// S mapping(F f, S s) { return f + s; }
// F composition(F f, F g) { return f + g; }  // f: 新, g: 旧
// F id() { return 0; }
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
//
// ============================================================
// [3] 区間加算・区間和
// ------------------------------------------------------------
// struct S { ll sum, cnt; };
// using F = ll;
// S op(S a, S b) { return {a.sum + b.sum, a.cnt + b.cnt}; }
// S e() { return {0, 0}; }
// S mapping(F f, S s) { return {s.sum + f * s.cnt, s.cnt}; }
// F composition(F f, F g) { return f + g; }
// F id() { return 0; }
// // 初期化: rep(i, n) seg.set(i, {v[i], 1});
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
//
// ============================================================
// [4] 区間代入・区間最小値  (inf = 代入なし)
// ------------------------------------------------------------
// using S = ll;
// using F = ll;
// S op(S a, S b) { return min(a, b); }
// S e() { return inf; }
// S mapping(F f, S s) { return f != inf ? f : s; }
// F composition(F f, F g) { return f != inf ? f : g; }  // f: 新, g: 旧
// F id() { return inf; }
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
//
// ============================================================
// [5] 区間代入・区間最大値  (inf = 代入なし)
// ------------------------------------------------------------
// using S = ll;
// using F = ll;
// S op(S a, S b) { return max(a, b); }
// S e() { return -inf; }
// S mapping(F f, S s) { return f != inf ? f : s; }
// F composition(F f, F g) { return f != inf ? f : g; }  // f: 新, g: 旧
// F id() { return inf; }
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
//
// ============================================================
// [6] 区間代入・区間和  (inf = 代入なし)
// ------------------------------------------------------------
// struct S { ll sum, cnt; };
// using F = ll;
// S op(S a, S b) { return {a.sum + b.sum, a.cnt + b.cnt}; }
// S e() { return {0, 0}; }
// S mapping(F f, S s) { return f != inf ? S{f * s.cnt, s.cnt} : s; }
// F composition(F f, F g) { return f != inf ? f : g; }
// F id() { return inf; }
// // 初期化: rep(i, n) seg.set(i, {v[i], 1});
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
// ============================================================
