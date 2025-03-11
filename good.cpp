#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<vector<int>> border(n, vector<int>(m));
    queue<pair<int,int>> q;
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (a[i][j] == 'H') {
                q.push({i, j});
                dist[i][j] = 0;
            }
            if (a[i][j] == '#') {
                continue;
            }
            for (int di = -1; di <= 1; di += 1) {
                for (int dj = -1; dj <= 1; dj += 1) {
                    if (di != 0 || dj != 0) {
//                        if (abs(di)+abs(dj) == 2) {
//                            continue;
//                        }
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            if (a[ni][nj] == '#') {
                                border[i][j] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    vector<vector<int>> border_ugl(n, vector<int>(m));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (a[i][j] == '#') {
                continue;
            }
            for (int di = -1; di <= 1; di += 1) {
                for (int dj = -1; dj <= 1; dj += 1) {
                    if (di != 0 || dj != 0) {
                        if (abs(di)+abs(dj) != 2) {
                            continue;
                        }
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            if (a[ni][nj] == '#') {
                                border_ugl[i][j] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (border[i][j] >= 3) {
//                border[i][j] = 0;
            } else if (border_ugl[i][j] == 2) {
//                border[i][j] = 9;
            }
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cout << border[i][j];
        }cout << "\n";
    }
//    int mini = 1e9;
//    for (int di = -1; di <= 1; di += 1) {
//        for (int dj = -1; dj <= 1; dj += 1) {
//            if (di != 0 || dj != 0) {
//                int ni = hi + di;
//                int nj = hj + dj;
//                mini = min(mini, dist[ni][nj]);
//            }
//        }
//    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cout << border[i][j];
        }cout << "\n";
    }
}