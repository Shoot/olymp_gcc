#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <random>
#include <chrono>
#include <bitset>
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> sm(n+1);
    vector<vector<int>> sm_rev(n+1);
    int one = 0;
    for (int i = 1; i <= n; i += 1) {
        int depend; cin >> depend;
        if (depend == i) one += 1;
        sm[i].push_back(depend);
        sm_rev[depend].push_back(i);
    }
    bitset<1'000'000> seen;
    vector<int> topo;
    auto dfs = [&] (auto f, int v) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x);
            }
        }
        topo.push_back(v);
    };
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            dfs(dfs, i);
        }
    }
    reverse(topo.begin(), topo.end());
//    for (const auto &x : topo) {
//        cout << x << '!';
//    }cout << endl;
    vector<int> comp(n+1);
    int COMP = 0;
    int SZ = 0;
    auto dfs_rev = [&] (auto f, int v) -> void {
        comp[v] = COMP;
        SZ += 1;
        for (const auto &x : sm_rev[v]) {
            if (!comp[x]) {
                f(f, x);
            }
        }
    };
    int tot = 0;
    for (int i = 0; i < n; i += 1) {
        if (!comp[topo[i]]) {
            COMP += 1;
            SZ = 0;
            dfs_rev(dfs_rev, topo[i]);
            if (SZ != 1) {
                tot += 1;
            }
        }
    }
    cout << tot+one << endl;
}

int32_t main() {
    solve();
    return 0;
}
