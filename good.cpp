#include <bits/stdc++.h>
using namespace std;
#define int long long
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
                if (sz[x] > sz[adj[u].front()]) {
                    swap(x, adj[u].front());
                }
            }
        }
    };
    dfs(dfs, 1);
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
    struct Node {
        int su = 0;
        int lz = 0;
    };
    vector<Node> ST(4*n+10);
    auto push = [&] (int u, int tl, int tr) -> void {
        int tm = (tl + tr) >> 1;
        int szl = tm-tl+1;
        int szr = tr-(tm+1)+1;
        ST[2*u+1].lz += ST[u].lz;
        ST[2*u+1].su += ST[u].lz*szl;
        ST[2*u+2].lz += ST[u].lz;
        ST[2*u+2].su += ST[u].lz*szr;
        ST[u].lz = 0;
    };
    auto st = [&] (auto f, int u, int tl, int tr, int pos, int val) -> void {
        if (tl == tr) {
            ST[u].su = val;
            return;
        }
        push(u, tl, tr);
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            f(f, 2*u+1, tl, tm, pos, val);
        } else {
            f(f, 2*u+2, tm+1, tr, pos, val);
        }
        ST[u].su = ST[2*u+1].su + ST[2*u+2].su;
    };
    auto inc = [&] (auto f, int u, int tl, int tr, int l, int r, int val) -> void {
        if (tl == l && tr == r) {
            ST[u].lz += val;
            ST[u].su += val*(tr-tl+1);
            return;
        }
        push(u, tl, tr);
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, val);
        }
        ST[u].su = ST[2*u+1].su + ST[2*u+2].su;
    };
    auto gt = [&] (auto f, int u, int tl, int tr, int l, int r) -> int {
        if (tl == l && tr == r) {
            return ST[u].su;
        }
        push(u, tl, tr);
        int tm = (tl + tr) >> 1;
        int ret = 0;
        if (l <= tm) {
            ret += f(f, 2*u+1, tl, tm, l, min(r, tm));
        }
        if (r >= tm+1) {
            ret += f(f, 2*u+2, tm+1, tr, max(l, tm+1), r);
        }
        return ret;
    };
    auto up = [&] (int& a, const int& b, int& ans) {
        while (!second_inside(top[a], b)) {
            ans += gt(gt, 0, 0, n-1, tin[top[a]], tin[a]);
            a = p[top[a]];
        }
    };
    for (int i = 1; i <= n; i += 1) {
        inc(inc, 0, 0, n-1, tin[i], tin[i], a[i]);
    }
    for (int i = 0; i < q; i += 1) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int u, x;
            cin >> u >> x;
            st(st, 0, 0, n-1, tin[u], x);
        } else {
            int u, v;
            cin >> u >> v;
            int ans = 0;
            up(u, v, ans);
            up(v, u, ans);
            ans += gt(gt, 0, 0, n-1, min(tin[u], tin[v]), max(tin[u], tin[v]));
            cout << ans << "\n";
        }
    }
}