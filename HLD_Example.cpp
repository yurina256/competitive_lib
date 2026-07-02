#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <atcoder/segtree>
#include "lib/HLD.cpp"

using namespace std;

// ====================================================
// 2, 3用 (可換演算: 加算)
// ====================================================
long long op_add(long long a, long long b) { return a + b; }
long long e_add() { return 0; }

// ====================================================
// 4用 (非可換演算: 一次関数の合成 f(x) = ax + b)
// ====================================================
constexpr long long MOD = 998244353;

struct Linear {
  long long a, b;  // f(x) = ax + b
};

// 一次関数の合成 g(f(x)) を計算する
// g(f(x)) = g_a * (f_a * x + f_b) + g_b = (g_a * f_a) * x + (g_a * f_b + g_b)
Linear composite(Linear f, Linear g) {
  return {
      (g.a * f.a) % MOD,
      (g.a * f.b + g.b) % MOD};
}

// セグメント木のノードに載せる情報
struct SegNode {
  Linear normal;  // 順方向の合成 (左から右へ順番に適用)
  Linear rev;     // 逆方向の合成 (右から左へ順番に適用)
};

SegNode op_linear(SegNode left, SegNode right) {
  return {
      composite(left.normal, right.normal),  // 左を適用したあとに右を適用
      composite(right.rev, left.rev)         // 右を適用したあとに左を適用
  };
}

SegNode e_linear() {
  return {{1, 0}, {1, 0}};  // 恒等写像 f(x) = x
}

