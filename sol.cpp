#include <bits/stdc++.h>
using namespace std;
int main() {
    const long long INF = 1e18;
    long long n;
    cin >> n;
    long long m;
    cin >> m;
    vector<long long> price(n+1);
    set<long long> prices;
    for (long long i = 1; i <= n; i += 1) {
        cin >> price[i];
        prices.insert(price[i]);
    }
    vector<vector<pair<int, int>>> adj(n+1);
    set<int> key_levels;
    for (long long i = 0; i < m; i += 1) {
        long long u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        key_levels.insert(w);
    }
    struct State {
        int v;
        int level;
        auto operator<=>(const State & o) const = default;
    };
    map<long long, set<State>> st;
    vector<map<int, long long>> d(n+1);
    vector<map<int, bool>> seen(n+1);
    d[1][1] = 0;
    st[0].insert({1, 1});
    while (!st.empty()) {
        auto [u, level] = *st.begin()->second.begin();
        if (u == n) {
            cout << d[u][level] << endl;
            return 0;
        }
        st.begin()->second.erase(st.begin()->second.begin());
        if (st.begin()->second.empty()) {
            st.erase(st.begin());
        }
        if (seen[u].count(level)) {
            continue;
        }
        seen[u][level] = true;
        for (const auto &[w, v] : adj[u]) {
            if (w <= level) {
                if (!d[v].count(level) || d[v][level] > d[u][level]) {
                    d[v][level] = d[u][level];
                    st[d[v][level]].insert({v, level});
                }
            }
        }
        auto it = key_levels.upper_bound(level);
        while (it != key_levels.end()) {
            int nwl = *it;
            if (!d[u].count(nwl) || d[u][nwl] > d[u][level] + price[u]*(nwl-level)) {
                d[u][nwl] = d[u][level] + price[u]*(nwl-level);
                st[d[u][level] + price[u]*(nwl-level)].insert({u, nwl});
            } else {
                break;
            }
            it++;
        }
    }
    cout << -1 << endl;
    return 0;
}