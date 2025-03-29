#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    // Запросы
    //0  is_sorted(a.begin()+l, a.begin()+r+1)
    //1  sort(a.begin()+l, a.begin()+r+1)
    //2  return a[i]
    //3  a[i] = x
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    struct Q {
        int tp;
        int l;
        int r;
        int i;
        int x;
    };
    vector<Q> qs;
    for (int ii = 0; ii < q; ii += 1) {
        int l, r;
        cin >> l >> r;
        l -= 1;
        r -= 1;
        qs.push_back({0, l, r});
        qs.push_back({1, l, r});
    }
    auto gosimple = [&] () -> void {
        auto b = a;
        for (const auto &[tp, l, r, nvm1, nvm2] : qs) {
            if (tp == 0) {
                cout << (is_sorted(b.begin()+l, b.begin()+r+1)?"YES":"NO") << "\n";
            }
            if (tp == 1) {
                sort(b.begin()+l, b.begin()+r+1);
            }
        }
    };
    auto gofast = [&] () -> void {
        auto b = a;
        vector<vector<int>> vv;
        set<int> starts;
        vv.push_back({b[0]});
        starts.insert(0);
        for (int i = 1; i < n; i += 1) {
            if (b[i-1] <= b[i]) {
                vv.back().push_back(b[i]);
            } else {
                starts.insert(i);
                vv.push_back({b[i]});
            }
        }
        for (const auto &[tp, l, r, nvm1, nvm2] : qs) {
            if (tp == 0) {
                if (*(--starts.upper_bound(r)) <= l) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            }
            if (tp == 1) {

            }
        }
    };
    gosimple();
    cout << "----\n";
    gofast();
}