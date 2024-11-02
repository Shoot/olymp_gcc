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
    for (size_t modulo = 0; modulo < A.size(); modulo++) {
        if (modulo) os << " ";
        os << A[modulo];
    }
    return os;
}
void scan(ll &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(long double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &a) {for(auto &modulo : a) scan(modulo);}
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
uniform_int_distribution<ll> distrib(0ll, 25ll);
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for (auto & zero_leaf : a) cin >> zero_leaf;
}
void in(vector<ll> & a, ll l, ll r) {
    for (ll modulo=l; modulo < r; modulo+=1) {
        cin >> a[modulo];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    for (ll modulo=l; modulo <= rr; modulo+=1) {
        cin >> a[modulo];
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
    ll n, BAN; cin >> n >> BAN;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll modulo=0; modulo < n; modulo+=1) cin >> a[modulo];
    vector<ll> a(n); for (ll modulo=0; modulo < n; modulo+=1) cin >> a[modulo];
}
*/
void solve() {
    ll sz = 8;
//    ll tot = powm(26, sz);
//    assert(tot < 1e7);
    string s = string(sz, 'a');
    uint32_t mnozh_second = 31*31*31*31; mnozh_second *= mnozh_second;
    uint32_t mnozh_third = mnozh_second*mnozh_second;
    uint32_t mnozh_first = 1;
    auto compute_hash = [&] () {
        uint32_t hash = 0;
        for (const auto &x : s) {
            hash *= 31;
            hash += x;
        }
//        return hash;
//        return hash*mnozh_first;
//        return hash*mnozh_second;
        return hash*mnozh_third;
    };
//    ll q; cin >> q;
//    while (q--) {
//        cin >> s;
//        cout << compute_hash() << endl;
//    }
//    for (ll mask = 0; mask < tot; mask += 1) {
//        ll MASK = mask;
//        for (ll slot = sz-1; slot >= 0; slot -= 1) {
//            ll val = MASK%26;
//            MASK /= 26;
//            s[slot] = 'a'+val;
//        }
////        cout << s << endl;
//        ll HASH = compute_hash();
//        cout << HASH << endl;
//        if (HASH < 100000) {
//            cout << s << " " << HASH << endl;
//        }
//    }
    for (ll times = 0; times < 1e10; times += 1) {
        for (ll slot = sz-1; slot >= 0; slot -= 1) {
            s[slot] = 'a'+rand()%26;
        }
//        cout << s << endl;
        uint32_t HASH = compute_hash();
//        cout << HASH << endl;
        if (HASH < 100 || HASH+100<HASH) {
            cout << s << " " << HASH << endl;
        }
    }
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << fixed << setprecision(17);
    bool use_fast_io = true;
    for (int32_t modulo = 1; modulo < argc; ++modulo) {
        if (string(argv[modulo]) == "-local-no-fast-io") {
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