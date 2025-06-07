#include <bits/stdc++.h>
using namespace std;
#define int long long
#define YES(x) cout << (x?"YES":"NO")
#define NO(x) cout << (x?"NO":"YES")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
    cin >> T;
    // +3 - 1 = 2
    // +2 - 2 = 0
    // +1 - 3 = -2
    // +0 - 4 = -4
//    map<pair<int,int>,set<pair<int,int>>> vals;
//    vals[{4,1}] = {{0, 0}};
//    queue<pair<int,int>> q;
//    q.push({4, 1});
    int di[4] = {0, 0, 1, -1};
    int dj[4] = {1, -1, 0, 0};
//    while (!q.empty()) {
//        auto [p, s] = q.front();
//        cout << p << " " << s << "\n";
//        q.pop();
//        for (const auto &[x, y] : vals[{p, s}]) {
//            for (int k = 0; k < 4; k += 1) {
//                int nx = x + di[k];
//                int ny = y + dj[k];
//                if (!vals[{p, s}].count({nx, ny})) {
//                    int adj = 0;
//                    adj += vals[{p, s}].count({nx+1, ny});
//                    adj += vals[{p, s}].count({nx-1, ny});
//                    adj += vals[{p, s}].count({nx, ny+1});
//                    adj += vals[{p, s}].count({nx, ny-1});
//                    int p_inc = 4 - adj;
//                    p_inc -= 4 - p_inc;
//                    int s_inc = 1;
//                    assert(p_inc == -2 || p_inc == 0 || p_inc == 2 || p_inc == -4);
//                    int nws = s+s_inc;
//                    int nwp = p+p_inc;
//                    if (s == 3 && p == 8) {
//                        cout << nx << " " << ny << "\n";
//                        cout << nwp << nws << adj << "LDDD\n";
//                    }
//                    if (!vals.count({nwp, nws})) {
//                        vals[{nwp, nws}] = vals[{p, s}];
//                        vals[{nwp, nws}].insert({nx, ny});
//                        if (vals[{nwp, nws}].size() < 50000 && nwp <= 100 && nws <= 100) {
//                            q.push({nwp, nws});
//                        }
//                    }
//                }
//            }
//        }
//    }
//    for (const auto &[x, y] : vals[{8, 3}]) {
//        cout << x << "$" << y << "\n";
//    }
    for (int tt = 0; tt < T; tt += 1) {
        // p_contrib = 4-adj
//        0 <= p_contrib <= 3
        // s_contrib = 1
        int p, s;
        cin >> p >> s;
        if (p == 4*s) {
            cout << 1 << "\n";
            cout << 1 << " " << 1 << "\n";
            continue;
        }
        if (p > 3*s) {
            cout << -1 << "\n";
            continue;
        }
        int P = 4, S = 1;
        double need = double(p) / s;
        set<pair<int,int>> vals = {{0, 0}};
        while (true) {
            if (vals.size() > 1000) {
                vals.clear();
                break;
            }
            int g = __gcd(P, S);
            if (P/g == p && S/g == s) {
                break;
            }
            double have = double(P) / S;
            bool need_more = have < need;
            pair<int,int> best = {-1, -1};
            int best_val = need_more ? -1e18 : 1e18;
            int best_adj = need_more ? 1e18 : -1e18;
            for (const auto &[x, y] : vals) {
                for (int k = 0; k < 4; k += 1) {
                    int nx = x + di[k];
                    int ny = y + dj[k];
                    if (!vals.count({nx, ny})) {
                        int adj = 0;
                        adj += vals.count({nx+1, ny});
                        adj += vals.count({nx-1, ny});
                        adj += vals.count({nx, ny+1});
                        adj += vals.count({nx, ny-1});
                        int p_inc = 4 - adj;
                        p_inc -= 4 - p_inc;
                        int s_inc = 1;
                        assert(p_inc == -2 || p_inc == 0 || p_inc == 2 || p_inc == -4);
                        int nws = s+s_inc;
                        int nwp = p+p_inc;
                        adj += vals.count({nx+1, ny+1});
                        adj += vals.count({nx+1, ny-1});
                        adj += vals.count({nx-1, ny+1});
                        adj += vals.count({nx-1, ny-1});
                        if ((need_more && (p_inc > best_val || (p_inc == best_val && adj < best_adj))) || (!need_more && (p_inc < best_val || (p_inc == best_val && adj > best_adj)))) {
                            best_val = p_inc;
                            best = {nx, ny};
                            best_adj = adj;
                        }
                    }
                }
            }
            vals.insert(best);
            S += 1;
            P += best_val;
        }
        if (!vals.size()) {
            cout << -1 << "\n";
            continue;
        }
        cout << vals.size() << "\n";
        for (const auto &[x, y] : vals) {
            cout << x << " " << y << "\n";
        }
//        cout << "IDK\n";
    }
}