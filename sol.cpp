#include <bits/stdc++.h>
using namespace std;
signed main() {
    int T;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, m, choose, inc;
        cin >> n >> m >> choose >> inc;
        vector<int> vals(n);
        for (int i = 0; i < n; i += 1) {
            cin >> vals[i];
        }
        vector<pair<int, int>> segs(m);
        vector<vector<pair<int, int>>> starts(n);
        for (auto &[l, r] : segs) {
            cin >> l >> r;
            l -= 1;
            r -= 1;
            starts[l].push_back({l, r});
        }
        auto can = [&] (int X) -> bool {
            int available = choose;
            vector<int> diff(n);
            diff[0] = vals[0];
            for (int i = 1; i < n; i += 1) {
                diff[i] = vals[i] - vals[i - 1];
            }
            int prev = 0;
            priority_queue<pair<int,int>> pq;
            for (int i = 0; i < n; i += 1) {
                for (const auto &[l, r] : starts[i]) {
                    pq.push({r,l});
                }
                int curr = prev + diff[i];
                int cnt = (X - curr + inc - 1) / inc;
                if (cnt <= 0) {
                    prev = curr;
                    continue;
                }
                available -= cnt;
                if (available < 0) {
                    return false;
                }
                for (int j = 0; j < cnt; j += 1) {
                    if (pq.empty()) {
                        return false;
                    }
                    auto [r, l] = pq.top();
                    pq.pop();
                    if (r < i) {
                        return false;
                    }
                    curr += inc;
                    if (r+1 < n) {
                        diff[r+1] -= inc;
                    }
                }
                prev = curr;
            }
            return true;
        };
        int l = 1, r = 1e9;
        int good = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (can(mid)) {
                good = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << good << "\n";
    }
}