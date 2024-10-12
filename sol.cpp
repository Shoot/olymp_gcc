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
using namespace std;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ostream& endl(ostream& os) {
    return os << '\n';
}
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
void scan(int &a) { cin >> a; }
void scan(long long &a) { cin >> a; }
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
uniform_int_distribution<ll> distrib(1ll, 12ll);
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for (auto & x : a) cin >> x;
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
ll powm(ll a, ll b, ll MOD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
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
ll mul(ll a, ll b, ll MOD) {
    return (a*b)%MOD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sum(ll a, ll b, ll MOD) {
    return (a+b)%MOD;
}
ll sub(ll a, ll b) {
    return (a-(b%MOD)+MOD)%MOD;
}
ll sub(ll a, ll b, ll MOD) {
    return (a-(b%MOD)+MOD)%MOD;
}
ll fj0dsq983gf8(ll index, vector<ll> & tree)  {
    index += 1;
    ll sum = 0;
    while (index > 0) {
        sum += tree[index-1];
        index -= index & -index;
    }
    return sum;
} // zero-indexed!!!
ll get_sum_ft(ll left, ll right, vector<ll> & tree) {
    ll n = (ll)tree.size();
    if (!(left <= right)) return 0;
    assert(left <= right);
    if (right >= n) {
        clog << "FENWICK ALERT: R >= tree.size() (IT'S ZERO INDEXED !!!)" << endl;
        right = n-1;
    }
    ll ans = fj0dsq983gf8(right, tree);
    if (left-1 >= 0) {
        ans -= fj0dsq983gf8(left - 1, tree);
    }
    return ans;
} // zero-indexed!!!
void inc_ft(ll index, ll inc, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(index >= 0);
    assert(index < n);
    index += 1;
    while (index < n) {
        tree[index] += inc;
        index += index & -index;
    }
} // zero-indexed!!!
void build_ft(vector<ll> & a, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(tree.size() == a.size());
    for (ll i = 0; i < n; i++) {
        tree[i] += a[i];
        ll r = i | (i + 1);
        if (r < n) tree[r] += tree[i];
    }
} // zero-indexed!!!
ll inv(ll i, ll m) {
    if (i == 1) return 1;
    return m - ((inv(m % i, i) * m) / i);
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
    ll _2=-1, _3=-1, _5=-1, _7=-1, _11=-1, _13=-1, _17=-1;
    ll tot = 0;
    for (ll i = 0; i < 1; i += 1) {
        cout << "? " << 2 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _2 = tot%2;
            break;
        }
        tot += 1;
    }
    if (_2 == -1) _2 = (tot)%2;
    clog << "2 : " << _2 << endl;

    for (ll i = 0; i < 2; i += 1) {
        cout << "? " << 3 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _3 = tot%3;
            break;
        }
        tot += 1;
    }
    if (_3 == -1) _3 = (tot)%3;
    clog << "3 : " << _3 << endl;

    for (ll i = 0; i < 4; i += 1) {
        cout << "? " << 5 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _5 = tot%5;
            break;
        }
        tot += 1;
    }
    if (_5 == -1) _5 = (tot)%5;
    clog << "5 : " << _5 << endl;

    for (ll i = 0; i < 6; i += 1) {
        cout << "? " << 7 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _7 = tot%7;
            break;
        }
        tot += 1;
    }
    if (_7 == -1) _7 = (tot)%7;
    clog << "7 : " << _7 << endl;

    for (ll i = 0; i < 10; i += 1) {
        cout << "? " << 11 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _11 = tot%11;
            break;
        }
        tot += 1;
    }
    if (_11 == -1) _11 = (tot)%11;
    clog << "11 : " << _11 << endl;

    for (ll i = 0; i < 12; i += 1) {
        cout << "? " << 13 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _13 = tot%13;
            break;
        }
        tot += 1;
    }
    if (_13 == -1) _13 = (tot)%13;
    clog << "13 : " << _13 << endl;

    for (ll i = 0; i < 16; i += 1) {
        cout << "? " << 17 << endl;
        cout.flush();
        ll ans;
        cin >> ans;
        if (ans == 1) {
            _17 = tot%17;
            break;
        }
        tot += 1;
    }
    if (_17 == -1) _17 = (tot)%17;
    clog << "17 : " << _17 << endl;

    ll maxi = 5e5;
    for (ll i = 0; i <= maxi; i += 1) {
        if (i%2 == _2 &&
        i%3 == _3 &&
        i%5 == _5 &&
        i%7 == _7 &&
        i%11 == _11 &&
        i%13 == _13 &&
        i%17 == _17) {
            cout << "! " << i << endl;
            cout.flush();
            ll du; cin >> du;
            return;
        }
    }
    assert(false);
}

int32_t main(int32_t argc, char* argv[]) {
    cout << setprecision(17);
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
    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
