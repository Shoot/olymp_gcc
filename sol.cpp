#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, q;
    cin >> n >> q;
    struct Node {
        int l = -1;
        int r = -1;
        int su = 0;
        int mn = 1e9;
        int mx = -1e9;
    };
    vector<Node> tree;
    auto su = [&] (int u) -> int {
        return (u == -1 ? 0 : tree[u].su);
    };
    auto mn = [&] (int u) -> int {
        return (u == -1 ? 1e9 : tree[u].mn);
    };
    auto mx = [&] (int u) -> int {
        return (u == -1 ? -1e9 : tree[u].mx);
    };
    auto recalc = [&] (int u) -> void {
        if (u == -1) {
            return;
        }
        tree[u] = {tree[u].l, tree[u].r, su(tree[u].l)+su(tree[u].r),
                                         min(mn(tree[u].l), mn(tree[u].r)),
                                         max(mx(tree[u].l), mx(tree[u].r))};
    };
    auto nw = [&] () -> int {
        tree.push_back({});
        return tree.size()-1;
    };
    auto inc = [&] (auto f, int u, int tl, int tr, int pos) -> void {
        if (tl == tr) {
            tree[u].su += 1;
            tree[u].mn = tl;
            tree[u].mx = tl;
            return;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            if (tree[u].l == -1) {
                tree[u].l = nw();
            }
            f(f, tree[u].l, tl, tm, pos);
        } else {
            if (tree[u].r == -1) {
                tree[u].r = nw();
            }
            f(f, tree[u].r, tm+1, tr, pos);
        }
        recalc(u);
    };
    auto split = [&] (auto f, int u, int sz) -> int {
        int ret = nw();
        if (!sz) {
            return ret;
        }
        if (su(u) == sz) {
            swap(tree[u], tree[ret]);
            return ret;
        }
        if (tree[u].l == -1 && tree[u].r == -1) {
            tree[ret] = tree[u];
            tree[u].su -= sz;
            tree[ret].su = sz;
            return ret;
        }
        if (su(tree[u].l) >= sz) {
            tree[ret].l = f(f, tree[u].l, sz);
            recalc(u);
            recalc(ret);
            return ret;
        } else {
            sz -= su(tree[u].l);
            swap(tree[ret].l, tree[u].l);
            tree[ret].r = f(f, tree[u].r, sz);
            recalc(u);
            recalc(ret);
            return ret;
        }
    };
    auto merge = [&] (auto f, int& u, int& v) -> void {
        if (su(u) == 0) {
            swap(u, v);
            return;
        }
        if (su(v) == 0) {
            return;
        }
        if (tree[u].l == -1 && tree[u].r == -1) {
            // leaf
            assert(tree[v].l == -1 && tree[v].r == -1);
            tree[u].su += tree[v].su;
            v = -1;
            return;
        }
        // v is never used after
        f(f, tree[u].l, tree[v].l);
        f(f, tree[u].r, tree[v].r);
        v = -1;
        recalc(u);
    };
    int prev = 1e9;
    vector<int> roots(1'000'000);
    vector<int> LL(1'000'000); // starting_point_by_order
    auto comp = [&] (auto const& a, auto const& b) {
        return LL[a] < LL[b];
    };
    set<int, decltype(comp)> st(comp);
    int C = 0;
    for (int i = 0; i < n; i += 1) {
        int x;
        cin >> x;
        if (x < prev) {
            LL[C] = i;
            st.insert(C);
            roots[C] = nw();
            C += 1;
        }
        prev = x;
        inc(inc, roots[C-1], 1, 1e9, x);
    }
    for (int ii = 0; ii < q; ii += 1) {
//        for (const auto &x : st) {
//            cout << x << ": " << LL[x] << ": " << su(roots[x]) << ":D\n";
//        }
        int l, r;
        cin >> l >> r;
        l -= 1;
        r -= 1;
        LL[999'999] = l;
        auto it1 = (--st.upper_bound(999'999));
        int ordl = *it1;
        LL[999'999] = r;
        auto it2 = (--st.upper_bound(999'999));
        int ordr = *it2;
        if (ordl == ordr) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
        int ret = split(split, roots[ordl], l-LL[ordl]);
        swap(ret, roots[ordl]);
        int pref = split(split, roots[ordr], r-LL[ordr]+1);
        merge(merge, ret, pref);
        it1++;
        while (it1 != it2) {
            merge(merge, ret, roots[*it1]);
            auto d = it1;
            it1++;
            st.erase(d);
        }
        if (l == LL[ordl]) {
            st.erase(ordl); // если левый плохой то удалили
        }
        it2++;
        if (r == n-1 || (it2 != st.end() && LL[*it2] == r+1)) {
            // если правый плохой то удалили
            st.erase(ordr);
        } else {
            // иначе подвинули
            st.erase(ordr);
            LL[ordr] = r+1;
            st.insert(ordr);
        }
        assert(su(ret) == r-l+1);
        LL[C] = l;
//        cout << C << "!!\n";
        st.insert(C);
        roots[C] = ret;
        auto ml = st.lower_bound(C);
        if (ml != st.begin()) {
            ml--;
            if (tree[roots[*ml]].mx <= tree[roots[C]].mn) {
                merge(merge, roots[*ml], roots[C]);
                st.erase(C);
            }
        }
        auto it = st.upper_bound(C);
        assert(it != st.begin());
        it--;
        auto mr = st.upper_bound(C);
        if (mr != st.end()) {
            if (tree[roots[*it]].mx <= tree[roots[*mr]].mn) {
                merge(merge, roots[*it], roots[*mr]);
                st.erase(*mr);
            }
        }
        C += 1;
    }
}
