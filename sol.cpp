#include <bits/stdc++.h>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2", "popcnt")
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<bitset<4'000>> g(4000);
    vector<bitset<4'000>> ans(4000);
    int n;
    cin >> n;
    char c;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            cin >> c;
            g[i][j] = c-'0';
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (g[i][j]) {
                ans[i] ^= g[j];
            }
        }
    }
    int cnt = 0;
    for (const auto &x : ans) {
        cnt += x.count();
    }
    cout << cnt << "\n";
}
