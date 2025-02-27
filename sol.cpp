#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main () {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cap(2*n+2, vector<int>(2*n+2));
    for (int i = 1; i <= n; i += 1) {
        cap[2*i][2*i+1] = 1;
    }
    vector<set<int>> xx(n+1);
    for (int i = 0; i < m; i += 1) {
        int u, v;
        cin >> u >> v;
        xx[u].insert(v);
        xx[v].insert(u);
        cap[2*u+1][2*v] = 1e9;
        cap[2*v+1][2*u] = 1e9;
    }
    vector<int> par;
    vector<int> curr;
    curr.reserve(1000);
    auto min_cut = [&] (int src, int snk) -> int {
        curr.clear();
        vector<vector<int>> adj(2*n+2);
        for (int i = 0; i <= 2*n+1; i += 1) {
            for (int j = 0; j <= 2*n+1; j += 1) {
                if (cap[i][j] != 0) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        auto find_shortest = [&] () -> int {
            par.assign(2*n+2, -1);
            queue<pair<int, int>> q;
            q.push({1e9, src});
            while (!q.empty()) {
                auto [min_on_path, u] = q.front();
                q.pop();
                if (u == snk) {
                    return min_on_path;
                }
                for (const auto &v : adj[u]) {
                    if (cap[u][v] == 0 || par[v] != -1) {
                        continue;
                    }
                    par[v] = u;
                    q.push({min(min_on_path, cap[u][v]), v});
                }
            }
            return 0;
        };
        int tot = 0;
        while (true) {
            int add = find_shortest();
            if (add == 0) {
                break;
            }
            int go = snk;
            while (go != src) {
                int from = par[go];
                cap[from][go] -= add;
                cap[go][from] += add;
                go = from;
            }
            tot += add;
        }
        for (int i = 1; i <= n; i += 1) {
            if (par[2*i+1] == -1 && par[2*i] != -1) {
                curr.push_back(i);
            }
        }
        return tot;
    };
    auto cap_copy = cap;
    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 1);
    for (int from = 1; from <= n; from += 1) {
        for (int to = 1; to <= n; to += 1) if (from != to && !xx[from].count(to)) {
            cap = cap_copy;
            if (min_cut(from*2+1, to*2) != curr.size()) {
                continue;
            }
            if (curr.size() < ans.size()) {
                ans = curr;
            }
        }
    }
    cout << ans.size() << "\n";
    for (const auto &x : ans) {
        cout << x << " ";
    }cout << "\n";
}