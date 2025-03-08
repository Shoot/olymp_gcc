#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[2][1 << 10][1001];
signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> w(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> w[i];
    }
    vector<int> c(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> c[i];
    }
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i += 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bitset<10'000> seen;
    auto dfs = [&] (auto f, int u) -> void {
        seen[u] = true;
        dp[1][1 << (c[u]-1)][u] = w[u];
        for (const auto &x : adj[u]) {
            if (!seen[x]) {
                f(f, x);
                // Подмаски 3^n - итого O(n*(3^n)) - норм (1000*59049=6e7)
                // Подмаски 4^n - итого O(n*(4^n)) - не норм (1000*1048576=1e9)
                // Всего подмасок всех подмасок = (1 + x)^n = \sum_{k=0}^n \binom{n}{k} x^k = 3^n
                for (int from = (1 << 10) - 1; from >= 0; from -= 1) {
                    int other = ((1 << 10) - 1) ^ from;
                    for (int add = other; add; (add-=1)&=other /*Перебираем подмаски add маски other*/) {
                        for (int add_on = 0; add_on <= 1; add_on += 1) {
                            dp[0][from | add][u] = max(dp[0][from | add][u], dp[add_on][add][x] + dp[0][from][u]);
                        }
                    }
                }
                for (int from = (1 << 10) - 1; from >= 0; from -= 1) {
                    int other = ((1 << 10) - 1) ^ from;
                    for (int add = other; add; (add-=1)&=other /*Перебираем подмаски add маски other*/) {
                        dp[1][from|add][u] = max(dp[1][from|add][u], dp[0][add][x]+dp[1][from][u]);
                    }
                }
            }
        }
    };
    dfs(dfs, 1);
    int maxi = -1;
    for (int on = 0; on <= 1; on += 1) {
        for (int colors_subset = 0; colors_subset < (1 << 10); colors_subset += 1) {
            maxi = max(maxi, dp[on][colors_subset][1]);
        }
    }
    cout << maxi << "\n";
}