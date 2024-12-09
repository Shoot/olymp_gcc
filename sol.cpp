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
//define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl
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
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;
using comp = complex<double>;
const double PI = acos(-1);
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
void solve() {
    vector<comp> w;
    auto FFT = [&] (auto f, const vector<comp> &P, vector<comp>& A, bool invert,
                    ll coeff_from = 0, ll write_from = 0, ll n = -1, ll step = 1) -> void {
        assert(n != 0);
        if (n == -1) {
            n = ll(P.size());
            if (A.empty()) {
                A.resize(n);
            }
            w.resize(n);
            comp c(1);
            auto x = comp(cos(PI * 2. / n), sin(PI * 2. / n));
            if (invert) {
                x = comp(cos(PI * 2. / n), -sin(PI * 2. / n));
            }
            for (ll i = 0; i < n; i += 1) {
                w[i] = c;
                c *= x;
            }
        }
        if (n == 1) {
            A[write_from] = P[coeff_from];
            return;
        }
        f(f, P, A,  invert, coeff_from, write_from, n/2, step * 2);
        f(f, P, A, invert, coeff_from+step, write_from+n/2, n/2, step * 2);
        ll idx = 0;
        for (ll i = write_from; i < write_from+n/2; i += 1) {
            auto aa = A[i];
            auto bb = A[i + n/2];
            A[i] = aa + w[idx] * bb;
            A[i + n/2] = aa + -w[idx] * bb;
            idx += step;
        }
    };
    auto multiply = [&] (vector<ll> &A, vector<ll> &B) -> vector<ll> {
        vector<comp> one(A.begin(), A.end()), another(B.begin(), B.end());
        ll multsz = 1;
        while (multsz < ll(A.size()+B.size())) multsz <<= 1;
        one.resize(multsz);
        another.resize(multsz);
        vector<comp> FFT_direct_one;
        vector<comp> FFT_direct_another;
        FFT(FFT, one, FFT_direct_one, false);
        FFT(FFT, another, FFT_direct_another, false);

        vector<comp> values_mult(multsz);
        for (ll i = 0; i < multsz; i += 1) {
            values_mult[i] = FFT_direct_one[i] * FFT_direct_another[i];
        }
        vector<comp> coeff_mult;
        FFT(FFT, values_mult, coeff_mult, true);

        vector<ll> coeff_ll(multsz);
        for (ll i = 0; i < multsz; i += 1) {
            coeff_ll[i] = round(coeff_mult[i].real() / multsz);
        }
        return coeff_ll;
    };
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
