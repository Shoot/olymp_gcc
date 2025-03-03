#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2", "popcnt")
signed main() {
    vector<vector<bitset<255>>> a(255, vector<bitset<255>>(255));
    int n;
    cin >> n;
    vector<pair<int,int>> pts(n);
    for (auto &[x, y] : pts) {
        cin >> x >> y;
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            int dx_ray = pts[j].first - pts[i].first;
            int dy_ray = pts[j].second - pts[i].second;
            for (int k = 0; k < n; k += 1) {
                int x = pts[k].first;
                int y = pts[k].second;
                int our_dx = x - pts[i].first;
                int our_dy = y - pts[i].second;
                int cross = dx_ray * our_dy - dy_ray * our_dx;
                if (cross > 0) {
                    a[i][j][k] = true;
                }
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i += 1) {
        for (int j = i+1; j < n; j += 1) {
            for (int k = j+1; k < n; k += 1) {
                if (!a[i][j][k]) {
                    cnt += (a[i][k] & a[k][j] & a[j][i]).none();
                } else {
                    cnt += (a[i][j] & a[j][k] & a[k][i]).none();
                }
            }
        }
    }
    cout << cnt << "\n";
}
