#include <bits/stdc++.h>
using namespace std;
//#define int long long
signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    long long ans = 0;
    // массив позиций элемента value на отрезке [l, r]
    vector<vector<pair<int,int>>> tree(4*n+10);
    auto build = [&] (auto f, int u, int tl, int tr) -> void {
        if (tl == tr) {
            tree[u] = {{a[tl], tl}};
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, 2*u+1, tl, tm);
        f(f, 2*u+2, tm+1, tr);
        int it1 = 0;
        int it2 = 0;
        for (int i = 0; i < tr-tl+1; i += 1) {
            if (it1 == tree[2*u+1].size() || it2 != tree[2*u+2].size() && tree[2*u+2][it2] < tree[2*u+1][it1]) {
                tree[u].push_back(tree[2*u+2][it2++]);
            } else {
                tree[u].push_back(tree[2*u+1][it1++]);
            }
        }
    };
    build(build, 0, 0, n-1);
    vector<int> ret;
    auto gt = [&] (auto f, int u, int tl, int tr, int l, int r, int val) -> void {
        if (l == tl && r == tr) {
            auto it = lower_bound(tree[u].begin(), tree[u].end(), pair<int,int>{val, -1e9}); // tree[u].begin()
            auto it2 = upper_bound(tree[u].begin(), tree[u].end(), pair<int,int>{val, 1e9});
            while (it != it2) {
                ret.push_back(it->second);
                it += 1;
            }
            return;
        }
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, val);
        }
    };
    vector<vector<int>> ST(20, vector<int>(n));
    ST[0] = a;
    for (int i = 1; i < 20; i += 1) {
        for (int j = 0; j < n; j += 1) {
            ST[i][j] = ST[i-1][j];
            int sz = 1 << (i-1);
            if (j+sz < n) {
                ST[i][j] = min(ST[i][j], ST[i-1][j+sz]);
            }
        }
    }
    auto gt_min = [&] (int l, int r) -> int {
        int sz = __lg(r-l+1);
        return min(ST[sz][l], ST[sz][r-(1<<sz)+1]);
    };
    auto godo = [&] (auto f, int l, int r) -> void {
        if (l > r) {
            return;
        }
        ret.clear();
        gt(gt, 0, 0, n-1, l, r, gt_min(l, r));
        assert(ret.size());
        int i = ret[(ret.size()-1)/2];
        int j = i;
        while (j >= l && a[j] % a[i] == 0) {
            j -= 1;
        }
        long long szl = i-j;
        j = i;
        while (j <= r && a[j] % a[i] == 0) {
            j += 1;
        }
        long long szr = j-i;
        ans += szl*szr;
        f(f, l, i-1);
        f(f, i+1, r);
    };
    godo(godo, 0, n-1);
    cout << ans << "\n";
}