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
#define roff(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
//ostream& endl(ostream& os) {
//    return os << '\n';
//}
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
uniform_int_distribution<ll> distrib(0ll, LLONG_MAX);
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
ld rand01 () {
    ld shit1 = distrib(rng);
    ld shit2 = distrib(rng);
    return min(shit1, shit2)/max(shit1, shit2);
}
struct shit {
    char c;
    ll r, b;
};
ll MAX_T = 1.96e6;
ld temp = 1e3;
vector<shit> a;
ll n;
ll calc() {
    ll have_red = 0;
    ll have_blue = 0;
    ll tot = n;
    ll money_red = 0;
    ll money_blue = 0;
    fo(i,0,n){
        ll price_red = max(0ll, a[i].r-have_red);
        ll can_spend_red = min(money_red, price_red);
        price_red -= can_spend_red;
        money_red -= can_spend_red;
        ll price_blue = max(0ll, a[i].b-have_blue);
        ll can_spend_blue = min(money_blue, price_blue);
        price_blue -= can_spend_blue;
        money_blue -= can_spend_blue;
        tot += max(price_red, price_blue);
        money_red += max(0ll, price_blue-price_red);
        money_blue += max(0ll, price_red-price_blue);
        if (a[i].c == 'R') have_red += 1;
        else have_blue += 1;
    }
    return tot;
}

void solve() {
    cin >> n;
    uniform_int_distribution<ll> distribution(0, n-1);
    a.resize(n);
    fo(i,0,n)cin>>a[i].c>>a[i].r>>a[i].b;
    auto start = chrono::high_resolution_clock::now();
    ll ans = calc();
    ll prev_res = ans;
    while (true) {
        auto curr_time = chrono::high_resolution_clock::now();
        if (chrono::duration_cast<chrono::microseconds>(curr_time-start).count() >= MAX_T) {
            cout << ans << endl;
            return;
        }
        auto prev_state = a;
        swap(a[distribution(rng)], a[distribution(rng)]);
        swap(a[distribution(rng)], a[distribution(rng)]);
        ll res = calc();
        if (res <= prev_res) {
//            clog << prev_res << " -> " << res;
            ans = res;
            prev_res = res;
        } else {
//            clog << res << " " << prev_res << endl;
            ld e_power = (ld)((prev_res-res))/temp;
            ld move = expl(e_power);
//            clog << e_power << endl;
//            clog << move << endl;
            if (move < rand01()) {
                a = prev_state; // otkat
            } else {
                prev_res = res; // izmenenie
            }
        }
        temp *= 0.9999;
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
