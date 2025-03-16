#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i += 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n+1);
    vector<int> p(n+1, -1e9);
    vector<int> tin(n+1, -1), tout(n+1, -1);
    int t = 0;
    auto dfs = [&] (auto f, int u) -> void {
        sz[u] = 1;
        for (auto &x : adj[u]) {
            if (x != p[u]) {
                p[x] = u;
                f(f, x);
                sz[u] += sz[x];
                if (adj[u].front() == p[u] || sz[x] > sz[adj[u].front()]) {
                    swap(x, adj[u].front());
                }
            }
        }
    };
    dfs(dfs, 1);
    for (int i = 1; i <= n; i += 1) {
        if (adj[i].size() == 1) {
            continue;
        }
        assert(p[i] != adj[i][0]);
    }
    vector<int> top(n+1, -1);
    auto hld = [&] (auto f, int u) -> void {
        tin[u] = t++;
        for (const auto &x : adj[u]) {
            if (x != p[u]) {
                if (x == adj[u][0]) {
                    top[x] = top[u];
                } else {
                    top[x] = x;
                }
                f(f, x);
            }
        }
        tout[u] = t;
    };
    top[1] = 1;
    hld(hld, 1);
    auto second_inside = [&] (int a, int b) -> bool {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    };
    auto A = a;
    for (int i = 1; i <= n; i += 1) {
        A[tin[i]] = a[i];
    }
    vector<vector<int>> ST(4*n+10);
    auto build = [&] (auto f, int u, int tl, int tr) -> void {
        if (tl == tr) {
            ST[u] = {A[tl]};
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, 2*u+1, tl, tm);
        f(f, 2*u+2, tm+1, tr);
        ST[u].resize(tr-tl+1);
        merge(ST[2*u+1].begin(), ST[2*u+1].end(), ST[2*u+2].begin(), ST[2*u+2].end(), ST[u].begin());
    };
    build(build, 0, 0, n-1);
    auto gt = [&] (auto f, int u, int tl, int tr, int l, int r, int val) -> int {
        if (tl == l && tr == r) {
            auto it = upper_bound(ST[u].begin(), ST[u].end(), val);
            if (it == ST[u].end()) {
                return 2e9;
            }
            return *it;
        }
        int tm = (tl + tr) >> 1;
        int ret = 2e9;
        if (l <= tm) {
            ret = min(ret, f(f, 2*u+1, tl, tm, l, min(r, tm), val));
        }
        if (r >= tm+1) {
            ret = min(ret, f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, val));
        }
        return ret;
    };
    auto up = [&] (int& a, const int& b, int& ans, const int& x) {
        while (!second_inside(top[a], b)) {
            ans = min(ans, gt(gt, 0, 0, n-1, tin[top[a]], tin[a], x));
            a = p[top[a]];
        }
    };
    for (int i = 0; i < q; i += 1) {
        int u, v, x;
        cin >> u >> v >> x;
        int ans = 2e9;
        up(u, v, ans, x);
        up(v, u, ans, x);
        ans = min(ans, gt(gt, 0, 0, n-1, min(tin[u], tin[v]), max(tin[u], tin[v]), x));
        cout << (ans==2e9?-1:ans) << "\n";
    }
}