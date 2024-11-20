#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <random>
#include <chrono>
#include <sstream>
#include <bitset>
using namespace std;
void solve() {
    long long n; cin >> n;
    vector<vector<long long>> sm(n+1);
    for (long long i = 0; i < n-1; i += 1) {
        long long u, v; cin >> u >> v;
        sm[u].push_back(v);
        sm[v].push_back(u);
    }
    bitset<1'000'000> seen;
    vector<long long> dist(n+1);
    auto dfs = [&] (auto f, long long v, long long d) -> void {
        seen[v] = true;
        dist[v] = d;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                f(f, x, d+1);
            }
        }
    };
    dfs(dfs, 1, 0);
    long long maxi = max_element(dist.begin(), dist.end())-dist.begin();
    seen.reset();
    dfs(dfs, maxi, 0);
    cout << *max_element(dist.begin(), dist.end())+1 << endl;
}

int32_t main() {
    long long tt = 1;
//    cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}