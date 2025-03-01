#include <bits/stdc++.h>
using namespace std;
signed main() {
    vector<bitset<1'000>> g(1000);
    int n;
    cin >> n;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            char c;
            cin >> c;
            g[i][j] = c-'0';
        }
    }
    for (int k = 0; k < n; k += 1) {
        for (int u = 0; u < n; u += 1) {
            // for (int v ...)
            if (g[u][k]) {
                // "add" v vertices
                g[u] |= g[k];
            }
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            cout << g[i][j];
        }cout << "\n";
    }
}