int main() {
  // ----------------------------------------------------
  // 木構造の作成
  // ----------------------------------------------------
  // 頂点数 5 の木
  //       0
  //      / \
  //     1   2
  //    / \
  //   3   4
  int n = 5;
  HeavyLightDecomposition hld(n);
  hld.add_edge(0, 1);
  hld.add_edge(0, 2);
  hld.add_edge(1, 3);
  hld.add_edge(1, 4);

  // 根を 0 として HLD を構築
  hld.build(0);

  // ----------------------------------------------------
  // 1. 基本的な木機能 (LCA と距離)
  // ----------------------------------------------------
  cout << "=== 1. 基本的な木機能 ===" << endl;
  cout << "LCA of 3 and 4: " << hld.lca(3, 4) << " (Expected: 1)" << endl;
  cout << "LCA of 3 and 2: " << hld.lca(3, 2) << " (Expected: 0)" << endl;
  cout << "Distance between 3 and 4: " << hld.distance(3, 4) << " (Expected: 2)" << endl;
  cout << "Distance between 3 and 2: " << hld.distance(3, 2) << " (Expected: 3)" << endl;
  cout << endl;

  // ----------------------------------------------------
  // 2. 頂点属性クエリ (セグメント木との連携)　
  // ----------------------------------------------------
  cout << "=== 2. 頂点属性パスクエリ & 部分木クエリ ===" << endl;
  vector<long long> vertex_vals = {10, 20, 30, 40, 50};

  vector<long long> seg_init(n);
  for (int v = 0; v < n; ++v) {
    seg_init[hld.in[v]] = vertex_vals[v];
  }
  atcoder::segtree<long long, op_add, e_add> seg_vertex(seg_init);

  // 3 と 2 のパス上の頂点の値の総和: 3 -> 1 -> 0 -> 2 (40 + 20 + 10 + 30 = 100)
  long long path_sum = 0;
  hld.process_path_vertex(3, 2, [&](int l, int r) {
    path_sum += seg_vertex.prod(l, r);
  });
  cout << "Path sum (3 to 2): " << path_sum << " (Expected: 100)" << endl;

  // 頂点 1 の値を 20 から 100 に変更する
  seg_vertex.set(hld.in[1], 100);
  cout << "Update vertex 1 value to 100" << endl;

  // 再度 3 と 2 のパス上の総和を計算: 40 + 100 + 10 + 30 = 180
  path_sum = 0;
  hld.process_path_vertex(3, 2, [&](int l, int r) {
    path_sum += seg_vertex.prod(l, r);
  });
  cout << "Path sum (3 to 2) after update: " << path_sum << " (Expected: 180)" << endl;

  // 部分木クエリ: 頂点 1 の部分木 {1, 3, 4} の総和: 100 + 40 + 50 = 190
  auto [sub_l, sub_r] = hld.get_subtree(1);
  cout << "Subtree sum of vertex 1: " << seg_vertex.prod(sub_l, sub_r) << " (Expected: 190)" << endl;
  cout << endl;

  // ----------------------------------------------------
  // 3. 辺属性クエリ (セグメント木との連携)
  // ----------------------------------------------------
  cout << "=== 3. 辺属性パスクエリ ===" << endl;
  // 辺 (0, 1) = 2, (0, 2) = 3, (1, 3) = 4, (1, 4) = 5
  // 深い方の頂点に辺の値を割り当てる
  vector<long long> edge_seg_init(n, 0);
  edge_seg_init[hld.in[1]] = 2;  // (0, 1)
  edge_seg_init[hld.in[2]] = 3;  // (0, 2)
  edge_seg_init[hld.in[3]] = 4;  // (1, 3)
  edge_seg_init[hld.in[4]] = 5;  // (1, 4)

  atcoder::segtree<long long, op_add, e_add> seg_edge(edge_seg_init);

  // 3 と 2 のパス上の辺の値の総和: (3,1), (1,0), (0,2) -> 4 + 2 + 3 = 9
  long long edge_path_sum = 0;
  hld.process_path_edge(3, 2, [&](int l, int r) {
    edge_path_sum += seg_edge.prod(l, r);
  });
  cout << "Edge path sum (3 to 2): " << edge_path_sum << " (Expected: 9)" << endl;
  cout << endl;

  // ----------------------------------------------------
  // 4. 有向パスクエリ (非可換演算: 一次関数の合成)
  // ----------------------------------------------------
  cout << "=== 4. 有向パスクエリ (非可換: 一次関数の順序付き合成) ===" << endl;

  // 各頂点の一次関数 f_v(x) = a_v * x + b_v (検証用の新規の値: aの積も完全に変更)
  // f_0(x) = 2x + 3
  // f_1(x) = 5x + 4
  // f_2(x) = 3x + 2
  // f_3(x) = 7x + 1
  // f_4(x) = 4x + 5
  vector<Linear> linears = {
      {2, 3},  // 0
      {5, 4},  // 1
      {3, 2},  // 2
      {7, 1},  // 3
      {4, 5}   // 4
  };

  vector<SegNode> linear_seg_init(n);
  for (int v = 0; v < n; ++v) {
    linear_seg_init[hld.in[v]] = {linears[v], linears[v]};
  }
  atcoder::segtree<SegNode, op_linear, e_linear> seg_linear(linear_seg_init);

  // 【検証A】 頂点 3 から 2 へのパス (3 -> 1 -> 0 -> 2) で関数を順に合成する
  // 合成関数: F(x) = f_2( f_0( f_1( f_3(x) ) ) )
  // 具体的な手計算:
  // f_3(x) = 7x + 1
  // f_1(f_3(x)) = 5*(7x + 1) + 4 = 35x + 9
  // f_0(f_1(f_3(x))) = 2*(35x + 9) + 3 = 70x + 21
  // f_2(f_0(f_1(f_3(x)))) = 3*(70x + 21) + 2 = 210x + 65
  // よって a = 210, b = 65

  Linear total_func = {1, 0};  // 恒等写像で初期化

  hld.process_directed_path(
      3, 2,
      // 上りパス (3 -> 1 -> 0)
      [&](int l, int r) {
        total_func = composite(total_func, seg_linear.prod(l, r).rev);
      },
      // 下りパス (0 -> 2)
      [&](int l, int r) {
        total_func = composite(total_func, seg_linear.prod(l, r).normal);
      });

  cout << "Composite result (3 to 2): y = " << total_func.a << "x + " << total_func.b
       << " (Expected: y = 210x + 65)" << endl;

  // 【検証B】 逆方向のパス 2 から 3 へのパス (2 -> 0 -> 1 -> 3)
  // 合成関数: G(x) = f_3( f_1( f_0( f_2(x) ) ) )
  // 手計算:
  // f_2(x) = 3x + 2
  // f_0(f_2(x)) = 2*(3x + 2) + 3 = 6x + 7
  // f_1(f_0(f_2(x))) = 5*(6x + 7) + 4 = 30x + 39
  // f_3(f_1(f_0(f_2(x)))) = 7*(30x + 39) + 1 = 210x + 274
  // よって a = 210, b = 274

  Linear total_func_rev = {1, 0};
  hld.process_directed_path(
      2, 3,
      [&](int l, int r) {
        total_func_rev = composite(total_func_rev, seg_linear.prod(l, r).rev);
      },
      [&](int l, int r) {
        total_func_rev = composite(total_func_rev, seg_linear.prod(l, r).normal);
      });

  cout << "Composite result (2 to 3): y = " << total_func_rev.a << "x + " << total_func_rev.b
       << " (Expected: y = 210x + 274)" << endl;

  return 0;
}

/*
出力結果:
=== 1. 基本的な木機能 ===
LCA of 3 and 4: 1 (Expected: 1)
LCA of 3 and 2: 0 (Expected: 0)
Distance between 3 and 4: 2 (Expected: 2)
Distance between 3 and 2: 3 (Expected: 3)

=== 2. 頂点属性パスクエリ & 部分木クエリ ===
Path sum (3 to 2): 100 (Expected: 100)
Update vertex 1 value to 100
Path sum (3 to 2) after update: 180 (Expected: 180)
Subtree sum of vertex 1: 190 (Expected: 190)

=== 3. 辺属性パスクエリ ===
Edge path sum (3 to 2): 9 (Expected: 9)

=== 4. 有向パスクエリ (非可換: 一次関数の順序付き合成) ===
Composite result (3 to 2): y = 210x + 65 (Expected: y = 210x + 65)
Composite result (2 to 3): y = 210x + 274 (Expected: y = 210x + 274)
*/
