#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n;
    cin >> n;
    vector<int> leafs;
    vector<vector<int>> adj(n+1);
    for (int i = 1; i <= n; i += 1) {
        int sz;
        cin >> sz;
        adj[i].resize(sz);
        for (auto &x : adj[i]) {
            cin >> x;
        }
    }
    vector<int> rightest_child(n+1, -1);
    vector<int> leftest_child(n+1, n);
    vector<int> d(n+1);
    vector<vector<int>> binup(20, vector<int>(n+1));
    binup[0][1] = 1;
    auto dfs = [&] (auto f, int u) -> void {
        if (adj[u].empty()) {
            leafs.push_back(u);
            rightest_child[u] = leafs.size()-1;
            leftest_child[u] = leafs.size()-1;
            return;
        }
        for (const auto &x : adj[u]) {
            d[x] = d[u] + 1;
            binup[0][x] = u;
            f(f, x);
            rightest_child[u] = max(rightest_child[u], rightest_child[x]);
            leftest_child[u] = min(leftest_child[u], leftest_child[x]);
        }
    };
    dfs(dfs, 1);
    for (int i = 1; i < 20; i += 1) {
        for (int u = 1; u <= n; u += 1) {
            binup[i][u] = binup[i-1][binup[i-1][u]];
        }
    }
    auto LCA = [&] (int u, int v) -> int {
        if (d[u] < d[v]) {
            swap(u, v);
        }
        int diff = d[u] - d[v];
        for (int i = 0; i < 20; i += 1) {
            if (diff&(1<<i)) {
                u = binup[i][u];
            }
        }
        assert(d[u] == d[v]);
        if (u == v) {
            return u;
        }
        for (int i = 19; i >= 0; i -= 1) {
            if (binup[i][u] != binup[i][v]) {
                u = binup[i][u];
                v = binup[i][v];
            }
        }
        assert(u != v);
        assert(binup[0][u] == binup[0][v]);
        return binup[0][u];
    };
    int q;
    cin >> q;
    set<tuple<int,int, int>> st;
    for (int i = 0; i < q; i += 1) {
        int tp, u;
        cin >> tp >> u;
        if (tp == 1) {
            st.insert({rightest_child[u], d[u], u});
            st.insert({leftest_child[u], d[u], u});
        } else {
            st.erase({rightest_child[u], d[u], u});
            st.erase({leftest_child[u], d[u], u});
        }
        if (st.empty()) {
            cout << 0 << "\n";
        } else if (st.size() > 1) {
            auto temp = LCA(leafs[get<0>(*st.begin())], leafs[get<0>(*st.rbegin())]);
            cout << temp << "\n";
        } else {
            cout << get<1>(*st.begin()) << "\n";
        }
    }
}