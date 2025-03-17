#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> comp_su(n);
    for (auto &x : comp_su) {
        cin >> x;
    }
    vector<pair<int,int>> edges(q, {-1,-1});
    map<pair<int,int>,int> idx;
    vector<int> edge_end(q, -1);
    struct Query {
        int tp;
        int edge_idx;
        int u;
        int inc;
    };
    vector<vector<Query>> tree(4*q+10);
    auto add_edge = [&] (auto f, int u, int tl, int tr, int l, int r, Query qq) -> void {
        if (tl == l && tr == r) {
            tree[u].push_back(qq);
            return;
        }
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), qq);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, qq);
        }
    };
    for (int i = 0; i < q; i += 1) {
        int tp;
        cin >> tp;
        if (tp == 0) {
            int u, v;
            cin >> u >> v;
            edges[i] = {u, v};
            idx[{u,v}] = i;
            idx[{v,u}] = i;
        }
        if (tp == 1) {
            int u, v;
            cin >> u >> v;
            edge_end[idx[{u,v}]] = i;
        }
        if (tp == 2) {
            int u, x;
            cin >> u >> x;
            add_edge(add_edge, 0, 0, q-1, i, q-1, {2, -1, u, x});
        }
        if (tp == 3) {
            int u;
            cin >> u;
            add_edge(add_edge, 0, 0, q-1, i, i, {3, -1, u, -1});
        }
    }
    for (int i = 0; i < q; i += 1) {
        if (edges[i].first != -1) {
            add_edge(add_edge, 0, 0, q-1, i, edge_end[i]!=-1?edge_end[i]:q-1, {0, i, -1, -1});
        }
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    vector<int> sz(n, 1);
    vector<pair<int&,int>> history;
    auto find = [&] (auto f, int u) -> int {
        return p[u] == u ? u : f(f, p[u]);
    };
    auto add = [&] (auto f, int u, int inc) -> void {
        u = find(find, u);
        history.push_back({comp_su[u], comp_su[u]});
        comp_su[u] += inc;
    };
    auto unite = [&] (int u, int v) -> void {
        u = find(find, u);
        v = find(find, v);
        if (u != v) {
            if (sz[u] > sz[v]) {
                swap(u, v);
            }
            history.push_back({p[u], p[u]});
            p[u] = v;
            history.push_back({sz[v], sz[v]});
            sz[v] += sz[u];
            history.push_back({comp_su[v], comp_su[v]});
            comp_su[v] += comp_su[u];
        }
    };
    auto dfs = [&] (auto f, int u, int tl, int tr) -> void {
        int b4 = history.size();
        for (const auto &[tp, edge_idx, U, inc] : tree[u]) {
            if (tp == 0) {
                unite(edges[edge_idx].first, edges[edge_idx].second);
            }
            if (tp == 2) {
                add(add, U, inc);
            }
        }
        for (const auto &[tp, edge_idx, U, inc] : tree[u]) {
            if (tp == 3) {
                cout << comp_su[find(find, U)] << "\n";
            }
        }
        if (tl != tr) {
            int tm = (tl + tr) >> 1;
            f(f, 2*u+1, tl, tm);
            f(f, 2*u+2, tm+1, tr);
        }
        while (history.size() > b4) {
            history.back().first = history.back().second;
            history.pop_back();
        }
    };
    dfs(dfs, 0, 0, q-1);
}