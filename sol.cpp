#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ostream& endl(ostream& os) {
    return os << '\n';
}
#define all(xxx) xxx.begin(), xxx.end()
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
template <class T, class S> inline bool chmax(T &a, const S &b) { return (a < b ? a = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &a, const S &b) { return (a > b ? a = b, 1 : 0); }
template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& A) {
    os << A.fi << " " << A.se;
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& A) {
    for (size_t i = 0; i < A.size(); i++) {
        if (i) os << " ";
        os << A[i];
    }
    return os;
}
void scan(ll &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(long double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &a) {for(auto &i : a) scan(i);}
template <class T> void scan(T &a) { cin >> a; }
void IN() {}
template <class Head, class... Tail> void IN(Head &head, Tail &...tail) {
    scan(head);
    IN(tail...);
}
void print() {
    cout << "\n";
}
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail) {
    cout << head;
    if (sizeof...(Tail)) cout << " ";
    print(forward<Tail>(tail)...);
}
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for (auto & zero_leaf : a) cin >> zero_leaf;
}
void in(vector<ll> & a, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> a[i];
    }
}
ll powm(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll powm(ll a, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MODD;
        b >>= 1;
        a = (a*a) % MODD;
    }
    return d;
}
ll poww(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ld poww(ld a, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll mul(ll a, ll b, ll MODD) {
    return (a*b)%MODD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sum(ll a, ll b, ll MODD) {
    return (a+b)%MODD;
}
ll sub(ll a, ll b) {
    return (a-(b%MOD)+MOD)%MOD;
}
ll sub(ll a, ll b, ll MODD) {
    return (a-(b%MODD)+MODD)%MODD;
}
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/
bitset<1'000'000> seen;
void solve() {
    seen.reset();
    ll n; cin >> n;
    ll log = 30;
    vvll sm(n);
    for (ll i = 0; i < n-1; i += 1) {
        ll u, v;
        cin >> u >> v;
        v -= 1;
        u -= 1;
        sm[u].push_back(v);
        sm[v].push_back(u);
    }
    vvll blift(31, vll(n));
    vll depth(n);
    auto compute_blifts = [&] (auto f, ll v, ll p, ll d) -> void {
        assert(!seen[v]);
        depth[v] = d;
        seen[v] = true;
        blift[0][v] = p;
        for (ll i = 1; i <= 30; i += 1) {
            blift[i][v] = blift[i-1][blift[i-1][v]];
        }
        for (const auto &x : sm[v]) if (x != p) {
                f(f, x, v, d+1);
            }
    };
    compute_blifts(compute_blifts, 0, 0, 0);
    auto compute_lca = [&] (ll u, ll v) -> ll {
        assert(u < n && v < n);
        if (depth[u]>depth[v]) swap(u, v);
        ll diff = depth[v]-depth[u]; assert(diff >= 0);
        for (ll bit = 0; bit <= 30; bit += 1) if ((1ll<<bit)&diff) {
                v = blift[bit][v];
            }
        if (v == u) return v;
        for (ll i = 30; i >= 0; i -= 1) {
            if (blift[i][v] != blift[i][u]) {
                v = blift[i][v];
                u = blift[i][u];
            }
        }
        assert(v != u && blift[0][v] == blift[0][u]);
        return blift[0][u];
    };
    ll q; cin >> q;
    while (q--) {
        ll sz; cin >> sz;
        vll a(sz);
        for (auto &x : a) {
            cin >> x;
            x-=1;
        }
        sort(all(a), [&] (ll a, ll b) {
            return depth[a]>depth[b];
        });
        // чекаем одну ветку
        set<ll> vetka;
        for (ll i = 0; i < sz; i += 1) if (compute_lca(a[i], a[0]) == a[i]) {
                vetka.insert(a[i]);
            }
        vll rest;
        set<ll> another_vetka;
        ll restsz = 0;
        for (const auto &x : a) if (!vetka.contains(x)) rest.push_back(x), restsz+=1;
        for (const auto &x : rest) {
            if (compute_lca(x, rest[0]) != x) {
                break;
            }
            another_vetka.insert(x);
        }
        if (vetka.size() + another_vetka.size() == sz && (rest.empty() ||
                                                          depth[compute_lca(a.front(), rest.front())] <= depth[a.back()])) { // a.first() в первую ветку!!
            // ^^ чекнули LCA самых низких из обеих веток
            // этот LCA должен быть выше или на высоте самой высокой вершины
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << fixed << setprecision(17);
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
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

    while (tt--) {
        solve();
    }
    return 0;
}