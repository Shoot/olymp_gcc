#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <random>
#include <chrono>
#include <bitset>
using namespace std;
void solve() {
    long long n, m;
    cin >> n >> m;
    vector<vector<int>> sm(n+1);
    vector<pair<int, int>> edges;
    vector<multiset<int>> sms(n+1);
    for (int i = 0; i < m; i += 1) {
        int u, v;
        cin >> u >> v;
        sm[u].push_back(v);
        sms[u].insert(v);
        sm[v].push_back(u);
        sms[v].insert(u);
        edges.push_back(make_pair(u, v));
        edges.push_back(make_pair(v, u));
    }
    bitset<1'000'000> seen;
    vector<int> depth(n+1);
    vector<int> up_in_subtree(n+1);
    auto dfs = [&] (auto f, int v, int h) -> void {
        seen[v] = true;
        depth[v] = h;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x, h+1);
            }
        }
    };
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            dfs(dfs, i, 1);
        }
    }
    seen.reset();
    auto dfs2 = [&] (auto f, int v, int par) -> void {
        seen[v] = true;
        up_in_subtree[v] = depth[v];
        for (const auto &x : sm[v]) {
            if (seen[x] && x != par || sms[v].count(par) > 1) {
                up_in_subtree[v] = min(up_in_subtree[v], depth[x]);
            }
        }
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x, v);
                up_in_subtree[v] = min(up_in_subtree[v], up_in_subtree[x]);
            }
        }
    };
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            dfs2(dfs2, i, -1);
        }
    }
    seen.reset();
    vector<int> sz(n+1, 1);
    auto calc_sz = [&] (auto f, int v) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x);
                sz[v] += sz[x];
            }
        }
    };
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            calc_sz(calc_sz, i);
        }
    }
    int bridges = 0;
    long long mini = n*(n-1)/2;
    for (const auto &[u, v] : edges) {
        if (depth[u] < up_in_subtree[v]) {
            long long x = min(sz[v], sz[u]);
            long long y = n-x;
            mini = min(mini, x*(x-1)/2+y*(y-1)/2);
            clog << u << " " << v << endl;
            bridges += 1;
        }
    }
    cout << mini << endl;
}

int32_t main() {
    int tt; cin >> tt;
    for (int T = 0; T < tt; T += 1) solve();
    return 0;
}
