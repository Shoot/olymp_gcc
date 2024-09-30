#include <bits/stdc++.h>
using namespace std;
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
#define all(value) value.begin(), value.end()
#define fo(XX, X, fi) for(ll XX = X; XX < fi; XX++)
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
ostream& endl(ostream& os) {
    return os << '\n';
}
#define vv(type,name,n,...) \
    vector<vector<type>> name(n,vector<type>(__VA_ARGS__))
#define vvv(type,name,n,m,...) \
    vector<vector<vector<type>>> name(n,vector<vector<type>>(m,vector<type>(__VA_ARGS__)))
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(2ll, 10ll);
constexpr ll MOD = 1e9+7;
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
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sub(ll a, ll b) {
    return (a-b+100*MOD)%MOD;
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
const ll N = 8e5;
bitset<N> seen;
vll tree(4*N, 0);
vll add(4*N, -1);
int tt, tin[N], tout[N], vs[N];
vv(ll, sm, N, 0);
void dfsshit(int v, int p) {
    vs[tt] = v;
    tin[v] = tt++;
    cout << v << ": " << tin[v] << endl;
    fo(i, 0, sm[v].size()) if (sm[v][i] != p) dfsshit(sm[v][i], v);
    tout[v] = tt;
    cout << v << ": " << tout[v] << endl;
}
void dfs(ll v, vector<ll> & res, const vvll & sm) {
    res.push_back(v);
    for (const auto & adj : sm[v]) {
        if (!seen[adj]) {
            seen[adj] = true;
            dfs(adj, res, sm);
        }
    }
    res.push_back(v);
}

void push(ll v) {
    if (add[v] == -1) return;
    tree[v*2+1] = add[v*2+1] = add[v];
    tree[v*2+2] = add[v*2+2] = add[v];
    add[v] = -1;
}

ll get_color(ll v, ll l, ll r, ll tl, ll tr) {
    if (tl >= tr) return 0ll;
    if (tl == l && tr == r) return tree[v];
    push(v);
    ll mid = (l+r) >> 1;
    auto getl = get_color(v*2+1, l, mid, tl, min(tr, mid));
    auto getr = get_color(v*2+2, mid, r, max(mid, tl), tr);
    return getl | getr;
}

void paint(ll v, ll l, ll r, ll tl, ll tr, ll c) {
    if (tl >= tr) return;
    if (tl == l && tr == r) {
        tree[v] = c;
        add[v] = c;
    } else {
        push(v);
        ll mid = (l+r) >> 1;
        paint(v*2+1, l, mid, tl, min(tr, mid), c);
        paint(v*2+2, mid, r, max(mid, tl), tr, c);
        tree[v] = tree[v*2+1] | tree[v*2+2];
    }
}

void build(ll v, ll l, ll r, vll & a) {
    if (l + 1 == r) {
        tree[v] = a[l];
    } else {
        ll mid = (l+r) >> 1;
        build(v*2+1, l, mid, a);
        build(v*2+2, mid, r, a);
        tree[v] = tree[v*2+1] | tree[v*2+2];
    }
}

void solve() {
    seen.reset();
    ll n, q; cin >> n >> q;
    vll a(n); in(a);
    fo(i, 0, n) {
        a[i] = 1ll << (a[i]-1);
    }
    build(0, 0, n, a);
    fo(i, 0, n-1) {
        ll u, v;
        cin >> u >> v;
        u -= 1; v -= 1;
        sm[u].push_back(v);
        sm[v].push_back(u);
    }
    tt = 0;
    dfsshit(0, -1);
    vll res;
    seen[0] = true;
    dfs(0, res, sm);
    for (auto x: res) clog << x << " ";
    clog << endl;
    vll leftpos(n, -1);
    vll rightpos(n, -1);
    fo(i, 0, res.size()) {
        if (leftpos[res[i]] == -1) {
            leftpos[res[i]] = i;
        } else {
            rightpos[res[i]] = i;
        }
    }
    fo(i, 0, n) {
        clog << leftpos[i] << " " << rightpos[i] << endl;
    }
    fo(i, 0, q) {
        ll type; cin >> type;
        if (type == 1) {
            ll v, c; cin >> v >> c; v -= 1;
            c = 1ll << (c-1);
            paint(0, 0, n, tin[v], tout[v], c);
        } else {
            ll v; cin >> v; v -= 1;
            cout << __builtin_popcount(get_color(0, 0, n, tin[v], tout[v])) << endl;
        }
    }
}

int32_t main(int32_t argc, char* argv[]) {
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
