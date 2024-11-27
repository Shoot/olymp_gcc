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
void solve() {
    int n; cin >> n;
    vector<multiset<int>> sm(n+1);
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            int x; cin >> x;
            if (x != 0) {
                assert(x == 1);
                assert(i != j);
                sm[i].insert(j);
            }
        }
    }
    bitset<1'000'000> seen;
    auto dfs = [&] (auto f, int v) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x);
            }
        }
    };
    dfs(dfs, 1);
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            cout << 0 << endl;
            return;
        }
    }
    vector<int> nech_vs;
    for (int i = 1; i <= n; i += 1) {
        if (sm[i].size()%2) {
            nech_vs.push_back(i);
            clog << i << " is nech" << endl;
        }
    }
    if (nech_vs.size() > 2) {
        cout << 0 << endl;
        return;
    }
    vector<int> ans;
    auto find_euler_path = [&] (auto f, int v) -> void {
        while (!sm[v].empty()) {
            auto it = sm[v].begin();
            int x = *it;
            auto it1 = sm[v].find(x);
            auto it2 = sm[x].find(v);
            assert(it1 != sm[v].end());
            assert(it2 != sm[x].end());
            sm[v].erase(it1);
            sm[x].erase(it2);
            f(f, x);
        }
        ans.push_back(v);
    };
    if (nech_vs.size() == 2) {
        find_euler_path(find_euler_path, min(nech_vs[0], nech_vs[1]));
        reverse(ans.begin(), ans.end());
    } else {
        assert(nech_vs.size() == 0);
        find_euler_path(find_euler_path, 1);
        reverse(ans.begin(), ans.end());
    }
    for (const auto &x : ans) {
        cout << x << ' ';
    }cout << endl;
}

int32_t main() {
    solve();
    return 0;
}
