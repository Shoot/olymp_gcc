#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <random>
#include <chrono>
#include <bitset>
#include <assert.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distrib(1, 10);
void solve() {
    int n; cin >> n;
    vector<vector<int>> d(n, vector<int>(n));
    int maxi = 0;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            cin >> d[i][j];
            maxi = max(maxi, d[i][j]);
        }
    }
    int l = 0, r = maxi;
    int good = -1;
    auto can = [&] (int x) -> bool {
        vector<vector<int>> sm(n);
        vector<vector<int>> sm_rev(n);
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                if (d[i][j] <= x) sm[i].push_back(j), sm_rev[j].push_back(i);
            }
        }
        vector<bool> seen(n, false);
        auto dfs = [&] (auto f, int v) -> void {
            seen[v] = true;
            for (const auto &x : sm[v]) {
                if (!seen[x]) {
                    seen[x] = true;
                    f(f, x);
                }
            }
        };
        dfs(dfs, 0);
        for (int i = 0; i < n; i += 1) {
            if (!seen[i]) return false;
        }
        fill(seen.begin(), seen.end(), false);
        auto dfs_rev = [&] (auto f, int v) -> void {
            seen[v] = true;
            for (const auto &x : sm_rev[v]) {
                if (!seen[x]) {
                    seen[x] = true;
                    f(f, x);
                }
            }
        };
        dfs_rev(dfs_rev, 0);
        for (int i = 0; i < n; i += 1) {
            if (!seen[i]) return false;
        }
        return true;
    };
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (can(mid)) {
            r = mid - 1;
            good = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << good << endl;
}

int32_t main() {
    solve();
    return 0;
}
