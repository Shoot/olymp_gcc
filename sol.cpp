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
    struct Node {
        int suff = 0;
        int pref = 0;
        int overall = 0;
        int whole = 0;
    };
    auto gomerge = [&] (const Node& a, const Node& b) -> Node {
        Node ret = Node();
        ret.whole = a.whole + b.whole;
        ret.pref = max(a.pref, a.whole+b.pref);
        ret.suff = max(b.suff, a.suff+b.whole);
        ret.overall = max({a.overall, b.overall, a.suff+b.pref});
        return ret;
    };
    vector<Node> ST(4*n+10);
    auto st = [&] (auto f, int u, int tl, int tr, int pos, int val) -> void {
        if (tl == tr) {
            ST[u].pref = max(0ll,val);
            ST[u].suff = max(0ll,val);
            ST[u].overall = max(0ll,val);
            ST[u].whole = val;
            return;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            f(f, 2*u+1, tl, tm, pos, val);
        } else {
            f(f, 2*u+2, tm+1, tr, pos, val);
        }
        ST[u] = gomerge(ST[2*u+1], ST[2*u+2]);
    };
    auto gt = [&] (auto f, int u, int tl, int tr, int l, int r) -> Node {
        if (tl == l && tr == r) {
            return ST[u];
        }
        int tm = (tl + tr) >> 1;
        Node ret = Node();
        if (l <= tm) {
            ret = gomerge(ret, f(f, 2*u+1, tl, tm, l, min(r, tm)));
        }
        if (r >= tm+1) {
            ret = gomerge(ret, f(f, 2*u+2, tm+1, tr, max(l, tm+1), r));
        }
        return ret;
    };
    auto up = [&] (int& a, const int& b, Node& ans) -> Node {
        vector<pair<int,int>> temp;
        while (!second_inside(top[a], b)) {
            temp.push_back({tin[top[a]], tin[a]});
            a = p[top[a]];
        }
        for (const auto &[x, y] : temp) {
            ans = gomerge(gt(gt, 0, 0, n-1, x, y), ans);
        }
        return ans;
    };
    for (int i = 1; i <= n; i += 1) {
        st(st, 0, 0, n-1, tin[i], a[i]);
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
            Node from_u = Node();
            Node from_v = Node();
            up(u, v, from_u);
            up(v, u, from_v);
            if (tin[u] < tin[v]) {
                swap(from_u, from_v);
                swap(u, v);
            }
            // u @ bottom
            swap(from_v.pref, from_v.suff); // reverse one half (i choose to reverse the one that goes to the top)
            auto shit = gt(gt, 0, 0, n-1, min(tin[u], tin[v]), max(tin[u], tin[v]));
            from_u = gomerge(shit, from_u);
            cout << gomerge(from_v,from_u).overall << "\n";
        }
    }
}