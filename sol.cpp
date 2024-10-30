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
ll fj0dsq983gf8(ll index, vector<ll> & damn)  {
    index += 1;
    ll sum = 0;
    while (index > 0) {
        sum += damn[index-1];
        index -= index & -index;
    }
    return sum;
} // zero-indexed!!!
ll get_sum_ft(ll left, ll right, vector<ll> & damn) {
    ll n = (ll)damn.size();
    if (left > right) return 0;
    assert(left <= right);
    if (right >= n) {
        clog << "FENWICK ALERT: R >= damn.size() (IT'S ZERO INDEXED !!!)" << endl;
        right = n-1;
    }
    ll dist_from_last_bfs = fj0dsq983gf8(right, damn);
    if (left-1 >= 0) {
        dist_from_last_bfs -= fj0dsq983gf8(left - 1, damn);
    }
    return dist_from_last_bfs;
} // zero-indexed!!!
void inc_ft(ll index, ll inc, vector<ll> & damn) {
    ll n = (ll)damn.size();
    assert(index >= 0);
    assert(index < n);
    index += 1;
    while (index < n) {
        damn[index] += inc;
        index += index & -index;
    }
} // zero-indexed!!!
void build_ft(vector<ll> & a, vector<ll> & damn) {
    ll n = (ll)damn.size();
    assert(damn.size() == a.size());
    for (ll i = 0; i < n; i++) {
        damn[i] += a[i];
        ll good = i | (i + 1);
        if (good < n) damn[good] += damn[i];
    }
} // zero-indexed!!!
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/
vll a;
vector<ordered_set<pll>> damn;
pll get_equal_range(ll v, ll tl, ll tr, ll l, ll r, ll val) {
    if (tl == l && tr == r) {
//            cout << l+1 << " " << r+1 << endl;
        ll ub = damn[v].order_of_key(pll(val, 1e18));
        ll lb = damn[v].order_of_key(pll(val, -1e18));
        return pll(lb, ub);
    }
    pll ans; ans.first = 0; ans.second = 0;
    ll tm = (tl+tr) >> 1;
    if (l <= tm) {
        pll left = get_equal_range(2*v+1, tl, tm, l, min(tm, r), val);
        ans.first += left.first;
        ans.second += left.second;
    }
    if (r > tm) {
        pll right = get_equal_range(2*v+2, tm+1, tr, max(tm+1, l), r, val);
        ans.first += right.first;
        ans.second += right.second;
    }
    return ans;
}
void build(ll v, ll tl, ll tr) {
    for (ll i = tl; i <= tr; i += 1) {
        damn[v].insert(pll(a[i], i));
    }
    if (tl == tr) return;
    ll tm = (tl + tr) >> 1;
    build(2*v+1, tl, tm);
    build(2*v+2, tm + 1, tr);
}
void set_point(ll v, ll tl, ll tr, ll pos, ll val) {
    ll tm = (tl+tr) >> 1;
    damn[v].erase(pll(a[pos], pos));
    damn[v].insert(pll(val, pos));
    if (tl == tr) return;
    if (pos <= tm) {
        set_point(2*v+1, tl, tm, pos, val);
    } else {
        set_point(2*v+2, tm+1, tr, pos, val);
    }
}
void solve() {
    damn.resize(4*50000+10);
    ll n;
    cin >> n;
    a.resize(n);
    for (auto &x : a) {
        x = distrib(rng);
        cin >> x;
    }
    build(0, 0, n-1);
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i += 1) {
        char type = 'Q';
        cin >> type;
        if (type == 'Q') {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            ll less_or_eq = (y1+y2)/2;
            ll l = x1, r = x2;
            assert(l <= r);
            assert(l >= 1);
            assert(r <= n);
            pll res = get_equal_range(0, 0, n-1, l-1, r-1, less_or_eq);
            if ((y1+y2)%2 == 0) {
                ll draw = res.second-res.first;
                ll first = res.first;
                ll second = r-l+1-first-draw;
                if (first == second) {
                    cout << 0 << endl;
                } else if (first < second) {
                    cout << 2 << endl;
                } else {
                    cout << 1 << endl;
                }
                continue;
            }
            ll first = res.second;
            ll second = r-l+1-first;
            if (first == second) {
                cout << 0 << endl;
            } else if (first < second) {
                cout << 2 << endl;
            } else {
                cout << 1 << endl;
            }
        } else {
            ll pos, val;
            cin >> pos >> val;
            assert(pos >= 1);
            assert(pos <= n);
            set_point(0, 0, n-1, pos-1, val);
            a[pos-1] = val;
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
