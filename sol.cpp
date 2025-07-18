//#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
//using namespace __gnu_pbds;
//template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//#define int long long
//#define double long double
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
//constexpr int INF = 1e18;
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
//    for (int tt = 0; tt < T; tt += 1) {
//    }
    // 3D Mo представляем так: фиксируем квадрат и поднимаемся вверх до конца, таким образом покрываем все 3D пространство
    // 3D Mo оцениваем так:
    // (внутри квадрата всего)    (поднимаемся всего)
    // 3e5*sz*2                   1e5*(1e5/sz)^2
    // Q*(размер квадрата)*2      N*(кол-во квадратов)

    // Online 2D Mo: запускаемся от состояния в квадрате, обновляем для всех квадратов
    // Online 2D Mo оцениваем так
    // (внутри квадрата)      (обновление всех квадратов)
    // Q*(размер квадрата)*2  Q*(кол-во квадратов)
    // 3e5 * sz * 2       +   3e5 * ((1e5 / sz)^2)

    // НАЙДЕМ КОНСТАНТУ
    // 6e5 * sz           +   3e15 / (sz^2) -> min
    // f' = 6e5 + 3e15 / (-2 * sz^3) = 0
    // 6e5 = 3e15 / (2 * sz^3)
    // (2 * sz^3) * 6e5 = 3e15
    // (2 * sz^3) = 3e15/6e5
    //      sz^3 = 3e15/3e5
    //      sz^3 = 1e10
    //      sz = 1e10**(1/3)=2154

    constexpr int sz = 2154;
    int n;
    cin >> n;
    struct State {
        int l = 0;
        int r = -1;
        long long su = 0;
        vector<int> cnt;
        State() {
            cnt.resize(1e5+1);
        }
    };
    vector<vector<State>> mo((n+sz-1)/sz, vector<State>((n+sz-1)/sz));
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    int q;
    cin >> q;
    long long last = 0;
    for (int ii = 0; ii < q; ii += 1) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int pos, val;
            cin >> pos >> val;
            pos += last, val += last;
            if (pos >= n) {
                pos -= n;
            }
            if (val >= n) {
                val -= n;
            }val += 1;
            for (auto &x : mo) {
                for (auto &y : x) {
                    if (y.l <= pos && y.r >= pos) {
                        y.su -= y.cnt[a[pos]]-1;
                        y.cnt[a[pos]] -= 1;

                        y.cnt[val] += 1;
                        y.su += y.cnt[val]-1;
                    }
                }
            }
            a[pos] = val;
        } else {
            int l, r;
            cin >> l >> r;
            l += last, r += last;
            if (l >= n) {
                l -= n;
            }
            if (r >= n) {
                r -= n;
            }
            if (r < l) {
                swap(l, r);
            }
            auto& go = mo[l/sz][r/sz];
            if (go.r < go.l) {
                go.l = l, go.r = l-1;
            }
            while (go.l > l) {
                go.cnt[a[go.l-1]] += 1;
                go.su += go.cnt[a[go.l-1]]-1;
                go.l -= 1;
            }
            while (go.r < r) {
                go.cnt[a[go.r+1]] += 1;
                go.su += go.cnt[a[go.r+1]]-1;
                go.r += 1;
            }
            while (go.l < l) {
                go.su -= go.cnt[a[go.l]]-1;
                go.cnt[a[go.l]] -= 1;
                go.l += 1;
            }
            while (go.r > r) {
                go.su -= go.cnt[a[go.r]]-1;
                go.cnt[a[go.r]] -= 1;
                go.r -= 1;
            }
            last = (long long)(r-l+1)*(r-l)/2-go.su;
            cout << last << " ";
            last %= n;
        }
    }cout << "\n";
}