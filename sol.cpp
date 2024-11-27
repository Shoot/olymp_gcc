#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <random>
#include <chrono>
#include <bitset>
#include <assert.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distrib(1, 10);
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
    auto dfs = [&] (auto f, int v, int par) -> void {
        if (par >= 1 && par != v) depth[v] = depth[par] + 1;
        seen[v] = true;
        up_in_subtree[v] = depth[v];
        for (const auto &x : sm[v]) {
            if (x != par || sms[v].count(par) > 1) {
                if (seen[x]) {
                    up_in_subtree[v] = min(up_in_subtree[v], depth[x]);
                }
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
            depth[i] = 1;
            dfs(dfs, i, -1);
        }
    }
    vector<int> gde_v_slabaya(n+1);
    int base = 0;
    for (const auto &[u, v] : edges) {
        if (depth[u] < up_in_subtree[v]) {
            clog << u << " " << v << endl;
            gde_v_slabaya[v] += 1;
            base += 1;
        }
    }
    // для всех вершин сумму на пути от корня — найти макс такой суммы
    // это добавление обратного ребра
    int MAXI = 0;
    vector<int> max_on_path_to_leaf(n+1);
    auto find_max = [&] (auto f, int v) -> void {
        seen[v] = true;
        vector<int> children;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x);
                children.push_back(max_on_path_to_leaf[x]);
            }
        }
        sort(children.rbegin(), children.rend());
        if (children.size() > 1) {
            MAXI = max(MAXI, children[0]+children[1]);
        }
        max_on_path_to_leaf[v] = gde_v_slabaya[v];
        if (children.size() > 0) max_on_path_to_leaf[v] += children[0];
    };
    seen.reset();
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            find_max(find_max, i);
            MAXI = max(MAXI, max_on_path_to_leaf[i]);
        }
    }
    int ans = base-MAXI;
    cout << ans << endl;
}

int32_t main() {
    solve();
    return 0;
}
