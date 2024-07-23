#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define endl '\n'
using namespace std;
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
constexpr int N = (ll)(2e5+10);
//constexpr int N = (ll)(6e4+10);
constexpr ll FALLEN_SET = (ll) 1e18;
constexpr ll FALLEN_CHECK = (ll) 2e14+1;
struct node {
    ll val1;
    ll idx;
    ll to_be_pushed_to_each_child;
    ll dead_count;
    explicit node(ll _idx, ll _val1, ll _dead) {
        idx = _idx;
        val1 = _val1;
        dead_count = _dead;
        to_be_pushed_to_each_child = 0;
    }
    node(): node(0, 0, 0){};
};
node merge(node node1, node node2) {
    if (node1.val1 < node2.val1) {
        node _{node1.idx, node1.val1, node1.dead_count+node2.dead_count};
        return _;
    }
    node _{node2.idx, node2.val1, node1.dead_count+node2.dead_count};
    return _;
}
void build(array<node, 4*N> & ST, vector<ll> & array, ll v, ll tl, ll tr) {
    if (tl == tr) {
        ST[v].idx = tl;
        ST[v].val1 = array[tl];
    } else {
        ll tm = (tl+tr) >> 1;
        build(ST, array, v*2, tl, tm);
        build(ST, array, v*2+1, tm+1, tr);
        ST[v] = merge(ST[v*2], ST[v*2+1]);
    }
}
void build_ez(array<node, 4*N> & ST, vector<ll> & array, ll size) {
    build(ST, array, 1, 1, size);
}
//void push_down(array<node, 4*N> & ST, ll v, ll tl, ll tr) {
void push_down(array<node, 4*N> & ST, ll v) {
    ST[v*2].to_be_pushed_to_each_child += ST[v].to_be_pushed_to_each_child;
    ST[v*2+1].to_be_pushed_to_each_child += ST[v].to_be_pushed_to_each_child;
//    ll tm = (tl+tr) >> 1;
//    ST[v*2].val1 += ST[v].to_be_pushed_to_each_child*(tm-tl+1);
//    ST[v*2+1].val1 += ST[v].to_be_pushed_to_each_child*(tr-tm);
    ST[v*2].val1 += ST[v].to_be_pushed_to_each_child;
    ST[v*2+1].val1 += ST[v].to_be_pushed_to_each_child;
    ST[v].to_be_pushed_to_each_child = 0;
}
void add_many(array<node, 4*N> & ST, ll l, ll r, ll x, ll v, ll tl, ll tr) {
    if (tl == l && tr == r) {
//        ST[v].val1 += x*(tr-tl+1);
        ST[v].val1 += x;
        ST[v].to_be_pushed_to_each_child += x;
        return;
    }
    push_down(ST, v);
    ll tm = (tl+tr) >> 1;
    if (l <= tm) {
        add_many(ST, l, min(r, tm), x, v*2, tl, tm);
    }
    if (r > tm) {
        add_many(ST, max(l, tm+1), r, x, v*2+1, tm+1, tr);
    }
    ST[v] = merge(ST[v*2], ST[v*2+1]);
}
void add_many_ez(array<node, 4*N> & ST, ll l, ll r, ll x, ll size) {
    add_many(ST, l, r, x, 1, 1, size);
}
void rewrite_one(array<node, 4*N> & ST, ll pos, node nw, ll v, ll tl, ll tr) {
    if (pos == tl && pos == tr) {
        ST[v] = nw;
        return;
    }
    push_down(ST, v);
    ll tm = (tl+tr) >> 1;
    if (pos <= tm) {
        rewrite_one(ST, pos, nw, v*2, tl, tm);
    } else {
        rewrite_one(ST, pos, nw, v*2+1, tm+1, tr);
    }
    ST[v] = merge(ST[2*v], ST[2*v+1]);
}
void rewrite_one_ez(array<node, 4*N> & ST, ll pos, node nw, ll size) {
    rewrite_one(ST, pos, nw, 1, 1, size);
}
node get_many(array<node, 4*N> & ST, ll l, ll r, ll v, ll tl, ll tr) {
    if (tl == l && tr == r) return ST[v];
    push_down(ST, v);
    ll tm = (tl+tr)>>1;
    if (l <= tm && r > tm) {
        return merge(
                get_many(ST, l, min(r, tm), 2 * v, tl, tm),
                get_many(ST, max(l, tm+1), r, 2 * v + 1, tm+1, tr)
        );
    }
    if (l <= tm) {
        return get_many(ST, l, min(r, tm), 2 * v, tl, tm);
    }
    return get_many(ST, max(l, tm+1), r, 2 * v + 1, tm+1, tr); // (r > tm)
}
node get_many_ez(array<node, 4*N> & ST, ll l, ll r, ll size) {
    return get_many(ST, l, r, 1, 1, size);
}
void solve() {
    array<node, 4*N> tree;
    ll n, q; cin >> n >> q;
    vector<ll> a(n+1);
    vector<ll> killing_dist(n+1);
    for (ll i=1; i<=n; i++) {
        cin >> killing_dist[i];
        killing_dist[i] -= 1;
        cin >> a[i];
    }
    build_ez(tree, a, n);
    while (q--) {
        ll type, l, r;
        cin >> type >> l >> r;
        if (type == 2) {
            cout << r - l + 1 - get_many_ez(tree, l, r, n).dead_count << endl;
        } else {
            ll x; cin >> x;
            add_many_ez(tree, l, r, -x, n);
            while (tree[1].val1 <= 0) {
                deque<ll> deq;
                deq.push_back(tree[1].idx);
                while (!deq.empty()) {
                    ll curr = deq.front(); deq.pop_front();
                    node _{curr, FALLEN_SET, 1};
                    rewrite_one_ez(tree, curr, _, n);
                    while (true) {
                        node nxt = get_many_ez(tree, curr, min(n, curr + killing_dist[curr]), n);
                        if (nxt.val1 >= FALLEN_CHECK) break;
                        deq.push_back(nxt.idx);
                        add_many_ez(tree, nxt.idx, nxt.idx, FALLEN_SET, n);
                    }
                }
            }
        }
    }
}

int32_t main (int argc, char* argv[]) {
    bool use_fast_io = true;
    for (int i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
            break;
        }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cerr.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}