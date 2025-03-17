#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
mt19937 mt(time(0));
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1e9, m = 1e9;
    cin >> n >> m;
    int k = 7000;
    cin >> k;
    vector<pair<int,int>> pts(k);
    for (auto &[x, y] : pts) {
        cin >> x >> y;
//        x = mt();
//        y = mt();
    }
    int maxi = 1;
    sort(pts.begin(), pts.end());
    vector<bitset<7000>> ok(7000);
    for (auto &x : ok) {
        x.set();
    }
//    int OPS = 0;
    for (int i = 0; i < k; i += 1) {
        for (int j = ok[i]._Find_next(i); j < k; j = ok[i]._Find_next(j)) {
            ok[i][j] = false;
            int dx = pts[j].first - pts[i].first;
            int dy = pts[j].second - pts[i].second;
            int cnt = 2;
            int last = j;
            for (int f = ok[j]._Find_next(j); f < k; f = ok[last]._Find_next(f)) {
                if ((pts[f].first - pts[last].first) < dx || (pts[f].first - pts[last].first) == dx && (pts[f].second - pts[last].second) < dy) {
                    f = lower_bound(pts.begin()+f+1, pts.end(), pair<int,int>{pts[last].first+dx, pts[last].second+dy}) - pts.begin();
                    if (!ok[last][f]) {
                        f = ok[last]._Find_next(f);
                    }
                }
                if (f >= k || (pts[f].first - pts[last].first) > dx || (pts[f].first - pts[last].first) == dx && (pts[f].second - pts[last].second) > dy) {
                    break;
                }
//                OPS += 1;
                ok[last][f] = false;
                if ((pts[f].first - pts[last].first) == dx && (pts[f].second - pts[last].second) == dy) {
                    cnt += 1;
                    last = f;
                }
            }
            maxi = max(maxi, cnt);
        }
    }
    cout << maxi << "\n";
//    clog << OPS << "\n";
}