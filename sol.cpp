#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int>> val_and_idx(n);
    vector<int> a(n);
    for (int i = 0; i < n; i += 1) {
        cin >> a[i];
        val_and_idx[i] = {a[i], i};
    }
    sort(val_and_idx.begin(), val_and_idx.end());
    vector<vector<int>> tree(4*n+10);
    auto build = [&] (auto f, int u, int tl, int tr) -> void {
        if (tl == tr) {
            tree[u] = {val_and_idx[tl].second};
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, 2*u+1, tl, tm);
        f(f, 2*u+2, tm+1, tr);
        tree[u].resize(tr-tl+1);
        merge(tree[2*u+1].begin(), tree[2*u+1].end(), tree[2*u+2].begin(), tree[2*u+2].end(), tree[u].begin());
    };
    build(build, 0, 0, n-1);
    auto go = [&] (auto f, int u, int tl, int tr, int l, int r, int k) -> int {
        if (tl == tr) {
            return tree[u].front();
        }
        int tm = (tl + tr) >> 1;
        int left = upper_bound(tree[2*u+1].begin(), tree[2*u+1].end(), r)
                 - lower_bound(tree[2*u+1].begin(), tree[2*u+1].end(), l);
        if (left > k) {
            return f(f, 2*u+1, tl, tm, l, r, k);
        }
        return f(f, 2*u+2, tm+1, tr, l, r, k-left);
    };
    for (int qq = 0; qq < q; qq += 1) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << a[go(go, 0, 0, n-1, l, r-1, k)] << "\n";
    }
}