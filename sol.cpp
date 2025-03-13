#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    struct Edge {
        int u, v, w, idx;
        auto operator<=>(const Edge& other) const {
            if (w != other.w) {
                return w <=> other.w;
            }
            return min(u, v) <=> min(other.u, other.v);
        }
    };
    vector<Edge> edges(m);
    for (int i = 0; i < m; i += 1) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].idx = i+1;
    }
    bitset<1'00'001> used;
    auto voshlo = [&] (int x, bool final) -> int {
        used.reset();
        vector<int> p(n+1), sz(n+1, 1);
        auto find = [&] (auto f, int u) -> int {
            return p[u] = p[u] == u?u:f(f, p[u]);
        };
        auto merge = [&] (int u, int v) -> void {
            u = find(find, u);
            v = find(find, v);
            if (sz[u] > sz[v]) {
                swap(u, v);
            }
            p[u] = v;
            sz[v] += sz[u];
        };
        iota(p.begin(), p.end(), 0);
        for (auto &[u, v, w, idx] : edges) {
            if (min(u, v) == 1) {
                w += x;
            }
        }
        sort(edges.begin(), edges.end());
        int ret = 0;
        if (final) {
            n = n-1;
        }
        for (const auto &[u, v, w, idx] : edges) {
            if (find(find, u) != find(find, v)) {
                if (final && !k && min(u, v) == 1) {
                    continue;
                }
                if (final) {
                    n -= 1;
                }
                used[idx] = true;
                if (min(u, v) == 1) {
                    if (final) {
                        k -= 1;
                    }
                    ret += 1;
                }
                merge(u, v);
            }
        }
        for (auto &[u, v, w, idx] : edges) {
            if (min(u, v) == 1) {
                w -= x;
            }
        }
        return ret;
    };
    // перебираем инкремент для инцидентных ребер, чтобы вошло ровно k!!
    int good = -1e9;
    int l = -1e5-1, r = 1e5+1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int got = voshlo(mid, false);
        if (got < k) {
            r = mid - 1;
        } else {
            good = mid;
            l = mid + 1;
        }
    }
    voshlo(good, true);
    if (k || n) {
        cout << -1 << "\n";
        return 0;
    }
    cout << used.count() << "\n";
    for (int i = 1; i <= m; i += 1) {
        if (used[i]) {
            cout << i << " ";
        }
    }cout << "\n";
}