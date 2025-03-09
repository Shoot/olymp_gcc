#include <bits/stdc++.h>
using namespace std;
const int C = 250;
signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    auto b = a; b.erase(b.begin());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    // Можно прибавлять эту единицу на суффиксе и отвечать минимум на всем массиве, при чем не забудем отнять от всего l-1
    // a[i] - значение для последнего числа i в отсортированном текущем подмассиве
    struct Node {
        int val = 2e9;
        int lz = 0;
    };
    vector<Node> ST(4*5e4+10);
    auto push = [&] (int u) -> void {
        ST[2*u+1].lz += ST[u].lz;
        ST[2*u+1].val += ST[u].lz;
        ST[2*u+2].lz += ST[u].lz;
        ST[2*u+2].val += ST[u].lz;
        ST[u].lz = 0;
    };
    auto inc = [&] (auto f, int u, int tl, int tr, int l, int r, int val) -> void {
        if (tl == l && tr == r) {
            ST[u].val += val;
            ST[u].lz += val;
            return;
        }
        push(u);
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, val);
        }
        ST[u].val = min(ST[2*u+1].val, ST[2*u+2].val);
    };
    vector<int> cnt(5e5);
    auto rel = [&] (int x) -> int {
        return lower_bound(b.begin(), b.end(), x) - b.begin();
    };
    auto add = [&] (int x) -> void {
        int y = rel(x);
        if (!(cnt[y]++)) {
            inc(inc, 0, 0, 5e4, y, y, -2e9);
            inc(inc, 0, 0, 5e4, y, y, x);
        }
        inc(inc, 0, 0, 5e4, y, 5e4, -1);
    };
    auto remove = [&] (int x) -> void {
        int y = rel(x);
        if (!(--cnt[y])) {
            inc(inc, 0, 0, 5e4, y, y, 2e9);
            inc(inc, 0, 0, 5e4, y, y, -x);
        }
        inc(inc, 0, 0, 5e4, y, 5e4, 1);
    };
    struct Query {
        int l;
        int r;
        int idx;
        auto operator<=>(const Query &other) const {
            return make_tuple(l/C, r, idx) < make_tuple(other.l/C, other.r, other.idx);
        }
    };
    vector<Query> queries(q);
    for (int i = 0; i < q; i += 1) {
        int l, r;
        cin >> l >> r;
        queries[i] = {l, r, i};
    }
    vector<int> ans(q);
    sort(queries.begin(), queries.end());
    int last_l = 1;
    int last_r = 0;
    for (const auto [l, r, idx] : queries) {
        while (r > last_r) {
            add(a[++last_r]);
        }
        while (l < last_l) {
            add(a[--last_l]);
        }
        while (last_l < l) {
            remove(a[last_l++]);
        }
        while (last_r > r) {
            remove(a[last_r--]);
        }
        ans[idx] = ST.front().val - (l-1);
    }
    for (const auto &x : ans) {
        cout << x << "\n";
    }
}