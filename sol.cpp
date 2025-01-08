#include <bits/stdc++.h>
using namespace std;

int main() {
    while (true) {
        int m, n, A, B;
        cin >> m >> n >> A >> B;
        if (m == 0 && n == 0 && A == 0 && B == 0) {
            return 0;
        }
        int a = A, b = B, C = ~(1<<31), M = (1<<16)-1;
        auto gen = [&] () -> int {
            a = 36969 * (a & M) + (a >> 16);
            b = 18000 * (b & M) + (b >> 16);
            return (C & ((a << 16) + b)) % 1000000;
        };
        struct Triple {
            int x;
            int y;
            int z;
        };
        vector<Triple> triples(m + n);
        for (int i = 0; i < m; i += 1) {
            cin >> triples[i].x >> triples[i].y >> triples[i].z;
        }
        for (int i = m; i < m + n; i += 1) {
            triples[i].x = gen();
            triples[i].y = gen();
            triples[i].z = gen();
        }
        auto comp = [] (Triple a, Triple b) {
            if (a.x != b.x) return a.x < b.x;
            if (a.y != b.y) return a.y > b.y;
            return a.z > b.z;
        };
        sort(triples.begin(), triples.end(), comp);
        struct YZ {
            int y;
            int z;
            bool operator<(const YZ& another) const {
                if (y != another.y) return y < another.y;
                return z > another.z;
            }
        };
        int sz = int(triples.size());
        vector<set<YZ>> last(sz+1);
        auto can_continue_from = [&] (int from, int y, int z) -> bool {
            auto it = last[from].lower_bound({y, z});
            if (it == last[from].begin()) return false;
            it--;
            return it->z < z;
        };
        auto continue_from = [&] (int from, int y, int z) -> void {
            auto it = last[from + 1].upper_bound({y, z});
            while (it != last[from+1].end() && it->z >= z) {
                last[from + 1].erase(it);
                it = last[from + 1].upper_bound({y, z});
            }
            last[from + 1].insert({y, z});
        };
        for (const auto &[x, y, z] : triples) {
            int l = 1, r = sz - 1;
            int good = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (can_continue_from(mid, y, z)) {
                    good = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            continue_from(good, y, z);
        }
        for (int ans = sz; ans >= 1; ans -= 1) {
            if (!last[ans].empty()) {
                cout << ans << "\n";
                break;
            }
        }
    }
}