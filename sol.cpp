#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cap(n+m+2, vector<int>(n+m+2));
    int src = n+m;
    int snk = n+m+1;
    for (int i = 0; i < m; i += 1) {
        cap[src][n+i] = 1;
    }
    for (int i = 0; i < n; i += 1) {
        cap[i][snk] = 1;
    }
    for (int i = 0; i < n; i += 1) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j += 1) {
            int x;
            cin >> x;
            x -= 1;
            cap[n+x][i] = 1e18;
        }
    }
    n = n + m + 2;
    auto min_cut = [&] () -> int {
        vector<int> par;
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                if (cap[i][j] != 0) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        auto find_shortest = [&] () -> int {
            par.assign(n, -1);
            queue<pair<int, int>> q;
            q.push({1e18, src});
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
        return tot;
    };
    cout << min_cut() << "\n";
}