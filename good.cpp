#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int,int>>> adj(n+1);
        for (int i = 0; i < m; i += 1) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({w, v});
        }
        auto can = [&] (int x) -> bool {
            vector<int> d(n+1);
            vector<bool> curr(n+1);
            vector<int> done(n+1);
            queue<int> q;
            for (int i = 1; i <= n; i += 1) {
                q.push(i);
            }
            while (!q.empty()) {
                auto tp = q.front();
                q.pop();
                for (const auto &[w, v] : adj[tp]) {
                    if (d[v] > d[tp] + w - x) {
                        d[v] = d[tp] + w - x;
                        if (!curr[v]) {
                            curr[v] = true;
                            q.push(v);
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
        int l = -1e11, r = 1e11;
        int good = -1e18;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (can(mid)) {
                good = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (good < 0) {
            cout << "No Solution\n";
            continue;
        }
        if (good == 1e11) {
            cout << "Infinite\n";
            continue;
        }
        cout << good << "\n";
    }
}