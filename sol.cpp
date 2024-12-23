#include <bits/stdc++.h>
using namespace std;
int main() {
    const long long INF = 1e18;
    long long n;
    cin >> n;
    long long m;
    cin >> m;
    vector<long long> price(n+1);
    for (long long i = 1; i <= n; i += 1) {
        cin >> price[i];
    }
    vector<vector<pair<long long, long long>>> adj(n+1);
    for (long long i = 0; i < m; i += 1) {
        long long u, v, l;
        cin >> u >> v >> l;
        adj[u].push_back({l, v});
        adj[v].push_back({l, u});
    }
    set<pair<long long, long long>> st;
    vector<long long> min_level(n+1, INF);
    min_level[1] = 1;
    st.insert({1, 1});
    bitset<1'000'000> seen;
    long long price_at_best_gym = INF;
    long long tot = 0;
    long long curr_level = 1;
    while (!st.empty()) {
        long long v = st.begin()->second;
        tot += price_at_best_gym*(min_level[v]-curr_level);
        if (v == n) {
            cout << tot << endl;
            return 0;
        }
        curr_level = min_level[v];
        price_at_best_gym = min(price_at_best_gym, price[v]);
        st.erase(st.begin());
        if (seen[v]) {
            continue;
        }
        seen[v] = true;
        for (const auto &[l, x] : adj[v]) {
            if (min_level[x] > max(min_level[v], l)) {
                min_level[x] = max(min_level[v], l);
                st.insert({max(min_level[v], l), x});
            }
        }
    }
    cout << -1 << endl;
    return 0;
}