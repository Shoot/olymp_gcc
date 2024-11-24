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
using vvpll = vector<vector<pll>>;
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
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl
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
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 5ll);
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
vvll sm;
vvll sm_rev;
vbo seen;
vll comp;
ll n;
void solve() {
    auto add_disj = [&] (ll a, ll a_is_neg, ll b, ll b_is_neg) -> void {
        a = (2 * a) ^ a_is_neg;
        b = (2 * b) ^ b_is_neg;
        ll neg_a = a ^ 1;
        ll neg_b = b ^ 1;
        sm[neg_a].push_back(b);
        sm_rev[b].push_back(neg_a);
        sm[neg_b].push_back(a);
        sm_rev[a].push_back(neg_b);
    };
    auto add_eq = [&] (ll a, ll b) -> void {
        a = (2 * a);
        b = (2 * b);
        ll neg_a = a ^ 1;
        ll neg_b = b ^ 1;
        sm[a].push_back(b);
        sm[b].push_back(a);
        sm_rev[b].push_back(a);
        sm_rev[a].push_back(b);
        sm[neg_b].push_back(neg_a);
        sm[neg_a].push_back(neg_b);
        sm_rev[neg_a].push_back(neg_b);
        sm_rev[neg_b].push_back(neg_a);
    };
    auto add_uneq = [&] (ll a, ll b) -> void {
        a = (2 * a);
        b = (2 * b);
        ll neg_a = a ^ 1;
        ll neg_b = b ^ 1;
        sm[a].push_back(neg_b);
        sm[b].push_back(neg_a);
        sm_rev[b].push_back(neg_a);
        sm_rev[a].push_back(neg_b);
        sm[neg_b].push_back(a);
        sm[neg_a].push_back(b);
        sm_rev[neg_a].push_back(b);
        sm_rev[neg_b].push_back(a);
    };
    ll curr = 0;
    auto solvable = [&] () -> bool {
        vll toposort;
        auto dfs = [&] (auto f, ll v) -> void {
            seen[v] = true;
            for (const auto &x : sm[v]) {
                if (!seen[x]) {
                    seen[x] = true;
                    f(f, x);
                }
            }
            toposort.push_back(v);
        };
        ll COMP = 0;
        auto dfs_rev = [&] (auto f, ll v) -> void {
            comp[v] = COMP;
            for (const auto &x : sm_rev[v]) {
                if (comp[x] == -1) {
                    comp[x] = COMP;
                    f(f, x);
                }
            }
        };
        for (ll i = 0; i < curr; i += 1) {
            if (!seen[2*i]) dfs(dfs, 2*i);
            if (!seen[2*i+1]) dfs(dfs, 2*i+1);
        }
        reverse(all(toposort));
        for (const auto &x : toposort) {
            if (comp[x] == -1) {
                dfs_rev(dfs_rev, x);
                COMP += 1;
            }
        }
        bool OK = true;
        for (ll i = 0; i < curr; i += 1) {
            OK &= comp[2*i] != comp[2*i+1];
        }
        return OK;
    };
    // last_solvable
    cin >> n;
    ll good = -1;
    ll l = 0, r = n-1;
    struct shit {
        ll x;
        ll y;
        ll val1;
        ll val2;
    };
    vector<shit> a(n);
    map<ll, ll> stroka;
    map<ll, ll> stolbec;
    for (ll i = 0; i < n; i += 1) {
        cin >> a[i].x >> a[i].y >> a[i].val1 >> a[i].val2;
        if (stroka.count(a[i].x) == 0) {
            stroka[a[i].x] = curr++;
        }
        if (stolbec.count(a[i].y) == 0) {
            stolbec[a[i].y] = curr++;
        }
        a[i].x = stroka[a[i].x];
        a[i].y = stolbec[a[i].y];
    }
    auto ok = [&] (ll up_to) -> bool {
        sm.assign(4*n+10, vll());
        sm_rev.assign(4*n+10, vll());
        seen.assign(4*n+10, false);
        comp.assign(4*n+10, -1);
        for (ll i = 0; i <= up_to; i += 1) {
            if (a[i].val1 == a[i].val2) {
                add_eq(a[i].x, a[i].y);
            } else {
                add_uneq(a[i].x, a[i].y);
            }
        }
        return solvable();
    };
    while (l <= r) {
        ll mid = (l+r) >> 1;
        if (ok(mid)) {
            good = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    for (ll i = 0; i < n; i += 1) {
        cout << (i<=good?"Yes":"No") << endl;
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
