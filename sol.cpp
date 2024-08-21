#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
//const int N = 3e4+10;
const int N = 3e5+10;
ll rnd_replacement[N+1];
ll perm_xor[N+1];
ll pref_xor[N+1];
set<pair<ll, ll>> st;
struct node {
    ll val1;
    ll idx;
    explicit node(ll _idx, ll _val1) {
        idx = _idx;
        val1 = _val1;
    }
    node(): node(0, 0){}
};
node merge(node node1, node node2) {
    if (node1.val1 > node2.val1) {
        return node{node1.idx, node1.val1};
    }
    return node{node2.idx, node2.val1};
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
node get_many(array<node, 4*N> & ST, ll l, ll r, ll v, ll tl, ll tr) {
    if (tl == l && tr == r) return ST[v];
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
void process(ll l, ll r, ll val) {
//    clog << "process: " << l << " " << r << endl;
    if (perm_xor[val] != (pref_xor[r]^pref_xor[l-1])) return;
//    clog << l << " " << r << " !" << endl;
    st.insert(make_pair(l, r));
}
void f(array<node, 4*N> & ST, ll l, ll r, ll size) {
    if (l > r) return;
//    clog << "f: " << l << " " << r << endl;
    node maxi = get_many_ez(ST, l, r, size);
//    clog << "got " << maxi.idx << endl;
    for (ll i=max(l, maxi.idx-maxi.val1+1); i<=min(r-maxi.val1+1, maxi.idx); i++) {
        process(i, min(r, i+maxi.val1-1), maxi.val1);
    }
    f(ST, l, maxi.idx-1, size);
    f(ST, maxi.idx+1, r, size);
}
void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n+1);
    pref_xor[0] = 0;
    for (ll j=1; j<=n; j++) {
        cin >> a[j];
        pref_xor[j] = pref_xor[j-1] ^ rnd_replacement[a[j]];
    }
    array<node, 4*N> tree;
    build_ez(tree, a, n);
    f(tree, 1, n, n);
    cout << st.size() << endl;
}
int32_t main (int argc, char* argv[]) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> distrib(1, LLONG_MAX);
    perm_xor[0] = 0;
    for (ll j=1; j<=N; j++) {
        rnd_replacement[j] = distrib(rng);
        perm_xor[j] = perm_xor[j-1] ^ rnd_replacement[j];
    }
    bool use_fast_io = true;
    for (int i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cerr.tie(nullptr);
        clog.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}