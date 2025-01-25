#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    vector<int> component;
    vector<pair<bool,bool>> comps;
    component.reserve(1000);
    comps.reserve(1000);
    for (int tt = 0; tt < T; tt += 1) {
        int m;
        cin >> m;
        vector<int> inDegree(1001), outDegree(1001);
        vector<vector<int>> adj(1001);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            outDegree[u]++;
            inDegree[v]++;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int fix1 = 0;
        int fix2 = 0;
        for (int i = 1; i <= 1000; i += 1) {
            if (inDegree[i] > outDegree[i]) {
                fix1 += inDegree[i] - outDegree[i];
            } else if (inDegree[i] < outDegree[i]) {
                fix2 += outDegree[i] - inDegree[i];
            }
        }
        auto dfs = [&] (auto f, int u) -> void {
            if (!inDegree[u] && !outDegree[u]) {
                return;
            }
            component.push_back(u);
            inDegree[u] = 0;
            outDegree[u] = 0;
            for (const auto &v : adj[u]) {
                f(f, v);
            }
        };
        int tot = 0;
        comps.clear();
        int yes_yes = 0;

        for (int i = 1; i <= 1000; i += 1) {
            if (!inDegree[i] && !outDegree[i]) {
                continue;
            }
            component.clear();
            dfs(dfs, i);
            bool need1 = false;
            bool need2 = false;
            for (const auto &x : component) {
                need1 |= inDegree[i] > outDegree[i];
                need2 |= inDegree[i] < outDegree[i];
            }
            comps.push_back({need1,need2});
            yes_yes += need1 && need2;
            tot += 1;
        }

        cout << m + 1 + tot - 1 + (fix1+fix2)/2 - yes_yes - (first+last) / 2 << "\n";
    }
}