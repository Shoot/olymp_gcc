#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> bymask(1<<21, (1<<21)-1);
    auto add = [&] (auto f, int u, int x) -> void {
        if (bymask[u] == (bymask[u]&=x)) {
            return;
        }
        // &= можно релаксировать (с импактом) только k раз, ведь биты только зануляются (хотя бы на 1 каждый раз)
        int from = u;
        while (u) {
            f(f, from^(u&-u), x);
            u^=u&-u;
        }
    };
    for (const auto &x : a) {
        add(add, x, x);
    }
    int i = 0;
    while (bymask[i] == i) {
        i += 1;
    }
    cout << i << " ";
    for (int j = 0; j < m; j += 1) {
        int x;
        cin >> x;
        add(add, x, x);
        while (bymask[i] == i) {
            i += 1;
        }
        cout << i << " ";
    }cout << "\n";
}