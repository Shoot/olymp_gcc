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
constexpr int N = (int)(2e5*1.2);
struct node {
    ll val1;
    ll to_be_pushed_to_each_child;
    node(ll _val1):val1(_val1), to_be_pushed_to_each_child(0){} // for merge()
    node():val1(0), to_be_pushed_to_each_child(0){} // zeros
};
node merge(node node1, node node2) {
    node _{min(node1.val1,node2.val1)};
    return _;
}
void build(node ST[], vector<ll> & array, ll v, ll tl, ll tr) {
    if (tl == tr) {
        ST[v].val1 = array[tl];
    } else {
        ll tm = (tl+tr) >> 1;
        build(ST, array, v*2, tl, tm);
        build(ST, array, v*2+1, tm+1, tr);
        ST[v] = merge(ST[v*2], ST[v*2+1]);
    }
}
void build_ez(node ST[], vector<ll> & array, ll size) {
    build(ST, array, 1, 1, size);
}
void push_down(node ST[], ll v, ll tl, ll tr) {
    ST[v*2].to_be_pushed_to_each_child += ST[v].to_be_pushed_to_each_child;
    ST[v*2+1].to_be_pushed_to_each_child += ST[v].to_be_pushed_to_each_child;
//    ll tm = (tl+tr) >> 1;
//    ST[v*2].val1 += ST[v].to_be_pushed_to_each_child*(tm-tl+1);
//    ST[v*2+1].val1 += ST[v].to_be_pushed_to_each_child*(tr-tm);
    ST[v*2].val1 += ST[v].to_be_pushed_to_each_child;
    ST[v*2+1].val1 += ST[v].to_be_pushed_to_each_child;
    ST[v].to_be_pushed_to_each_child = 0;
}
void add_many(node ST[], ll l, ll r, ll x, ll v, ll tl, ll tr) {
//    cerr << "upd: " << l << " " << r << " " << tl << " " << tr << endl;
    if (tl == l && tr == r) {
//        ST[v].val1 += x*(tr-tl+1);
        ST[v].val1 += x;
        ST[v].to_be_pushed_to_each_child += x;
        return;
    }
    push_down(ST, v, tl, tr);
    ll tm = (tl+tr) >> 1;
    if (l <= tm) {
        add_many(ST, l, min(r, tm), x, v*2, tl, tm);
    }
    if (r > tm) {
        add_many(ST, max(l, tm+1), r, x, v*2+1, tm+1, tr);
    }
    ST[v] = merge(ST[v*2], ST[v*2+1]);
    assert(ST[v].to_be_pushed_to_each_child == 0);
}
void add_many_ez(node ST[], ll l, ll r, ll x, ll size) {
    add_many(ST, l, r, x, 1, 1, size);
}
void rewrite_one(node ST[], ll pos, node nw, ll v, ll tl, ll tr) {
    if (pos == tl && pos == tr) {
        ST[v] = nw;
        return;
    }
    push_down(ST, v, tl, tr);
    ll tm = (tl+tr) >> 1;
    if (pos <= tm) {
        rewrite_one(ST, pos, nw, v*2, tl, tm);
    } else {
        rewrite_one(ST, pos, nw, v*2+1, tm+1, tr);
    }
    ST[v] = merge(ST[2*v], ST[2*v+1]);
//    cout << tl << " " << tr << ": " << ST[v].val1 << endl;
}
void rewrite_one_ez(node ST[], ll pos, node nw, ll size) {
//    cout << "!\n";
    rewrite_one(ST, pos, nw, 1, 1, size);
}
node get_many(node ST[], ll l, ll r, ll v, ll tl, ll tr) {
//    cerr << "get: " << l << " " << r << " " << tl << " " << tr << endl;
    if (tl == l && tr == r) return ST[v];
    push_down(ST, v, tl, tr);
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
node get_many_ez(node ST[], ll l, ll r, ll size) {
    return get_many(ST, l, r, 1, 1, size);
}
void solve() {
    node tree[4*N];
    ll n; cin >> n;
    vector<ll> a(n+1);
    for (int i=1; i<=n; i++) {
        cin >> a[i];
    }
    build_ez(tree, a, n);
    int q; cin >> q;
    string input;
    getline(cin, input);
    while (q--) {
        vector<int> numbers;
        getline(cin, input);
        istringstream stream(input);
        int number;
        while (stream >> number) {
            numbers.push_back(number);
        }
        if (numbers.size() == 3) {
            int l = numbers[0], r = numbers[1], x = numbers[2];
            if (l > r) {
                add_many_ez(tree, 1, r + 1, x, n);
                add_many_ez(tree, l + 1, n, x, n);
            } else {
                add_many_ez(tree, l + 1, r + 1, x, n);
            }
        } else {
            int l = numbers[0], r = numbers[1];
            if (l > r) {
                cout << merge(get_many_ez(tree, 1, r + 1, n), get_many_ez(tree, l + 1, n, n)).val1 << endl;
            } else {
                cout << get_many_ez(tree, l + 1, r + 1, n).val1 << endl;
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