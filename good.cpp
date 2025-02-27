#include <bits/stdc++.h>
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> row(n);
    vector<int> col(m);
    for (auto &x : row) {
        cin >> x;
    }
    for (auto &x : col) {
        cin >> x;
    }
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &x : a) {
        for (auto &y : x) {
            cin >> y;
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (a[i][j] != -1) {

            }
        }
    }
}