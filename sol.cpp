#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(2e5);
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
struct node {
    ll val1;
    explicit node(ll _val1) {
        val1 = _val1;
    }
    node(): node(0){};
};
node merge(node node1, node node2) {
    return node{gcd(node1.val1, node2.val1)};
}
void build(array<node, 4*N> & ST, ll array[], ll v, ll tl, ll tr) {
    if (tl == tr) {
        ST[v].val1 = array[tl];
    } else {
        ll tm = (tl+tr) >> 1;
        build(ST, array, v*2, tl, tm);
        build(ST, array, v*2+1, tm+1, tr);
        ST[v] = merge(ST[v*2], ST[v*2+1]);
    }
}
void build_ez(array<node, 4*N> & ST, ll array[], ll size) {
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

ll gcd(int a, int b) {
    while (b) {
        a = a % b;
        swap(a, b);
    }
    return a;
}
void solve() {
    ll n, q; cin >> n >> q;
    array<node, 4*N> tree_a;
    array<node, 4*N> tree_b;
    ll a[n+1]; forr(i, 1, n) cin >> a[i];
    ll b[n+1]; forr(i, 1, n) cin >> b[i];
    ll razna[n+1];
    ll raznb[n+1];
    razna[n] = raznb[n] = 0;
    for (ll i = n-1; i >= 1; --i) {
        razna[i] = a[i+1] - a[i];
        raznb[i] = b[i+1] - b[i];
    }
    build_ez(tree_a, razna, n);
    build_ez(tree_b, raznb, n);
    while (q--) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        ll shita, shitb;
        if (x2 != x1) shita = get_many_ez(tree_a, x1, x2-1, n).val1;
        else shita = 0;
        if (y2 != y1) shitb = get_many_ez(tree_b, y1, y2-1, n).val1;
        else shitb = 0;
        cout << gcd(
                a[x1] + b[y1],
                gcd(shita,
                    shitb)) << endl;
    }
}
int32_t main (int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
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
//    fo(i, 0, 1) skip.insert(distrib(rng));
//    cin >> tt;
    while (tt--) solve();
    return 0;
}