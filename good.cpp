#include <bits/stdc++.h>
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
ostream& endl(ostream& os) {
    return os << '\n';
}
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
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/

void solve(ll p) {
    vector<ll> pr;
    ll limit = 1e7;
    vector<ll> lp(limit+1, 0);
    forr(i, 2, limit) {
        if (lp[i] == 0) {
            cout << i << endl;
            pr.push_back(i);
            lp[i] = i;
        }
        ll j = 0;
        while (j < pr.size() && pr[j] <= lp[i] && pr[j]*i <= limit) {
            lp[pr[j]*i] = pr[j];
            j += 1;
        }
    }
//    ll p; cin >> p;
    clog << "p = " << p << endl;
    auto start = chrono::high_resolution_clock::now();
    vll r(p/2+1);
    vll sotki(p/100 + 1);
    sotki[0] += 1;
    r[1] = 1;
    // ВЫЧИСЛИТЬ ВСЕ j ДЛЯ ВЫЧИСЛЕНИЯ КОТОРЫХ ИСПОЛЬЗУЕТСЯ i
    // ВЫЧИСЛИТЬ ВСЕ j ДЛЯ ВЫЧИСЛЕНИЯ КОТОРЫХ ИСПОЛЬЗУЕТСЯ i
    // ВЫЧИСЛИТЬ ВСЕ j ДЛЯ ВЫЧИСЛЕНИЯ КОТОРЫХ ИСПОЛЬЗУЕТСЯ i

//    for (ll i = 1; i < p/2+1; i += 1) {
    for (ll i = 1; i < p/2+1; i += 1) {
//        cout << i << endl;
        ll dividend = p - i;
        // p%J=i, find all Js
        vll divs;
        ll temp = dividend;
        while (temp != 1) {
            divs.push_back(lp[temp]);
            temp /= lp[temp];
        }
        ll divs_sz = divs.size();
        cout << dividend << ": ";
        forr(i, 0, divs_sz-1) cout << divs[i] << ' ';
        cout << endl;
        for (ll mask = 0; mask < (1 << divs_sz); mask += 1) {
            ll divisor = 1;
            forr(i, 0, divs_sz-1) if ((1 << i) & mask) divisor *= divs[i];
            if (divisor > i) {
                ll that_i = divisor;
                ll that_curr = ((-(p / that_i) * r[i]) % p + p) % p;
                sotki[that_i/100] += that_curr;
                if (that_i <= p/2+1) r[that_i] = that_curr;
            }
        }
    }
    for (ll i=0; i < p/100+1; i++) {
        cout << sotki[i] % p << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds> (stop-start) << endl;
}

int32_t main(int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
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
//        for (ll p=2; p <= (ll)1e8; p++) {
//            bool prime = true;
//            for (ll j=2; j*j <= p; j++) {
//                if (p % j == 0) prime=false;
//            }
//            if (prime) solve(p);
//        }
        ll p; cin >> p; solve(p);
    }
    return 0;
}