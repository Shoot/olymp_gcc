#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,avx2")
vector<vector<bool>> dir;
vector<vector<bool>> complex_path;
vector<vector<int>> all;
void godo(int i, int j) {
    for (int b4j = i; b4j < j; b4j += 1) {
        complex_path[i][j] = complex_path[i][j] ^ (all[i][b4j]&dir[b4j][j]);
    }
}
signed main() {
    int n;
    cin >> n;
    all.assign(n, vector<int>(n));
    dir.assign(n, vector<bool>(n));
    complex_path.assign(n, vector<bool>(n));
    for (int i = 0; i < n; i += 1) {
        for (int j = i + 1; j < n; j += 1) {
            char c;
            cin >> c;
            all[i][j] = c == '1';
        }
    }
    int su = 0;
    for (int i = n-1; i >= 0; i -= 1) {
        for (int j = i + 1; j < n; j += 1) {
            godo(i, j);
            dir[i][j] = all[i][j] ^ complex_path[i][j];
            su += dir[i][j];
        }
    }
    cout << su << "\n";
}
