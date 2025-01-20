#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    while (cin >> n) {
        struct Corner {
            int x;
            int y;
            bool up_left;
            int idx;
            bool operator<(const Corner& other) const {
                return tie(x, y) < tie(other.x, other.y);
            }
        };
        vector<Corner> corners;
        for (int i = 1; i <= n; i += 1) {
            int x, y;
            cin >> x >> y;
            corners.push_back({x, y, true, i});
        }
        for (int i = 1; i <= n; i += 1) {
            int x, y;
            cin >> x >> y;
            corners.push_back({x, y, false, i});
        }
        sort(corners.begin(), corners.end());
    }
}
