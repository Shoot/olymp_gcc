#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<pair<int,int>> pts;
    int hi = -1, hj = -1;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (a[i][j] == '#') {
                pts.push_back({i,j});
            }
            if (a[i][j] == 'H') {
                assert(hi == -1 && hj == -1);
                hi = i;
                hj = j;
            }
        }
    }
    assert(hi != -1 && hj != -1);
    sort(pts.begin(), pts.end());
    auto [ii, jj] = pts.front();
    int dii = -1;
    if (jj == hj && ii > hi) {
        reverse(pts.begin(), pts.end());
        dii = 1;
    }
    vector<vector<bool>> ok(n, vector<bool>(m, true));
    auto [cuti, cutj] = pts.front();
    for (int i = cuti; i >= 0 && i < n; i += dii) {
        ok[i][cutj] = false;
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (a[i][j] == '#') {
                ok[i][j] = false;
            }
        }
    }
    queue<pair<int,int>> q;
    q.push({hi,hj});
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[hi][hj] = 0;
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (int di = -1; di <= 1; di += 1) {
            for (int dj = -1; dj <= 1; dj += 1) {
                int ni = i + di;
                int nj = j + dj;
                if (ni < 0 || ni >= n || nj < 0 || nj >= m || !ok[ni][nj]) {
                    continue;
                }
                if (dist[ni][nj] > dist[i][j] + 1) {
                    dist[ni][nj] = dist[i][j] + 1;
                    q.push({ni, nj});
                }
            }
        }
    }
    int mini = 1e9;
//    for (int i = 0; i < n; i += 1) {
//        for (int j = 0; j < m; j += 1) {
//            if (dist[i][j]==1e9) {
//                cout << "x";
//                continue;
//            }
//            cout << dist[i][j]%10;
//        }cout << "\n";
//    }
    for (int i = cuti+dii; i >= 0 && i < n; i += dii) {
        for (int di_left = -1; di_left <= 1; di_left += 1) {
            for (int di_right = -1; di_right <= 1; di_right += 1) {
                if (i+di_left < 0 || i+di_left >= n || i+di_right < 0 || i+di_right >= n) {
                    continue;
                }
                mini = min(mini, dist[i+di_left][cutj-1]+dist[i+di_right][cutj+1]+2);
            }
        }
    }
    cout << mini << "\n";
}