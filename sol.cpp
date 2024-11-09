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
template <class T, class S> inline bool chmax(T &best, const S &b) { return (best < b ? best = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &best, const S &b) { return (best > b ? best = b, 1 : 0); }
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
void scan(ll &best) { cin >> best; }
void scan(char &best) { cin >> best; }
void scan(double &best) { cin >> best; }
void scan(long double &best) { cin >> best; }
void scan(string &best) { cin >> best; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &best) {for(auto &i : best) scan(i);}
template <class T> void scan(T &best) { cin >> best; }
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
uniform_int_distribution<ll> distrib(1ll, 10ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;
void in(vector<ll> & best) {
    for (auto & zero_leaf : best) cin >> zero_leaf;
}
void in(vector<ll> & best, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> best[i];
    }
}
void inn(vector<ll> & best, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> best[i];
    }
}
ll powm(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MOD;
        b >>= 1;
        best = (best*best) % MOD;
    }
    return d;
}
ll powm(ll best, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MODD;
        b >>= 1;
        best = (best*best) % MODD;
    }
    return d;
}
ll poww(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ld poww(ld best, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ll mul(ll best, ll b) {
    return (best*b)%MOD;
}
ll mul(ll best, ll b, ll MODD) {
    return (best*b)%MODD;
}
ll sum(ll best, ll b) {
    return (best+b)%MOD;
}
ll sum(ll best, ll b, ll MODD) {
    return (best+b)%MODD;
}
ll sub(ll best, ll b) {
    return (best-(b%MOD)+MOD)%MOD;
}
ll sub(ll best, ll b, ll MODD) {
    return (best-(b%MODD)+MODD)%MODD;
}
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll best[n]; for (ll i=0; i < n; i+=1) cin >> best[i];
    vector<ll> best(n); for (ll i=0; i < n; i+=1) cin >> best[i];
}
*/
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
void solve() {
    struct hasher {
        ll operator() (ll x) const {
            return x ^ RANDOM;
        }
    };
    ll base = 31;
    ll N = 1e5+1;
    vector<ll> basepow(N);
    vector<ll> baseipow(N);
    basepow.front() = 1;
    for (ll i = 1; i < N; i += 1) basepow[i] = mul(basepow[i-1], base);
    baseipow.back() = powm(basepow.back(), MOD-2);
    for (ll i = N-2; i >= 0; i -= 1) baseipow[i] = mul(baseipow[i+1], base);
    string s; cin >> s;
    ll n = ll(s.size());
    ll q; cin >> q;
    set<ll> lengths;
    vector<ll> ASKED_HASH(q);
    vll ASKED_KOL(q);
    vll ASKED_LEN(q);
    vvll queries_by_sz(n+1);
    vll ans(q, n);
    vll pref_hash(n);
    for (ll i = 0; i < n; i += 1) {
        if (i) pref_hash[i] = pref_hash[i-1];
        pref_hash[i] = sum(pref_hash[i], mul(s[i]-'a'+1, basepow[i]));
    }
    auto get = [&] (ll l, ll r) {
        if (l == 0) return pref_hash[r];
        return mul(sub(pref_hash[r], pref_hash[l-1]), baseipow[l]);
    };
    for (ll i = 0; i < q; i += 1) {
        cin >> ASKED_KOL[i];
        string sq; cin >> sq;
        ll lq = ll(sq.size());
        if (lq > n) {
            ans[i] = -1;
            continue;
        }
        lengths.insert(lq);
        ASKED_LEN[i] = lq;
        for (ll j = 0; j < lq; j += 1) ASKED_HASH[i] = sum(ASKED_HASH[i], mul(sq[j]-'a'+1, basepow[j]));
        queries_by_sz[lq].push_back(i);
    }
    vvll indices(q);
    for (const auto &L : lengths) {
        gp_hash_table<ll, ll, hasher> idx_by_hash;
        for (const auto &i : queries_by_sz[L]) idx_by_hash[ASKED_HASH[i]] = i;
        for (ll i = 0; i < n; i += 1) {
            if (i+L-1 >= n) break;
            ll curr = get(i, i+L-1);
            if (idx_by_hash.find(curr) != idx_by_hash.end()) indices[idx_by_hash[curr]].push_back(i);
        }
        for (const auto &i : queries_by_sz[L]) {
            ll sz = indices[i].size();
            if (sz < ASKED_KOL[i]) {
                ans[i] = -1;
            } else {
                for (ll j = 0; j < sz; j += 1) {
                    if (j+ASKED_KOL[i]-1 >= sz) break;
                    ll segment_size = indices[i][j+ASKED_KOL[i]-1]-(indices[i][j]-ASKED_LEN[i]+1)+1;
                    ans[i] = min(ans[i], segment_size);
                }
            }
        }
    }
    for (const auto &x : ans) {
        cout << x << endl;
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
