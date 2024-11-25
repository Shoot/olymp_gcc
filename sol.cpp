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
//constexpr __int128 MOD = 819356875157278019ll;
constexpr __int128 MOD = 957363431467152001;
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
namespace std {
    template <>
    struct hash<__int128> {
        std::size_t operator()(__int128 value) const {
            // Simple hash function: mix the bits of __int128 into a size_t
            uint64_t high = static_cast<uint64_t>(value >> 64);
            uint64_t low = static_cast<uint64_t>(value);
            return std::hash<uint64_t>()(high) ^ (std::hash<uint64_t>()(low) << 1);
        }
    };
} // namespace std
__int128 MAXN = 2e5+10;
__int128 base = MAXN;
__int128 revbase7 = powm(base, MOD-2, MOD);
vector<__int128> base_power7(MAXN, 1);
vector<__int128> base_rev_power7(MAXN, 1);
void solve() {
    for (ll i = 1; i < MAXN; i += 1) {
        base_power7[i] = (base_power7[i-1]*base)%MOD;
        base_rev_power7[i] = (base_rev_power7[i-1]*revbase7)%MOD;
    }
    ll n; cin >> n;
    vector<string> shit(n);
    vvll pref(n);
    vll sz(n);
    for (ll i = 0; i < n; i += 1) {
        cin >> shit[i];
        sz[i] = shit[i].size();
        pref[i].resize(sz[i]+1);
    }
    for (ll x = 0; x < n; x += 1) {
        for (ll i = 0; i < sz[x]; i += 1) {
            pref[x][i+1] = sum(pref[x][i], mul(__int128(shit[x][i]-'a'+1), base_power7[i]), MOD);
        }
    }
    ll l = 1, r = *min_element(sz.begin(), sz.end());
    string ans;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_map<__int128, ll> st;
        for (ll x = 0; x < n; x += 1) {
            unordered_set<__int128> st_local;
            for (ll i = 0; i < sz[x]+1-mid; i += 1) {
                __int128 val = (((pref[x][i+mid]-pref[x][i]+MOD)%MOD)*base_rev_power7[i])%MOD;
                st_local.insert(val);
            }
            for (const auto &z : st_local) {
                st[z] += 1;
            }
        }
        bool intersected7 = false;
        __int128 got = -1;
        for (const auto &[i, j] : st) {
            assert(j <= n);
            if (j == n) {
                got = i;
                intersected7 = true;
                break;
            }
        }
        if (intersected7) {
            l = mid+1;
            ll x = 0;
            unordered_set<__int128> st_local;
            for (ll i = 0; i < sz[x]+1-mid; i += 1) {
                __int128 val = (((pref[x][i+mid]-pref[x][i]+MOD)%MOD)*base_rev_power7[i])%MOD;
                if (val == got) {
                    ans = shit[x].substr(i, mid);
                }
                st_local.insert(val);
            }
        } else {
            r = mid-1;
        }
    }
    cout << ans << endl;
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
