#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#define watch(x) clog << #x << " equals " << x << endl;
#define all(value) value.begin(), value.end()
#define fo(XX, X, fi) for(ll XX = X; XX < fi; XX++)
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
#define roff(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
ostream& endl(ostream& os) {
    return os << '\n';
}
#define vv(type,name,n,...) vector<vector<type>> name(n,vector<type>(__VA_ARGS__))
#define vvv(type,name,n,m,...) vector<vector<vector<type>>> name(n,vector<vector<type>>(m,vector<type>(__VA_ARGS__)))
#define vvvv(type,name,n,m,k,...) vector<vector<vector<vector<type>>>> name(n,vector<vector<vector<type>>>(m,vector<vector<type>>(k, vector<type>(__VA_ARGS__))))
#define vvvvv(type,name,n,m,k,l,...) vector<vector<vector<vector<vector<type>>>>> name(n,vector<vector<vector<vector<type>>>>(m,vector<vector<vector<type>>>(k, vector<vector<type>>(l, vector<type>(__VA_ARGS__)))))
#define LL(...) \
  ll __VA_ARGS__; \
  IN(__VA_ARGS__)
#define fi first
#define se second
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
        if(i) os << " ";
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
uniform_int_distribution<ll> distrib(0ll, 9ll);
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
    if (i == 1) return 1; return m-((inv(m%i, i)*m)/i);
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
    string s;
    cin >> s;
    ll n = ll(s.size());
    ll o = 26;
    vll pref_hash(n+1);
    forr(i,1,n) {
        pref_hash[i] = sum(mul(pref_hash[i-1], o), s[i-1]);
    }
    ll N = 6e5;
    vll powo(N);
    vll revpow_o(N);
    powo[0] = 1;
    fo(i,1,N) {
        powo[i] = mul(powo[i-1], o);
    }
    revpow_o[N-1] = powm(powo[N-1], MOD-2);
    roff(i, N-2, 0) {
        revpow_o[i] = mul(revpow_o[i+1], o);
    }
    assert(powo[0] == 1);
    assert(powo[1] == o);
    assert(revpow_o[0] == 1);
    assert(revpow_o[1] == powm(o, MOD-2));
    function<ll(ll, ll)> compute_hash = [&] (ll l, ll r) {
        return mul(
                sub(pref_hash[r],pref_hash[l-1]),
                revpow_o[l-1]
        );
    };
    ll tot = 0;
    forr(alen,1,n-2) {
        ll curr_minus = 0;
        if (alen*3 == n) {
            // a == b == c
            ll a = compute_hash(1, alen);
            ll b = compute_hash(alen+1, alen+alen);
            ll c = compute_hash(alen+alen+1, alen+alen+alen);
            if (a == c && a == b) {
//                cout << "a == b == c";
                curr_minus -= 2;
            }
        }
        if (alen+alen+1 <= n) {
            if (compute_hash(1, alen) == compute_hash(alen+1, alen+alen)) {
//                cout << "a == b" << endl;
                curr_minus += 1;
            } else {
//                cout << "a != b" << endl;
            }
        }
        if (alen+alen+1 <= n) {
            if (compute_hash(1, alen) == compute_hash(n-alen+1, n)) {
//                cout << "a == c" << endl;
                curr_minus += 1;
            } else {
//                cout << "a != c" << endl;
            }
        }
        if ((n-alen) % 2 == 0) {
            ll b_eq_c_len = (n-alen)/2;
            if (compute_hash(alen+1, alen+b_eq_c_len) == compute_hash(n-b_eq_c_len+1, n)) {
                curr_minus += 1;
//                cout << "b == c" << endl;
            } else {
//                cout << "b != c" << endl;
            }
        }
        ll contrib = n-1-alen-curr_minus;
//        cout << alen << ": " << contrib << endl;
        tot += contrib;
    }
    cout << tot << endl;
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
//    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}