#include <bits/stdc++.h>
using namespace std;
signed main() {
    int T;
    cin >> T;
    const int di[4] = {1, -1, 0, 0};
    const int dj[4] = {0, 0, 1, -1};
    for (int tt = 1; tt <= T; tt += 1) {
        int N;
        cin >> N;
        vector<string> a(N);
        for (int i = 0; i < N; i += 1) {
            cin >> a[i];
        }
        vector<vector<int>> adj(N*N);
        for (int i = 0; i < N; i += 1) {
            for (int j = 0; j < N; j += 1) if ((i+j)%2==1) {
                for (int k = 0; k < 4; k += 1) {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < N) {
                        if (a[i][j] == '#' && a[ni][nj] == '#') {
                            adj[i+j*N].push_back(ni+nj*N);
                        }
                    }
                }
            }
        }
        bitset<600> vis;
        vector<int> match(600, -1);
        auto matching = [&] (auto f, int u) -> bool {
            for (const auto &x : adj[u]) {
                if (!vis[x]) {
                    vis[x] = true;
                    if (match[x] == -1 || f(f, match[x])) {
                        match[x] = u;
                        return true;
                    }
                }
            }
            return false;
        };
        int sz = 0;
        for (int i = 0; i < N*N; i += 1) {
            vis.reset();
            if (matching(matching, i)) {
                sz += 1;
            }
        }
        cout << "Case " << tt << ": " << sz << "\n";
    }
}