#pragma once
#include <vector>
#include <stack>
#include <utility>

/**
 * @brief 木のオイラーツアー (非再帰実装)
 * 
 * 行きがけ順インデックス、帰りがけ順インデックス、および根からの深さを計算する。
 * これにより、部分木に対するクエリを1次元配列の区間に変換して処理できるようになります。
 */
struct EulerTour {
  int n;
  std::vector<int> index;      // 行きがけ順インデックス (頂点に入ったタイミング)
  std::vector<int> rev_index;  // 帰りがけ順インデックス (頂点から出たタイミング)
  std::vector<int> d;          // 各頂点の根からの深さ (1-indexed)

  /**
   * @brief コンストラクタ
   * @param g 隣接リスト表現の無向木
   * @param root 根とする頂点 (0-indexed)
   */
  EulerTour(const std::vector<std::vector<long long>>& g, int root = 0) {
    n = g.size();
    index.assign(n, -1);
    rev_index.assign(n, -1);
    d.assign(n, -1);

    std::stack<std::pair<int, bool>> stk;
    stk.push({root, true});
    int pt = 0;
    int depth = 0;

    while (!stk.empty()) {
      auto [p, type] = stk.top();
      stk.pop();
      if (type) {
        depth++;
        index[p] = pt;
        d[p] = depth;
        pt++;
        stk.push({p, false});
        for (auto next : g[p]) {
          if (index[next] == -1) {
            stk.push({(int)next, true});
          }
        }
      } else {
        depth--;
        rev_index[p] = pt;
        pt++;
      }
    }
  }
};
