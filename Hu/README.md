# ヒューリスティックコンテスト向けライブラリ (Hu)

AtCoder Heuristic Contest (AHC) 等のマラソンマッチで主力を担うアルゴリズム群の C++ 実装と解説です。

---

## 収録モジュール一覧

| ファイル | 概要・クラス | 特徴 |
| :--- | :--- | :--- |
| [HuUtils.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Hu/HuUtils.cpp) | `Hu::Timer`, `Hu::XorShift` | 高速乱数 (xoshiro256**) と高精度タイマー |
| [SimulatedAnnealing.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Hu/SimulatedAnnealing.cpp) | `Hu::AnnealingAcceptor` | 焼きなまし法・山登り法の受理判定器（最大化・最小化対応） |
| [SimulatedAnnealing_Example.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Hu/SimulatedAnnealing_Example.cpp) | TSP (2-opt) 実装例 | 山登り法と焼きなまし法の比較サンプル |
| [BeamSearch.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Hu/BeamSearch.cpp) | `Hu::BeamSearch` | 汎用ビームサーチ（深さ・幅固定、行動履歴復元対応） |
| [ChokudaiSearch.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Hu/ChokudaiSearch.cpp) | `Hu::ChokudaiSearch` | 時間駆動型木探索（制限時間を使い切る段階的展開） |
| [BeamSearch_Example.cpp](file:///C:/Users/yurina256/Desktop/atcoder/lib/Hu/BeamSearch_Example.cpp) | グリッド移動問題例 | ビームサーチと Chokudai サーチの動作比較サンプル |

---

## 1. 局所探索・メタヒューリスティクス系 (SimulatedAnnealing.cpp)

### 理論・アルゴリズム概要
解の「近傍（少しだけ変更した状態）」を次々に探索し、徐々に解を改善していくアプローチです。配置問題、巡回セールスマン問題（TSP）、スケジューリング問題などに極めて強力です。

- **山登り法 (Hill Climbing)**:
  - 常に現在のスコアより良くなる手だけを採用します。
  - 実装が最も容易ですが、局所最適解（ローカルミニマム）に嵌まると抜け出せなくなります。
- **焼きなまし法 (Simulated Annealing: SA)**:
  - スコアが悪化する手であっても、温度 $T$ と悪化幅 $\Delta$ に応じた確率 $P = \exp(-\Delta / T)$ で採用します。
  - 探索初期（$T$ が高い）は広い領域を探索し、探索終盤（$T$ が低い）は山登り法のように収束させます。

### 使い方・設計パターン (差分更新型)

```cpp
#include "lib/Hu/SimulatedAnnealing.cpp"

Hu::XorShift rng(12345);
Hu::Timer timer(1.95); // 制限時間 1.95 秒

// 初期温度 50.0, 終了温度 0.01 で最大化
Hu::AnnealingAcceptor sa(50.0, 0.01, Hu::AnnealingAcceptor::Objective::Maximize);

while (!timer.is_time_over()) {
    // 1. 近傍の操作を選ぶ
    auto move = pick_random_move(rng);

    // 2. 差分スコアを計算 (高速化の鍵)
    double next_score = current_score + calc_diff(move);

    // 3. 受理判定
    if (sa.accept(current_score, next_score, timer.progress())) {
        apply_move(move);
        current_score = next_score;
        if (current_score > best_score) {
            best_score = current_score;
            best_state = current_state;
        }
    } else {
        // 棄却 (必要なら状態のロールバック)
    }
}
```

---

## 2. 木探索・逐次構築系 (BeamSearch.cpp / ChokudaiSearch.cpp)

### 理論・アルゴリズム概要
ターン制ゲーム、パズル、あるいは「1手ずつ解を組み立てていく」問題に適したアプローチです。

- **ビームサーチ (Beam Search)**:
  - 深さ（手数）ごとに上位 $B$ 個（ビーム幅）のノードのみを残して次の深さを展開します。
  - メモリと手数が事前に読みやすく、高速に実行できます。
- **Chokudai サーチ (Chokudai Search)**:
  - 深さ $0, 1, \dots, D$ ごとに優先度付きキューを持ち、時間がある限り浅い深さと深い深さを交互に少しずつ展開し続けます。
  - 事前にビーム幅を決め打ちする必要がなく、制限時間いっぱい計算資源を使い切ることができます。

### 使い方・状態クラスの設計要件

`State` クラスに以下の2つのメンバ関数を実装するだけで利用可能です：

```cpp
struct MyState {
    int score = 0;

    // 行動を適用して状態を進める
    void apply(const Action& act) {
        // ...
    }

    // 次に取りうる候補手とスコアのペアを列挙
    void get_next_actions(std::vector<std::pair<Action, int>>& cand) const {
        // cand.emplace_back(act, score);
    }
};

// ビームサーチの実行
auto result = Hu::BeamSearch<MyState, Action, int, true>::solve(
    initial_state, MAX_DEPTH, BEAM_WIDTH
);

// 行動系列の取得
for (const auto& act : result.actions) {
    // 復元された手を出力
}
```

---

## アルゴリズム選択の指針

| 問題の性質 | 推奨アルゴリズム |
| :--- | :--- |
| **最終的な配置・順序・割り当てを決める問題** | 焼きなまし法 (`SimulatedAnnealing`) |
| **手数が固定で、1手ずつ選択肢を決定していく問題** | ビームサーチ (`BeamSearch`) |
| **手数固定だが制限時間をギリギリまで使い切りたい問題** | Chokudai サーチ (`ChokudaiSearch`) |
| **状態の全体再計算が重いが差分更新が $O(1)$ で可能な問題** | 焼きなまし法 (差分更新) |
