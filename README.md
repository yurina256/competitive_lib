# Yurina256 Competitive Programming Library

AtCoder などの競技プログラミングで使用する C++ テンプレートおよびアルゴリズム・データ構造のライブラリです。  
カテゴリ別に整理されており、各ライブラリファイルと同階層に動作確認および使用例を示す `_Example.cpp` が用意されています。

---

## ビジュアル図解ガイド (Visual Guide)
- [visual_guide.html](file:///C:/Users/yurina256/Desktop/atcoder/lib/visual_guide.html): 各アルゴリズム・データ構造の直感的なビジュアル図解＆動的シミュレータ（ブラウザで閲覧可能）

---

## テンプレート (Template)
- [template.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/template.cpp): 基本的な型定義、マクロ、高速I/O、`ordered_set` 等を含む標準の解答用テンプレート

---

## カテゴリ別ライブラリ一覧

### 1. データ構造 (DataStructure)
- [UnionFind.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/UnionFind.cpp): 集合の併合や同グループ判定、サイズ取得をほぼ $O(1)$ で行う素集合データ構造
- [lazySegTree.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/lazySegTree.cpp): 区間更新・区間クエリを $O(\log N)$ で処理できる遅延評価セグメント木
- [MergeSortTree.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/MergeSortTree.cpp): 区間内で特定値以下の要素数を $O(\log^2 N)$ で取得できるマージソート木
- [GetKth.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/GetKth.cpp): 動的に追加・削除される要素から、常に $K$ 番目に小さい（または大きい）値を $O(\log N)$ で取得する構造体
- [Ruiseki2D.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/Ruiseki2D.cpp): グリッド上の任意の矩形領域の総和を $O(1)$ で取得する2次元累積和
- [InversionNumber.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/InversionNumber.cpp): 転倒数（反転数）を $O(N \log N)$ で計算するアルゴリズム
- [IntervalSet.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/IntervalSet.cpp): 重複しない複数の区間を `std::set` で統合しながら効率的に管理するデータ構造
- [RangeFreqQuery.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/RangeFreqQuery.cpp): 特定の値が指定された区間内に何個出現するかを $O(\log N)$ で取得するデータ構造
- [Mo.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/DataStructure/Mo.cpp): クエリを平方分割して走査順をソートすることで状態遷移を高速化するクエリ平方分割アルゴリズム
- [ordered_set.cpp](file:///home/yurina256/Desktop/atcoder/lib/DataStructure/ordered_set.cpp): 任意の順位の要素取得や指定値未満の要素数を $O(\log N)$ で取得できる順序付き集合 (Policy-Based Data Structure)


### 2. グラフアルゴリズム (Graph)
- [Dijkstra.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/Dijkstra.cpp): 単一始点最短経路を $O((E + V) \log V)$ で求めるダイクストラ法
- [WarshallFloyd.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/WarshallFloyd.cpp): 全点対間最短経路を $O(V^3)$ で求めるワーシャルフロイド法
- [TreeDiameter.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/TreeDiameter.cpp): 木の直径（最遠頂点間の最長パス長）を $O(V)$ で求めるアルゴリズム
- [EulerTour.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/EulerTour.cpp): 木を平坦化し、部分木に対する処理を1次元配列の区間クエリに変換するオイラーツアー (非再帰)
- [Kruskal.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/Kruskal.cpp): 無向グラフの最小/最大全域木（Spanning Tree）を $O(E \log V)$ で求めるクラスカル法
- [HLD.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/HLD.cpp): 木に対するパス・部分木クエリを効率的に処理する重軽分解 (Heavy-Light Decomposition)
- [LinkCutTree.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Graph/LinkCutTree.cpp): 動的な森に対する辺の追加・削除、連結判定、根変更、パス上のモノイド集約を償却 $O(\log V)$ で処理する Link-Cut Tree

### 3. 数学・数論 (Math)
- [Combination.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Math/Combination.cpp): 前計算を行い、二項係数 $_n\mathrm{C}_r \pmod P$ などを $O(1)$ で求める構造体
- [PrimeFactorization.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Math/PrimeFactorization.cpp): 与えられた整数 $N$ を $O(\sqrt{N})$ で素因数分解するアルゴリズム
- [Eratosthenes.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Math/Eratosthenes.cpp): $N$ 以下の素数の列挙や、区間素数個数を $O(1)$ で計算するエラトステネスの篩
- [ExtendedGCD.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Math/ExtendedGCD.cpp): 不定方程式 $ax + by = \gcd(a, b)$ の整数解を $O(\log \min(a, b))$ で求める拡張ユークリッド互除法
- [Matrix.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Math/Matrix.cpp): 行列積、行列ベクトル積、および繰り返し二乗法を用いた高速な行列累乗 $A^N$ を計算するライブラリ
- [MillerRabin.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Math/MillerRabin.cpp): 64bit整数 (unsigned long long) 範囲の大きな数が素数であるかを $O(K \log^3 N)$ で決定的に判定する確率的素数判定法


### 4. 探索・全列挙 (Search)
- [BinarySearch.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Search/BinarySearch.cpp): 単調性を満たす境界値を求める二分探索および「めぐる式二分探索」のテンプレート
- [LIS.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Search/LIS.cpp): 最長増加部分列の長さを $O(N \log N)$ で求めるアルゴリズム（狭義・広義両対応）
- [SetPartition.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Search/SetPartition.cpp): $N$ 個の要素を区別しないグループに分割するすべての方法（ベル数）を辞書順で列挙する再帰

### 5. 文字列アルゴリズム (String)
- [Trie.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/String/Trie.cpp): 文字列の挿入や接頭辞（Prefix）検索を $O(|S|)$ で行うトライ木
- [RunLengthEncoding.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/String/RunLengthEncoding.cpp): 連続する同一の要素をまとめて圧縮する $O(N)$ のランレングス圧縮
- [RollingHash.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/String/RollingHash.cpp): 文字列の任意の部分文字列のハッシュ値を $O(1)$ で取得し、一致判定等を行うデータ構造
- [SAIS.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/String/SAIS.cpp): 文字列の接尾辞配列 (Suffix Array) を最悪計算量 $O(N)$ で構築する SA-IS 法

---

## 未検証ライブラリ (unverified)
動作確認済みですが、検証中のため `unverified/` ディレクトリに配置されているライブラリ群です。各ファイルと同階層に使用例を示す `_Example.cpp` があります。
### 1. データ構造 (DataStructure)
- [SegTree2D.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/DataStructure/SegTree2D.cpp): 2次元グリッド上の1点更新・矩形区間クエリを $O(\log H \log W)$ で処理する2次元セグメント木
- [SegTreeBeats.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/DataStructure/SegTreeBeats.cpp): 区間 chmin / chmax / 加算 / 更新 と区間総和 / 最大値 / 最小値クエリをならし $O(\log^2 N)$ で処理する Segment Tree Beats
- [ReversibleSegTree.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/DataStructure/ReversibleSegTree.cpp): 平衡二分探索木 (Implicit Treap) を用い、区間反転 `reverse(l, r)`・区間作用・区間集約・挿入・削除を $O(\log N)$ で処理する反転可能遅延セグメント木

### 2. グラフアルゴリズム (Graph)
- [LCA.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Graph/LCA.cpp): 木における2頂点の共通する最深の祖先を $O(\log V)$ で求める最小共通祖先構造体
- [SCC.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Graph/SCC.cpp): 有向グラフを強連結成分に分解しトポロジカルソートする強連結成分分解
- [TopologicalSort.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Graph/TopologicalSort.cpp): 有向グラフの依存関係を一列に並べるトポロジカルソート (閉路検出対応)
- [Dinic.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Graph/Dinic.cpp): 最大流 (および最小カット) を $O(V^2 E)$ で求める Dinic 法
- [MinCostFlow.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Graph/MinCostFlow.cpp): グラフに指定流量を送る最小費用を $O(F E \log V)$ で求める最小費用流 (Primal-Dual法)

### 3. 文字列アルゴリズム (String)
- [Parser.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/String/Parser.cpp): 典型的な四則演算の数式をパース・評価する再帰下降構文解析のテンプレート
- [ZAlgorithm.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/String/ZAlgorithm.cpp): 各 $i$ において文字列全体と $S[i..]$ の最長共通接頭辞の長さを $O(|S|)$ で求める Z-algorithm
- [Manacher.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/String/Manacher.cpp): 各文字を中心とする最長奇数長回文の半径を $O(|S|)$ で求める Manacher のアルゴリズム

### 4. 幾何学 (Geometry)
- [Geometry.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Geometry/Geometry.cpp): 点・直線・円などの基本オブジェクト定義、CCW、五心 (重心・内心・外心・垂心・傍心) や凸包を処理する幾何ライブラリ
- [Geometry3D.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/unverified/Geometry/Geometry3D.cpp): 3次元空間における点・直線・線分・平面オブジェクトの定義、射影、点と直線の最短距離などを処理する3次元幾何ライブラリ



