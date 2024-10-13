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
struct Node {
    ll l, r, sum;
    Node() {
        l=r=0;
        sum=0;
    }
};
bitset<1001> full1;
const ll N = 2.1e5;
vll Root(N);
vector<Node> Tree(20*N);
vector<ll> Id(20*N);
vector<bitset<1001>> dp(2*N);
ll n = 0ll, m = 0ll, nw = 0ll, avail = 0ll;
ll build_polka(ll id, ll polka, ll l=1,ll r=n) {
    ll u=++avail;
    Tree[u]=Tree[id];
    if (l==r) {
        ++nw;
        Id[u]=nw;
        return u;
    }
    ll mid=(l+r) >> 1;
    if (polka<=mid) Tree[u].l=build_polka(Tree[u].l,polka,l,mid);
    else Tree[u].r=build_polka(Tree[u].r,polka,mid+1,r);
    return u;
}
ll point_set_query(ll id, ll polka, ll mesto, ll value, ll l=1, ll r=n) {
    ll u=++avail;
    Tree[u]=Tree[id];
    if (l==r) {
        ++nw;
        Id[u]=nw;
        dp[nw]=dp[Id[id]];
        ll sum_after_point_update=Tree[id].sum;
        if (value!=dp[nw].test(mesto)) {
            dp[nw].flip(mesto);
            if (value) sum_after_point_update += 1;
            else sum_after_point_update -= 1;
        }
        Tree[u].sum=sum_after_point_update;
        return u;
    }
    ll mid=(l+r) >> 1;
    if (polka<=mid) Tree[u].l=point_set_query(Tree[u].l,polka,mesto,value,l,mid);
    else Tree[u].r=point_set_query(Tree[u].r,polka,mesto,value,mid+1,r);
    Tree[u].sum=Tree[Tree[u].l].sum+Tree[Tree[u].r].sum;
    return u;
}
ll toggle_range_query(ll id, ll pos, ll l=1, ll r=n) {
    ll u=++avail;
    Tree[u]=Tree[id];
    if (l==r) {
        ++nw;
        Id[u]=nw;
        dp[nw]=dp[Id[id]];
        Tree[u].sum=m-Tree[id].sum;
        dp[nw]=dp[nw]^full1;
        return u;
    }
    ll mid=(l+r) >> 1;
    if (pos<=mid) Tree[u].l=toggle_range_query(Tree[u].l,pos,l,mid);
    else Tree[u].r=toggle_range_query(Tree[u].r,pos,mid+1,r);
    Tree[u].sum=Tree[Tree[u].l].sum+Tree[Tree[u].r].sum;
    return u;
}
void solve() {
    cin >> n >> m;
    ll q; cin >> q;
    full1.set();
    for (ll i = 1; i <= n; i += 1) Root[0] = build_polka(Root[0], i);
    for (ll qq = 1; qq <= q; qq += 1) {
        ll type; cin >> type;
        if (type == 1) {
            // a[polka][mesto] = 1
            ll polka, mesto;
            cin >> polka >> mesto;
            Root[qq]=point_set_query(Root[qq-1],polka,mesto,1);
        } else if (type == 2) {
            // a[polka][mesto] = 0
            ll polka, mesto;
            cin >> polka >> mesto;
            Root[qq]=point_set_query(Root[qq-1],polka,mesto,0);
        } else if (type == 3) {
            // invert a[polka]
            ll polka; cin >> polka;
            Root[qq]=toggle_range_query(Root[qq-1],polka);
        } else {
            // restart from state #x
            ll x; cin >> x;
            Root[qq]=Root[x];
        }
        cout << Tree[Root[qq]].sum << endl;
    }
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
