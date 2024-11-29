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
//define all(xxx) xxx.begin(), xxx.end()
//define watch(xxx) cout << "value of " << #xxx << " is " << (xxx) << endl
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
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<__int128> distrib(1ll, 100ll);
constexpr __int128 MOD = 819356875157278019ll;
//constexpr __int128 MOD = 1e9+7;
__int128 powm(__int128 best, __int128 b) {
    assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*best) % MOD;
        b >>= 1;
        best = (best*best) % MOD;
    }
    return d;
}
__int128 powm(__int128 best, __int128 b, __int128 MODD) {
    assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*best) % MODD;
        b >>= 1;
        best = (best*best) % MODD;
    }
    return d;
}
__int128 poww(__int128 best, __int128 b) {
    assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ld poww(ld best, __int128 b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
__int128 mul(__int128 best, __int128 b) {
    return (best*b)%MOD;
}
__int128 mul(__int128 best, __int128 b, __int128 MODD) {
    return (best*b)%MODD;
}
__int128 sum(__int128 best, __int128 b) {
    return (best+b)%MOD;
}
__int128 sum(__int128 best, __int128 b, __int128 MODD) {
    return (best+b)%MODD;
}
__int128 sub(__int128 best, __int128 b) {
    return (best-(b%MOD)+MOD)%MOD;
}
__int128 sub(__int128 best, __int128 b, __int128 MODD) {
    return (best-(b%MODD)+MODD)%MODD;
}
void solve() {
    constexpr ll N = 1e6+1;
    constexpr __int128 b = 31;
    vector<__int128> base(N);
    vector<__int128> revbase(N);
    base[0] = 1;
    for (ll i = 1; i < N; i += 1) {
        base[i] = mul(base[i-1], b);
    }
    revbase.back() = powm(base.back(), MOD-2);
    for (ll i = N-2; i >= 0; i -= 1) {
        revbase[i] = mul(revbase[i+1], b);
    }
    assert(revbase[0] == 1);
    string temp; cin >> temp;
    ll n = ll(temp.size());
    vll a(n+1);
    for (ll i = 1; i <= n; i += 1) {
        a[i] = temp[i-1]-'a'+1;
    }
    vector<__int128> hash(n+1);
    for (ll i = 1; i <= n; i += 1) {
        hash[i] = sum(hash[i-1], mul(a[i], base[i-1]));
    }
//    cout << "pref hash: ";
//    for (const auto &x : hash) {
//        cout << ll(x) << ' ';
//    }cout << endl;
    vvll divs(n+1);
    for (ll div = 1; div <= n; div += 1) {
        for (ll j = div; j <= n; j += div) {
            divs[j].push_back(div);
        }
    }
//    for (const auto &x : divs) {
//        for (const auto &y : x) {
//            cout << y << ' ';
//        }cout << endl;
//    }
    vector<set<ll>> good_sizes(n+1);
    for (ll i = 1; i <= n; i += 1) {
        for (const auto &div : divs[i]) {
            if (div == i) {
                good_sizes[i].insert(i);
            } else {
                if (!good_sizes[i-div].contains(div)) continue;
                if (sum(hash[i-div], mul(hash[div], base[i-div])) == hash[i]) {
                    good_sizes[i].insert(div);
                }
            }
        }
    }
    for (ll i = 1; i <= n; i += 1) {
        cout << i/(*good_sizes[i].begin()) << ' ';
    }cout << endl;
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
