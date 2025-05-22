#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> p(n+m);
    vector<int> sz(n+m, 1);
    iota(p.begin(), p.end(), 0ll);
    auto find = [&] (auto f, int u) -> int {
        return p[u] == u ? u : f(f, p[u]);
    };
    auto unite = [&] (int u, int v) -> void {
        u = find(find, u);
        v = find(find, v);
        if (u != v) {
            if (sz[u] > sz[v]) {
                swap(u, v);
            }
            p[u] = v;
            sz[v] += sz[u];
        }
    };
    vector<pair<int,int>> edges;
    for (int i = 0; i < q; i += 1) {
        int I, J;
        char val;
        cin >> I >> J >> val;
        if (val == 'B') {
            edges.push_back({I-1, n+J-1});
        } else {
            edges.push_back({n+J-1, I-1});
        }
    }
    auto E = edges;
    vector<vector<int>> change(q);
    vector<int> curr(edges.size());
    iota(curr.begin(), curr.end(), 0ll);
    vector<int> comp_idx(n+m);
    vector<int> topo;
    topo.reserve(1e6);
    vector<bool> seen(1e6);
    auto assign_comp_idxes = [&] (const vector<forward_list<int>>& adj_curr, const vector<forward_list<int>>& iadj_curr) -> void {
        int N = adj_curr.size();
        fill(seen.begin(), seen.begin()+N, false);
        auto dfs = [&] (auto f, int u) -> void {
            if (seen[u]) {
                return;
            }
            seen[u] = true;
            for (const auto &x : adj_curr[u]) {
                f(f, x);
            }
            topo.push_back(u);
        };
        topo.clear();
        for (int i = 0; i < N; i += 1) {
            dfs(dfs, i);
        }
        reverse(topo.begin(), topo.end());
        auto mark = [&] (auto f, int u) -> void {
            seen[u] = true;
            for (const auto &x : iadj_curr[u]) {
                if (!seen[x]) {
                    comp_idx[x] = comp_idx[u];
                    f(f, x);
                }
            }
        };
        int curr_comp_idx = 0;
        fill(seen.begin(), seen.begin()+N, false);
        for (const auto &x : topo) {
            if (!seen[x]) {
                comp_idx[x] = curr_comp_idx++;
                mark(mark, x);
            }
        }
    };
    vector<int> id(n+m, -1);
    vector<int> by_id(n+m, -1);
    auto go = [&] (auto f, int l, int r, int le, int re) -> void { // l, r -- это про бинпоиск
        if (!(le <= re) || !(l <= r)) {
            return;
        }
        vector<forward_list<int>> adj, iadj;
        int mid = (l + r) >> 1;
        for (int i = le; i <= re; i += 1) {
            auto &[u, v] = edges[curr[i]];
            for (const auto &w : {u, v}) {
                if (id[w] == -1) {
                    id[w] = adj.size();
                    by_id[id[w]] = w;
                    adj.push_back({});
                    iadj.push_back({});
                }
            }
            u = id[u];
            v = id[v];
            if (curr[i] <= mid) {
                adj[u].push_front(v);
                iadj[v].push_front(u);
            }
        }
        // clear id array
        for (int i = 0; i < adj.size(); i += 1) {
            id[by_id[i]] = -1;
        }
        assign_comp_idxes(adj, iadj);
        int first_diff = partition(curr.begin()+le, curr.begin()+re+1, [&] (const int& e) {
            return comp_idx[edges[e].first] == comp_idx[edges[e].second];
        }) - curr.begin();
        for (int i = le; i < first_diff; i += 1) {
            change[mid].push_back(curr[i]);
        }
        if (l == r) {
            return;
        }
        for (int i = first_diff; i <= re; i += 1) {
            auto &[u, v] = edges[curr[i]];
            u = comp_idx[u];
            v = comp_idx[v];
        }
        f(f, l, mid-1, le, first_diff-1);
        f(f, mid+1, r, first_diff, re);
    };
    go(go, 0, q-1, 0, q-1);
    int ans = 0;
    for (int i = 0; i < q; i += 1) {
        for (const auto &edge_idx : change[i]) {
            auto u = find(find, E[edge_idx].first);
            auto v = find(find, E[edge_idx].second);
            if (u != v) {
                if (sz[u] > 1) {
                    ans -= sz[u] * sz[u];
                }
                if (sz[v] > 1) {
                    ans -= sz[v] * sz[v];
                }
                ans += (sz[u] + sz[v]) * (sz[u] + sz[v]);
                unite(u, v);
            }
        }
        cout << ans << "\n";
    }
}