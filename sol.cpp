#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n=500, m;
    vector<int> q;
    q.reserve(1e7);
    vector<int> done(n+1, -1e9);
    vector<int> doneflag(n+1, -1e9);
    vector<int> d(n+1, -1e9);
    vector<int> dflag(n+1, -1e9);
    vector<int> curr(n+1, -1e9);
    vector<vector<pair<int,int>>> adj(n+1);
    for (auto &x : adj) {
        x.reserve(500);
    }
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i += 1) {
            adj[i].clear();
        }
        for (int i = 0; i < m; i += 1) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({w, v});
        }
        int cnt = 0;
        auto can = [&] (int x) -> bool {
            cnt += 1;
            int end = 0;
            for (int i = 1; i <= n; i += 1) {
                q[end++] = i;
            }
            int it = 0;
            while (it < end) {
                auto tp = q[it];
                curr[tp] = -1e9;
                it += 1;
                for (const auto &[w, v] : adj[tp]) {
                    if (dflag[v] != cnt) {
                        dflag[v] = cnt;
                        d[v] = 0;
                    }
                    if (d[v] > d[tp] + w - x) {
                        d[v] = d[tp] + w - x;
                        if (curr[v] != cnt) {
                            curr[v] = cnt;
                            q[end++] = v;
                            if (doneflag[v] != cnt) {
                                doneflag[v] = cnt;
                                done[v] = 0;
                            }
                            done[v] += 1;
                            if (done[v] > n) {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        };
        if (!can(1)) {
            cout << "No Solution\n";
            continue;
        }
        if (can(10001)) {
            cout << "Infinite\n";
            continue;
        }
        int l = 1, r = 10000;
        int good = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (can(mid)) {
                good = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << r << "\n";
    }
}