g #pragma once
#include <vector>
#include <string>

    /**
     * @brief トライ木 (Trie)
     *
     * 英小文字の文字列集合を木構造で管理し、追加や接頭辞（prefix）による出現単語数のカウントを高速に行う。
     */
    struct Trie {
  std::vector<std::vector<long long>> v;
  std::vector<long long> empty;

  // v[p][26] = ノード p 以下の部分木に含まれる文字列の総数
  // v[p][27] = ノード p でちょうど終わる文字列の総数
  Trie() : v(1, std::vector<long long>(28, -1)), empty(28, -1) {
    v[0][26] = 0;
    v[0][27] = 0;
    empty[26] = 0;
    empty[27] = 0;
  }

  /**
   * @brief 文字列 s を挿入する (O(|s|))
   * @param s 挿入する文字列（英小文字のみを想定）
   */
  void insert(const std::string& s) {
    long long p = 0;
    for (size_t i = 0; i < s.size(); i++) {
      long long c = s[i] - 'a';
      v[p][26]++;
      if (v[p][c] == -1) {
        v[p][c] = v.size();
        p = v.size();
        v.push_back(empty);
      } else {
        p = v[p][c];
      }
    }
    v[p][26]++;
    v[p][27]++;
  }

  /**
   * @brief 文字列 s を接頭辞として含む、挿入済み文字列の個数を返す (O(|s|))
   */
  long long count_prefix(const std::string& s) {
    long long p = 0;
    for (size_t i = 0; i < s.size(); i++) {
      long long c = s[i] - 'a';
      if (v[p][c] == -1) {
        return 0;
      }
      p = v[p][c];
    }
    return v[p][26];
  }

  /**
   * @brief 文字列 s と完全に一致する、挿入済み文字列の個数を返す (O(|s|))
   */
  long long count_exact(const std::string& s) {
    long long p = 0;
    for (size_t i = 0; i < s.size(); i++) {
      long long c = s[i] - 'a';
      if (v[p][c] == -1) {
        return 0;
      }
      p = v[p][c];
    }
    return v[p][27];
  }
};
