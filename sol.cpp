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
//ostream& endl(ostream& os) {
//    return os << '\n';
//}
//define all(xxx) xxx.begin(), xxx.end()
//define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
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
void solve() {
    ll n; cin >> n;
    vvll sm1(n);
    vvll sm2(n);
    bitset<1000000> seen;
    for (ll i = 0; i < n-1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        sm1[u].push_back(v);
        sm1[v].push_back(u);
    }
    for (ll i = 0; i < n-1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        sm2[u].push_back(v);
        sm2[v].push_back(u);
    }
    vll subtree_sz1(n);
    vll subtree_sz2(n);
    auto calc_sz = [&] (auto f, ll v, vvll & sm, vll & subtree_sz) -> ll {
        seen[v] = true;
        subtree_sz[v] = 1;
        for (const auto &u : sm[v]) {
            if (!seen[u]) {
                subtree_sz[v] += f(f, u, sm, subtree_sz);
            }
        }
        return subtree_sz[v];
    };
    seen.reset();
    calc_sz(calc_sz, 0, sm1, subtree_sz1);
    seen.reset();
    calc_sz(calc_sz, 0, sm2, subtree_sz2);
    vll centroids1;
    vll centroids2;
    auto find_centroids = [&] (auto f, ll v, vvll &sm, vll &centroids, vll &subtree_sz) -> ll {
        seen[v] = true;
        for (const auto &u : sm[v]) if (!seen[u]) {
            seen[u] = true;
            if (subtree_sz[u] > n/2) {
                return f(f, u, sm, centroids, subtree_sz);
            } else if (subtree_sz[u] == n/2) {
                centroids.push_back(u);
            }
        }
        return v;
    };
    seen.reset();
    centroids1.push_back(find_centroids(find_centroids, 0, sm1, centroids1, subtree_sz1));
    seen.reset();
    centroids2.push_back(find_centroids(find_centroids, 0, sm2, centroids2, subtree_sz2));
    auto calc_hash = [&] (auto f, ll v, vvll &sm) -> ld {
        seen[v] = true;
        ld sum = 42;
        vector<ld> l;
        for (const auto &u : sm[v]) {
            if (!seen[u]) {
                seen[u] = true;
                l.push_back(f(f, u, sm));
            }
        }
        sort(l.begin(), l.end());
        for (const auto &x : l) {
            sum += log(x);
        }
        return sum;
    };
    vector<ld> first;
    vector<ld> second;
    for (const auto &c : centroids1) {
        seen.reset();
        first.push_back(calc_hash(calc_hash, c, sm1));
    }
    for (const auto &c : centroids2) {
        seen.reset();
        second.push_back(calc_hash(calc_hash, c, sm2));
    }
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
//    print(first);
//    print(second);
    cout << (first == second?"YES":"NO") << endl;
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
