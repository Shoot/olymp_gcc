#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
constexpr int MOD = (119<<23)+1;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int TT = 1;
//    cin >> TT;
    mt19937 mt(time(0));
    for (int tt = 0; tt < TT; tt += 1) {
        int n;
        cin >> n;
        vector<pair<int,int>> pts;
        if (n&1) {
            pts.push_back({0, 0});
            pts.push_back({n/2+1, 0});
            pts.push_back({0, n-n/2+1});
        } else if (n&3) {
            pts.push_back({0, 1});
            pts.push_back({1, 0});
            pts.push_back({n/2+2, 0});
            pts.push_back({n/2+1, 1});
        } else {
            pts.push_back({0, 1});
            pts.push_back({1, 0});
            pts.push_back({n/2+1, 0});
            pts.push_back({n/2+1, 1});
            pts.push_back({n/2+1+2, 1-2});
        }
        while (pts.size() < 5) {
            int x, y;
            while (true) {
                x = mt() % (int)1e3;
                y = mt() % (int)1e3;
                bool good = true;
                for (const auto &[ox, oy] : pts) {
                    good &= __gcd(abs(ox-x), abs(oy-y)) == 1;
                }
//                cout << x << " " << y << good << "\n";
                if (good) {
                    break;
                }
            }
            pts.push_back({x, y});
        }
        int cnt = 0;
        for (const auto &[x, y] : pts) {
            for (const auto &[ox, oy] : pts) {
                if (x == ox && y == oy) continue;
                cnt += __gcd(abs(ox-x), abs(oy-y)) - 1;
            }
        }
        cnt /= 2;
//        cout << cnt << "!\n";
        assert(cnt == n);
        for (const auto &[x, y] : pts) {
            cout << x << " " << y << "\n";
        }
    }
}