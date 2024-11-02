#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using qll = queue<__int128>;
using vll = vector<__int128>;
using vvll = vector<vector<__int128>>;
using qld = queue<ld>;
using vld = vector<ld>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ostream& endl(ostream& os) {
    return os << '\n';
}
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
constexpr __int128 MOD = 884341072164363733ll;
//constexpr __int128 MOD = 1e9+7;
__int128 powm(__int128 a, __int128 b) {
    //assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
__int128 powm(__int128 a, __int128 b, __int128 MODD) {
    //assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*a) % MODD;
        b >>= 1;
        a = (a*a) % MODD;
    }
    return d;
}
__int128 poww(__int128 a, __int128 b) {
    //assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ld poww(ld a, __int128 b) {
    //assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
__int128 mul(__int128 a, __int128 b) {
    return (a*b)%MOD;
}
__int128 mul(__int128 a, __int128 b, __int128 MODD) {
    return (a*b)%MODD;
}
__int128 sum(__int128 a, __int128 b) {
    return (a+b)%MOD;
}
__int128 sum(__int128 a, __int128 b, __int128 MODD) {
    return (a+b)%MODD;
}
__int128 sub(__int128 a, __int128 b) {
    return (a-(b%MOD)+MOD)%MOD;
}
__int128 sub(__int128 a, __int128 b, __int128 MODD) {
    return (a-(b%MODD)+MODD)%MODD;
}
/*
void copy_this () {
    __int128 n; cin >> n;
    __int128 n, k; cin >> n >> k;
    __int128 n, q; cin >> n >> q;
    __int128 a[n]; for (__int128 i=0; i < n; i+=1) cin >> a[i];
    vector<__int128> a(n); for (__int128 i=0; i < n; i+=1) cin >> a[i];
}
*/
vll cntbycharlocal(27);
vll cntbychar(27);
void solve() {
    __int128 BASE = 31;
    __int128 IBASE = powm(31, MOD-2);
    ll n; cin >> n;
    map<__int128, vector<char>> ask;
    ll tot = 0;
    vector<string> v(n);
    for (auto &x : v) cin >> x;
    sort(v.begin(), v.end(), [] (string a, string b){return a.size() < b.size();});
    for (const auto &x : v) {
        fill(cntbycharlocal.begin(), cntbycharlocal.end(), 0);
        for (const auto &c : x) cntbycharlocal[c-'a'+1] = 1;
        for (ll i = 1; i <= 26; i += 1) cntbychar[i] += cntbycharlocal[i];
    }
    for (ll i = 0; i < n; i += 1) {
        ll sz = ll(v[i].size());
        __int128 hash = 0;
        for (ll j = sz-1; j >= 0; j -= 1) {
            hash = mul(hash, BASE);
            hash = sum(hash, v[i][j]-'a'+1);
        }
        __int128 HASH = hash;
        set<ll> chars;
        for (ll j = 1; j < sz; j += 1) {
            chars.insert(v[i][j-1]-'a'+1);
            hash = sub(hash, v[i][j-1]-'a'+1);
            hash = mul(hash, IBASE);
            if (!ask[hash].empty()) for (const auto &c : ask[hash]) {
                if (chars.contains(c)) tot += 1;
            }
        }
        hash = HASH;
        if (sz > 1) {
            ask[mul(sub(hash, v[i][0]-'a'+1), IBASE)].push_back(v[i][0]-'a'+1);
        } else {
            tot += cntbychar[v[i][0]-'a'+1]-1;
        }
    }
    cout << tot << endl;
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
    __int128 tt = 1;
//    cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}
