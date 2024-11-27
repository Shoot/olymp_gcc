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
    vector<multiset<int>> sm(n+1);
    for (int i = 1; i <= n; i += 1) {
        int kol; cin >> kol;
        for (int j = 0; j < kol; j += 1) {
            int v, nvm; cin >> v >> nvm;
            if (i < v) {
                sm[i].insert(v);
                sm[v].insert(i);
            }
        }
    }
    int nech = 0;
    int nech_v = 1;
    for (int i = 1; i <= n; i += 1) {
        if (sm[i].size()%2) {
            nech_v = i;
            nech += 1;
        }
    }
    if (nech > 2) {
        cout << -1 << endl;
        return;
    }
    vector<int> ans;
    auto find_path = [&] (auto f, int v) -> void {
        while (!sm[v].empty()) {
            auto it = sm[v].begin();
            int x = *it;
            sm[v].erase(sm[v].find(x));
            sm[x].erase(sm[x].find(v));
            f(f, x);
        }
        ans.push_back(v);
    };

    find_path(find_path, nech_v);
    cout << ans.size()-1 << endl;
    for (const auto &x : ans) {
        cout << x << ' ';
    }
    cout << endl;
}

int32_t main() {
    solve();
    return 0;
}
