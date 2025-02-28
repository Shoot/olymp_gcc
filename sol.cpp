#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> row(n);
    vector<int> col(m);
    for (auto &x : row) {
        cin >> x;
    }
    for (auto &x : col) {
        cin >> x;
    }
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &x : a) {
        for (auto &y : x) {
            cin >> y;
        }
    }
    vector<vector<int>> cap(n+m+2, vector<int>(n+m+2));
    int src = n + m;
    int snk = n + m + 1;
    for (int i = 0; i < n; i += 1) {
        cap[src][i] = row[i];
    }
    for (int i = 0; i < m; i += 1) {
        cap[i+n][snk] = col[i];
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (a[i][j] != -1) {
                cap[src][i] -= a[i][j];
                cap[j+n][snk] -= a[i][j];
            } else {
                cap[i][j+n] = 1e18;
            }
        }
    }
    vector<int> par;
    auto min_cut = [&] () -> int {
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
    auto prev = cap;
    int N = n;
    n = n + m + 2;
    min_cut();
    for (int i = 0; i < N; i += 1) {
        for (int j = 0; j < m; j += 1) if (a[i][j] == -1) {
                a[i][j] = prev[i][j+N] - cap[i][j+N];
                if (a[i][j] < 0) {
                    cout << -1 << "\n";
                    return 0;
                }
            }
    }
    for (const auto &x : a) {
        for (const auto &y : x) {
            cout << y << " ";
        }cout << "\n";
    }
}