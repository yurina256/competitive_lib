#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/lazysegtree>

using namespace std;
using ll = long long;

// [1] 区間加算・区間最大値 の設定
namespace RangeAdd_RangeMax {
    constexpr ll inf = 4001001001001001001ll;
    using S = ll;
    using F = ll;
    S op(S a, S b) { return max(a, b); }
    S e() { return -inf; }
    S mapping(F f, S s) { return f + s; }
    F composition(F f, F g) { return f + g; }  // f: 新, g: 旧
    F id() { return 0; }
}

// [3] 区間加算・区間和 の設定
namespace RangeAdd_RangeSum {
    struct S { ll sum, cnt; };
    using F = ll;
    S op(S a, S b) { return {a.sum + b.sum, a.cnt + b.cnt}; }
    S e() { return {0, 0}; }
    S mapping(F f, S s) { return {s.sum + f * s.cnt, s.cnt}; }
    F composition(F f, F g) { return f + g; }
    F id() { return 0; }
}

int main() {
    int n = 8;
    vector<ll> initial_values = {1, 2, 3, 4, 5, 6, 7, 8};

    cout << "=== 1. 区間加算・区間最大値のデモ ===" << endl;
    {
        using namespace RangeAdd_RangeMax;
        // 初期値でセグメント木を初期化
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(initial_values);

        // [0, 8) の最大値を取得
        cout << "初期値 [0, 8) の最大値: " << seg.prod(0, 8) << " (期待値: 8)" << endl;

        // 区間 [2, 6) (要素: 3, 4, 5, 6) に +10 を加算
        // 新しい配列: {1, 2, 13, 14, 15, 16, 7, 8}
        seg.apply(2, 6, 10);

        cout << "加算後 [0, 8) の最大値: " << seg.prod(0, 8) << " (期待値: 16)" << endl;
        cout << "加算後 [0, 3) の最大値: " << seg.prod(0, 3) << " (期待値: 13)" << endl;
        cout << "加算後 [6, 8) の最大値: " << seg.prod(6, 8) << " (期待値: 8)" << endl;
    }
    cout << endl;

    cout << "=== 2. 区間加算・区間和のデモ ===" << endl;
    {
        using namespace RangeAdd_RangeSum;
        // 構造体 S を持つ vector を作って初期化
        vector<S> init_s(n);
        for (int i = 0; i < n; ++i) {
            init_s[i] = {initial_values[i], 1};
        }
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init_s);

        // [0, 8) の和を取得 -> 1+2+3+4+5+6+7+8 = 36
        cout << "初期値 [0, 8) の総和: " << seg.prod(0, 8).sum << " (期待値: 36)" << endl;

        // 区間 [1, 5) (要素: 2, 3, 4, 5) に +5 を加算
        // 新しい配列: {1, 7, 8, 9, 10, 6, 7, 8}
        seg.apply(1, 5, 5);

        cout << "加算後 [0, 8) の総和: " << seg.prod(0, 8).sum << " (期待値: 56)" << endl;
        cout << "加算後 [1, 5) の総和: " << seg.prod(1, 5).sum << " (期待値: 34)" << endl;
    }

    return 0;
}

/*
出力結果:
=== 1. 区間加算・区間最大値のデモ ===
初期値 [0, 8) の最大値: 8 (期待値: 8)
加算後 [0, 8) の最大値: 16 (期待値: 16)
加算後 [0, 3) の最大値: 13 (期待値: 13)
加算後 [6, 8) の最大値: 8 (期待値: 8)

=== 2. 区間加算・区間和のデモ ===
初期値 [0, 8) の総和: 36 (期待値: 36)
加算後 [0, 8) の総和: 56 (期待値: 56)
加算後 [1, 5) の総和: 34 (期待値: 34)
*/
