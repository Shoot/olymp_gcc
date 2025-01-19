#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi")
vector<vector<bool>> Good(600, vector<bool>(600));
vector<vector<pair<int, int>>> match(600, vector<pair<int, int>>(600, {-1, -1}));
bool seen[600][600];
int di[4] = {0, 0, -1, 1};
int dj[4] = {1, -1, 0, 0};
int n;
bool try_kuhn(int i, int j) {
    if (seen[i][j]) return false;
    seen[i][j] = true;
    for (int k = 0; k < 4; k += 1) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (ni < 0 || ni >= n || nj < 0 || nj >= n || !Good[ni][nj]) {
            continue;
        }
        if (match[ni][nj] == make_pair(-1, -1) || try_kuhn(match[ni][nj].first, match[ni][nj].second)) {
            match[ni][nj] = {i, j};
            return true;
        }
    }
    return false;
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tt = 1; tt <= T; tt += 1) {
        cin >> n;
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                match[i][j] = {-1, -1};
                char x;
                cin >> x;
                if (x == '#') {
                    Good[i][j] = true;
                } else {
                    Good[i][j] = false;
                }
            }
        }
        int matching = 0;
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                if ((i + j) % 2 != 0 || !Good[i][j]) continue;
                memset(seen, 0, sizeof(seen));
                if (try_kuhn(i, j)) {
                    matching += 1;
                }
            }
        }
        cout << "Case " << tt << ": " << matching << "\n";
    }
}
