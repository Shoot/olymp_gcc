#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i += 1) {
        cin >> a[i];
    }
    vector<int> b;
    for (int i = 0; i < 3; i += 1)
        for (const auto &x : a) {
            b.push_back(x);
        }
    vector<int> pref(b.size());
    for (int i = 0; i < b.size(); i += 1) {
        pref[i] = b[i];
        if (i) {
            pref[i] += pref[i-1];
        }
    }
    int we_do = n/2+n%2;
    int maxi = 0;
    vector<int> tree(4*(3*n)+10, 1e9);
    auto mineq = [&] (auto f, int u, int tl, int tr, int l, int r, int val) -> void {
        if (tl == l && tr == r) {
            tree[u] = min(tree[u], val);
            return;
        }
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l,tm+1), r, val);
        }
    };
    auto gt = [&] (auto f, int u, int tl, int tr, int pos) -> int {
        if (tl == tr) {
            return tree[u];
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return min(tree[u], f(f, 2*u+1, tl, tm, pos));
        } else {
            return min(tree[u], f(f, 2*u+2, tm+1, tr, pos));
        }
    };
    for (int start = 0; start+we_do-1 < 3*n; start += 1) {
        int val = pref[start+we_do-1]-(start?pref[start-1]:0);
        mineq(mineq, 0, 0, 3*n-1, start, start+we_do-1, val);
    }
    for (int i = n; i-n < n; i += 1) {
        int mini = 1e9;
        maxi = max(maxi, gt(gt, 0, 0, 3*n-1, i));
    }
    cout << maxi << "\n";
}