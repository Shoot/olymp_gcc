#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> dist(a[0], 1e18);
    dist[1] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({-0, 1});
    bitset<100'000> seen;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (seen[u]) {
            continue;
        }
        seen[u] = true;
        for (int i = 1; i < n; i += 1) {
            int nw = (u + a[i]) % a[0];
            if (dist[nw] > dist[u] + a[i]) {
                dist[nw] = dist[u] + a[i];
                pq.push({-dist[nw], nw});
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < a[0]; i += 1) {
        ans ^= dist[i];
    }
    cout << ans << "\n";
}