#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> check(n);
    vector<int> need(n);
    for (int i = 0; i < m; i += 1) {
        int p;
        cin >> p;
        p -= 1;
        check[p].push_back(i);
    }
    for (auto &x : need) {
        cin >> x;
    }
    int k;
    cin >> k;
    enum Type{ADD, ASK};
    struct Ask {
        int owner;
        Ask(int x) {
            owner = x;
        }
    };
    struct Add {
        int l;
        int r;
        int x;
        int i;
        Add(int v, int w, int y, int z) {
            l = v;
            r = w;
            x = y;
            i = z;
        }
    };
    struct Query {
        Type tp;
        void* ptr;
        Query(Type y, void* z) {
            tp = y;
            ptr = z;
        }
    };
    vector<Query> qs;
    for (int i = 0; i < n; i += 1) {
        qs.push_back(Query(ASK, new Ask(i)));
    }
    for (int i = 1; i <= k; i += 1) {
        int l, r, x;
        cin >> l >> r >> x;
        l -= 1;
        r -= 1;
        qs.push_back(Query(ADD, new Add(l, r, x, i)));
    }
    vector<int> undecided; // [owner_id]
    for (int i = 0; i < n; i += 1) {
        undecided.push_back(i);
    }
    vector<int> l(n, 0);
    vector<int> r(n, k);
    vector<int> good(n, k+1);
    vector<__int128> done(n);
    vector<int> nw;
    nw.reserve(1e6);
    undecided.reserve(1e6);
    auto get_idx = [&] (const Query& q) -> int {
        if (q.tp == ADD) {
            return reinterpret_cast<Add*>(q.ptr)->i;
        }
        int ow = reinterpret_cast<Ask*>(q.ptr)->owner;
        return (l[ow] + r[ow]) >> 1;
    };
    auto do_layer = [&] () -> void {
        sort(qs.begin(), qs.end(), [&] (const Query& q1, const Query& q2) {
            if (get_idx(q1) == get_idx(q2)) {
                return q1.tp < q2.tp;
            }
            return get_idx(q1) < get_idx(q2);
        });
        vector<__int128> curr(m);
        auto inc = [&] (int r, const int val) -> void { // r \in [0, m-1]
            if (!(r >= 0 && r < m)) return;
            r += 1;
            for (; r <= m; r += r & -r) {
                curr[r-1] += val;
            }
        };
        auto gt = [&] (int idx) -> __int128 {
            if (!(idx >= 0 && idx < m)) return 0;
            idx += 1;
            __int128 ret = 0;
            for (; idx; idx -= idx & -idx) {
                ret += curr[idx-1];
            }
            return ret;
        };
        for (const auto &[tp, ptr] : qs) {
            if (tp == ADD) {
                auto add = reinterpret_cast<Add*>(ptr);
                if (add->l <= add->r) {
                    inc(add->l, add->x);
                    inc((add->r)+1, -(add->x));
                } else {
                    inc(add->l, add->x);
                    inc(m, -(add->x));
                    inc(0, add->x);
                    inc((add->r)+1, -(add->x));
                }
            } else {
                auto ask = reinterpret_cast<Ask*>(ptr);
                for (const auto &x : check[ask->owner]) {
                    done[ask->owner] += gt(x);
                }
            }
        }
    };
    while (undecided.size()) {
        nw.clear();
        fill(done.begin(), done.end(), 0);
        do_layer();
        for (const auto &owner_id : undecided) {
            int mid = (l[owner_id] + r[owner_id]) >> 1;
            if (done[owner_id] >= need[owner_id]) {
                r[owner_id] = mid-1;
                good[owner_id] = mid;
            } else {
                l[owner_id] = mid+1;
            }
            if (l[owner_id] <= r[owner_id]) {
                nw.push_back(owner_id);
            }
        }
        swap(undecided, nw);
    }
    for (const auto &x : good) {
        if (x == k+1) {
            cout << "NIE\n";
        } else {
            cout << x << "\n";
        }
    }cout << "\n";
}