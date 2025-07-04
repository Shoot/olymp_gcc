//#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
//using namespace __gnu_pbds;
//template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int unsigned long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define ALICE(x) cout << (x?"Alice\n":"Bob\n")
#define BOB(x) cout << (x?"Bob\n":"Alice\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
//constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
constexpr int INF = 1e18;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LO
    cout << unitbuf;
#endif
//    int T;
//    cin >> T;
    for (int ii = 0; ; ii += 1) {
        string tp=(ii&1?"decode":"encode");
//        cin >> tp;
        auto swap = [&] (int x) -> int {
            return ULLONG_MAX^x;
        };
        if (tp == "encode") {
            ifstream cin("input.txt");
            ofstream cout("my.ans");
            int n;
            cin >> n;
            vector<int> a(n);
            for (auto &x : a) {
                cin >> x;
            }
            vector<int> b(16);
            for (int i = 0; i < n; i += 1) {
                if (max(a[i], swap(a[i])) == a[i]) {
                    b[i/64] |= 1ull << i%64;
                }
            }
            int y=0;
            for (int i = 0; i < 16; i += 1) {
                if (max(b[i], swap(b[i]))==b[i]) {
                    y |= 1ull << i;
                }
            }
            a.push_back(y);
            for (const auto &x : b) {
                a.push_back(x);
            }
            a.push_back(n);
            cout << a.size() << "\n";
            mt19937 mt(time(0));
            uniform_int_distribution<int> go(0, 1);
            for (auto &x : a) {
                if (go(mt)) {
                    x = swap(x);
                }
                cout << x << " ";
            }cout << "\n";
        }
        if (tp == "decode") {
            ifstream cin("my.ans");
            int n;
            cin >> n;
            vector<int> a(n);
            for (auto &x : a) {
                cin >> x;
            }
            n = a.back();
            n = min(n, swap(n));
            a.pop_back();
            vector<int> b;
            for (int i = 0; i < 16; i += 1) {
                b.push_back(a.back());
                a.pop_back();
            }
            map<int,signed> cnt;
            int best = min(a[n], swap(a[n]));
            for (int i = 0; i < 16; i += 1) { // 1 - maxi, 0 - mini
                if (best&(1<<i)) {
                    b[i] = max(b[i], swap(b[i]));
                } else {
                    b[i] = min(b[i], swap(b[i]));
                }
            }
            for (int i = 0; i < n; i += 1) {
                if (b[i/64]&(1ull<<(i%64))) {
                    cout << max(a[i], swap(a[i])) << " ";
                } else {
                    cout << min(a[i], swap(a[i])) << " ";
                }
            }cout << "\n";
        }
    }
}