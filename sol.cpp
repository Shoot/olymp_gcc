#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> tree(4*n+5);
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    auto build = [&] (auto f, int v, int tl, int tr) -> void {
        for (int i = tl; i <= tr; i += 1) {
            tree[v].push_back(a[i]);
        }
        sort(tree[v].begin(), tree[v].end());
        if (tl == tr) {
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, 2 * v + 1, tl, tm);
        f(f, 2 * v + 2, tm+1, tr);
    };
    build(build, 0, 0, n-1);
    auto answer = [&] (auto f, int v, int tl, int tr, int l, int r, int val) -> int {
        if (tl == l && tr == r) {
            return upper_bound(tree[v].begin(), tree[v].end(), val) - tree[v].begin();
        }
        int ans = 0;
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            ans += f(f, 2 * v + 1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm + 1) {
            ans += f(f, 2 * v + 2, tm + 1, tr, max(l, tm + 1), r, val);
        }
        return ans;
    };
    for (int i = 0; i < m; i += 1) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << answer(answer, 0, 0, n-1, l, r, x) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tt = 1; tt <= T; tt += 1) {
        cout << "Case " << tt << ":\n";
        solve();
    }
}