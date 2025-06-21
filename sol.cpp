#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
//constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
constexpr int INF = 1e18;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
//    int T=1;
//    cin >> T;
//    for (int tt = 0; tt < T; tt += 1) {
//    }
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    for (int i = 0; i < n-1; i += 1) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> tin1(n), tout1(n), tin2(n), tout2(n);
    int t1 = 0;
    vector<vector<int>> up(20, vector<int>(n));
    vector<int> d(n);
    auto dfs1 = [&] (auto f, int u, int p) -> void {
        tin1[u] = t1++;
        for (const auto &x : adj[u]) {
            if (x != p) {
                d[x] = d[u]+1;
                up[0][x] = u;
                f(f, x, u);
            }
        }
        tout1[u] = t1-1;
    };
    int t2 = 0;
    auto dfs2 = [&] (auto f, int u, int p) -> void {
        tin2[u] = t2;
        for (const auto &x : adj[u]) {
            if (x != p) {
                f(f, x, u);
            }
        }
        tout2[u] = t2++;
    };
    dfs1(dfs1, 0, -1);
    dfs2(dfs2, 0, -1);
    for (int i = 1; i < 20; i += 1) {
        for (int j = 0; j < n; j += 1) {
            up[i][j] = up[i-1][up[i-1][j]];
        }
    }
    struct Node {
        int val=0;
        int lz=0;
    };
    auto push = [&] (int u, int tl, int tr, vector<Node>& ST) -> void {
        int tm = (tl + tr) >> 1;
        int szl = tm-tl+1;
        int szr = tr-(tm+1)+1;
        ST[2*u+1].lz += ST[u].lz;
        ST[2*u+1].val += ST[u].lz*szl;
        ST[2*u+2].lz += ST[u].lz;
        ST[2*u+2].val += ST[u].lz*szr;
        ST[u].lz = 0;
    };
    auto inc = [&] (auto f, int u, int tl, int tr, int l, int r, int x, vector<Node>& ST) -> void {
        if (tl == l && tr == r) {
            ST[u].val += x*(tr-tl+1);
            ST[u].lz += x;
            return;
        }
        int tm = (tl + tr) >> 1;
        push(u, tl, tr, ST);
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), x, ST);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(tm+1, l), r, x, ST);
        }
        ST[u].val = ST[2*u+1].val + ST[2*u+2].val;
    };
    auto gt = [&] (auto f, int u, int tl, int tr, int l, int r, vector<Node>& ST) -> int {
        if (tl == l && tr == r) {
            return ST[u].val;
        }
        int tm = (tl + tr) >> 1;
        push(u, tl, tr, ST);
        int ret = 0;
        if (l <= tm) {
            ret += f(f, 2*u+1, tl, tm, l, min(r, tm), ST);
        }
        if (r >= tm+1) {
            ret += f(f, 2*u+2, tm+1, tr, max(tm+1, l), r, ST);
        }
        return ret;
    };
    vector<Node> _1(4*n+10), _2(4*n+10);
    auto gt_on_path_to_root = [&] (int u) -> int {
        int ret = gt(gt, 0, 0, n-1, 0, tout1[u], _1);
        if (tout2[u]-1 >= 0) {
            ret -= gt(gt, 0, 0, n-1, 0, tout2[u]-1, _2);
        }
        return ret;
    };
    auto inc_vertex = [&] (int u, int x) -> void {
        inc(inc, 0, 0, n-1, tin1[u], tin1[u], x, _1);
        inc(inc, 0, 0, n-1, tout2[u], tout2[u], x, _2);
    };
    auto gt_vertex = [&] (int u) -> int {
        return gt(gt, 0, 0, n-1, tout2[u], tout2[u], _2);
    };
    auto inc_subtree = [&] (int u, int x) -> void {
        inc(inc, 0, 0, n-1, tin1[u], tout1[u], x, _1);
        inc(inc, 0, 0, n-1, tin2[u], tout2[u], x, _2);
    };
    auto gt_subtree = [&] (int u) -> int {
        return gt(gt, 0, 0, n-1, tin1[u], tout1[u], _1);
    };
    auto LCA = [&] (int u, int v) -> int {
        if (d[u] < d[v]) {
            swap(u, v);
        }
        int diff = d[u] - d[v];
        for (int i = 0; i < 20; i += 1) {
            if (diff&(1<<i)) {
                u = up[i][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = 19; i >= 0; i -= 1) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    };
    auto gt_path = [&] (int u, int v) -> int {
        int lca = LCA(u, v);
        int ret = 0;
        ret += gt_on_path_to_root(u);
        ret += gt_on_path_to_root(v);
        ret -= gt_vertex(lca);
        if (up[0][lca] != lca) {
            ret -= 2ll*gt_on_path_to_root(up[0][lca]);
        }
        return ret;
    };
    for (int i = 0; i < n; i += 1) {
        inc_vertex(i, a[i]);
    }
    for (int ii = 0; ii < q; ii += 1) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int u, x;
            cin >> u >> x;
            u -= 1;
            inc_vertex(u, x-gt_vertex(u));
        }
        if (tp == 2) {
            int u, v;
            cin >> u >> v;
            u -= 1, v -= 1;
            cout << gt_path(u, v) << "\n";
        }
    }
}