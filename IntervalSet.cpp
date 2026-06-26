#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template <typename T>
struct IntervalMap {
    struct Node {
        long long l, r;
        mutable T val; // set内でも値を変更可能にするためmutable
        bool operator<(const Node& rhs) const { return l < rhs.l; }
    };

    std::set<Node> st;

    // 区間 [l, r] を値 v で塗りつぶす (add & update)
    void add(long long l, long long r, T v) {
        if (l > r) return;
        remove(l, r); // まず指定範囲の既存区間を消去・分断する
        st.insert({l, r, v});
    }

    // 区間 [l, r] を削除する (彫り込み)
    void remove(long long l, long long r) {
        if (l > r) return;

        auto it = st.lower_bound({l, r, T()});
        if (it != st.begin() && std::prev(it)->r >= l) {
            it = std::prev(it);
        }

        std::vector<Node> to_add;
        while (it != st.end() && it->l <= r) {
            if (it->r >= l) {
                long long old_l = it->l;
                long long old_r = it->r;
                T old_v = it->val;
                it = st.erase(it);

                if (old_l < l) to_add.push_back({old_l, l - 1, old_v});
                if (old_r > r) to_add.push_back({r + 1, old_r, old_v});
            } else {
                it++;
            }
        }
        for (const auto& node : to_add) st.insert(node);
    }

    // 値 x が含まれる区間のイテレータを返す
    auto find(long long x) const {
        auto it = st.lower_bound({x, x, T()});
        if (it != st.end() && it->l <= x && x <= it->r) return it;
        if (it != st.begin()) {
            it = std::prev(it);
            if (it->l <= x && x <= it->r) return it;
        }
        return st.end();
    }
};