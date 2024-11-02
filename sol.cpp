#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using qll = queue<__int128>;
using vll = vector<__int128>;
using vvll = vector<vector<__int128>>;
using qld = queue<ld>;
using vld = vector<ld>;
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
constexpr __int128 MOD = 884341072164363733ll;
//constexpr __int128 MOD = 1e9+7;
__int128 powm(__int128 a, __int128 b) {
    //assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
__int128 powm(__int128 a, __int128 b, __int128 MODD) {
    //assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*a) % MODD;
        b >>= 1;
        a = (a*a) % MODD;
    }
    return d;
}
__int128 poww(__int128 a, __int128 b) {
    //assert(b >= 0);
    __int128 d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ld poww(ld a, __int128 b) {
    //assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
__int128 mul(__int128 a, __int128 b) {
    return (a*b)%MOD;
}
__int128 mul(__int128 a, __int128 b, __int128 MODD) {
    return (a*b)%MODD;
}
__int128 sum(__int128 a, __int128 b) {
    return (a+b)%MOD;
}
__int128 sum(__int128 a, __int128 b, __int128 MODD) {
    return (a+b)%MODD;
}
__int128 sub(__int128 a, __int128 b) {
    return (a-(b%MOD)+MOD)%MOD;
}
__int128 sub(__int128 a, __int128 b, __int128 MODD) {
    return (a-(b%MODD)+MODD)%MODD;
}
/*
void copy_this () {
    __int128 n; cin >> n;
    __int128 n, k; cin >> n >> k;
    __int128 n, q; cin >> n >> q;
    __int128 a[n]; for (__int128 i=0; i < n; i+=1) cin >> a[i];
    vector<__int128> a(n); for (__int128 i=0; i < n; i+=1) cin >> a[i];
}
*/
ll SIZE = 1'000'000;
void solve() {
    __int128 BASE = 31;
    __int128 IBASE = powm(31, MOD-2);
    ll n = 100;
    cin >> n;
    SIZE = 7e5/n;
    map<pair<int, char>, int> cnt_by_hash_and_char;
    map<int, int> cnt_by_hash_ABCDE_1_5;
    map<int, int> cnt_by_hash_FGHIJ_6_10;
    map<int, int> cnt_by_hash_KLMNO_11_15;
    map<int, int> cnt_by_hash_PQRST_16_20;
    map<int, int> cnt_by_hash_UVWXY_21_25;
    map<int, ll> SINGLE;
    ll tot = 0;
    vector<string> v(n);
    vll seen(27);
    vll nvmgroup(5);
    for (ll i = 0; i < n; i += 1) {
//        cin >> v[i];

        v[i] = string(SIZE, 'a');
        for (ll j = 0; j < 15; j += 1) v[i][j] = distrib(rng)+'a';
        for (ll j = SIZE-15; j < SIZE; j += 1) v[i][j] = distrib(rng)+'a';
        ll sz = ll(v[i].size());
        __int128 hash = 0;
        fill(seen.begin(), seen.end(), 0);
        for (const auto &x : v[i]) {
            seen[x-'a'+1] = 1;
        }
        for (ll j = 1; j < 27; j += 1) {
            if (seen[j]) SINGLE[j] += 1;
        }
        for (ll j = sz-1; j >= 0; j -= 1) {
            hash = mul(hash, BASE);
            hash = sum(hash, v[i][j] - 'a' + 1);
        }
        fill(seen.begin(), seen.end(), 0);
        fill(nvmgroup.begin(), nvmgroup.end(), 0);
        for (ll j = 1; j < sz; j += 1) {
            seen[v[i][j-1]-'a'+1] = 1;
            hash = mul(sub(hash, v[i][j-1]-'a'+1), IBASE);
            if (seen[1] && seen[2] && seen[3] && seen[4] && seen[5]) {
                cnt_by_hash_ABCDE_1_5[hash] += 1;
                nvmgroup[0] = 1;
            }
            if (seen[6] && seen[7] && seen[8] && seen[9] && seen[10]) {
                cnt_by_hash_FGHIJ_6_10[hash] += 1;
                nvmgroup[1] = 1;
            }
            if (seen[11] && seen[12] && seen[13] && seen[14] && seen[15]) {
                cnt_by_hash_KLMNO_11_15[hash] += 1;
                nvmgroup[2] = 1;
            }
            if (seen[16] && seen[17] && seen[18] && seen[19] && seen[20]) {
                cnt_by_hash_PQRST_16_20[hash] += 1;
                nvmgroup[3] = 1;
            }
            if (seen[21] && seen[22] && seen[23] && seen[24] && seen[25]) {
                cnt_by_hash_UVWXY_21_25[hash] += 1;
                nvmgroup[4] = 1;
            }
            for (ll k = 1; k <= 26; k += 1)  {
                if (seen[k]) {
                    if (k == 26 || nvmgroup[(k-1)/5] == 0) {
                        cnt_by_hash_and_char[make_pair(hash, k)] += 1;
                    }
                }
            }
        }
    }
    for (ll i = 0; i < n; i += 1) {
//        cout << i << endl;
        ll sz = ll(v[i].size());
        __int128 hash = 0;
        for (ll j = sz-1; j >= 0; j -= 1) {
            hash = mul(hash, BASE);
            hash = sum(hash, v[i][j] - 'a' + 1);
        }
        if (sz > 1) {
            ll hashik = mul(sub(hash, v[i][0]-'a'+1), IBASE);
            ll charik = v[i][0]-'a'+1;
            ll INC = cnt_by_hash_and_char[make_pair(hashik, charik)]-1;
            if (charik >= 1 && charik <= 5) {
                INC += cnt_by_hash_ABCDE_1_5[hashik];
            } else if (charik >= 6 && charik <= 10) {
                INC += cnt_by_hash_FGHIJ_6_10[hashik];
            } else if (charik >= 11 && charik <= 15) {
                INC += cnt_by_hash_KLMNO_11_15[hashik];
            } else if (charik >= 16 && charik <= 20) {
                INC += cnt_by_hash_PQRST_16_20[hashik];
            } else if (charik >= 21 && charik <= 25) {
                INC += cnt_by_hash_UVWXY_21_25[hashik];
            }
//            assert(INC >= 0);
            tot += INC;
        } else {
            ll INC = SINGLE[v[i][0]-'a'+1]-1;
            tot += INC;
//            assert(INC >= 0);
        }
//        cout << tot << "!" << endl;
    }
//    //assert(tot >= 0);
    cout << tot << endl;
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
