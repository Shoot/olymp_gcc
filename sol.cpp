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
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 5ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;
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
vll manacher_odd(string &s) {
    ll n = (ll) s.size();
    vll d(n, 1);
    ll l = 0, r = 0;
    for (ll i = 1; i < n; i++) {
        if (i < r)
            d[i] = min(r - i + 1, d[l + r - i]);
        while (i - d[i] >= 0 && i + d[i] < n && s[i - d[i]] == s[i + d[i]])
            d[i]++;
        if (i + d[i] - 1 > r)
            l = i - d[i] + 1, r = i + d[i] - 1;
    }
    return d;
}
vll manacher_even(string &s) {
    ll n = (ll) s.size();
    vll d(n, 0);
    ll l = -1, r = -1;
    for (ll i = 0; i < n - 1; i++) {
        if (i < r)
            d[i] = min(r - i, d[l + r - i - 1]);
        while (i - d[i] >= 0 && i + d[i] + 1 < n && s[i - d[i]] == s[i + d[i] + 1])
            d[i]++;
        if (i + d[i] > r)
            l = i - d[i] + 1, r = i + d[i];
    }
    return d;
}
string s;
void solve2() {
    auto d1 = manacher_odd(s);
    auto d2 = manacher_even(s);
    ll n = ll(s.size());
    ll MAXI = 0;
    auto query = [&] (ll l, ll r) -> ll {
        ll kol = 0;
        ll sz = (r-l+1);
        if (sz < 0) return 0ll;
        auto ask = s.substr(l, sz);
        for (ll i = 0; i < n; i += 1) {
            if (s.substr(i, sz) == ask) {
                kol += 1;
            }
        }
        return kol;
    };
    for (ll l = 0; l < n; l += 1) {
        for (ll r = l; r < n; r += 1) {
            auto s1 = s.substr(l, r-l+1);
            auto s2 = s1;
            reverse(s2.begin(), s2.end());
            if (s2 == s1) {
                MAXI = max(MAXI, (r-l+1)*query(l, r));
            }
        }
    }
    cout << MAXI << endl;
}
void solve() {
    struct shit {
        ll idx;
        ll high_priority_class, low_priority_class;
    };
    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
//    string s(3e5, 'a');
//    ll C = 300000;
//    auto AA = string(C, 'a');
//    auto BB = string(C, 'b');
//    vector<string> SS;
//    for (ll i = 0; i < 26; i += 1) {
//        SS.push_back(string(C, 'a'+i));
//    }
//    for (ll i = 0; i < 3e5; i += C) {
//        s.append(SS[rand()%26]);
//    }
//    cout << s << endl;
    vll test(5e6);
    auto d1 = manacher_odd(s);
    auto d2 = manacher_even(s);
    ll n = ll(s.size());
    s.push_back('\0');
    n = ll(s.size());
    stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds>(stop - start) << endl;
    clog << "b4 suff" << endl;
    stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds>(stop - start) << endl;
    vll rank(n);
    vll sa(n);
    vll lcp(n - 1);
    ll alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds>(stop - start) << endl;
//    assert(chrono::duration_cast<chrono::milliseconds>(stop-start).count() <= 120);
    for (ll i = 0; i < n; i += 1) {
        rank[i] = c[i];
        sa[c[i]] = i;
    }
    ll k = 0;
    ll CNT = 0;
    for (ll i = 0; i < n; i += 1, k ? k -= 1 : 0) {
        if (rank[i] == n-1) {
            k = 0;
            continue;
        }
        ll j = sa[rank[i]+1];
        while (i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
    }
//    for (ll i = 0; i < n; i += 1) {
//        cout << lcp[rank[i]] << ' ';
//    }cout << endl;
    vvll st(20, vll(n));
    st[0] = lcp;
    for (ll b = 1; b < 20; b += 1) {
        for (ll i = 0; i < n; i += 1) {
            st[b][i] = st[b-1][i];
            ll shi = i+(1ll << (b-1));
            if (shi < n) st[b][i] = min(st[b][i], st[b-1][shi]);
        }
    }
    auto get_minimum_lcp = [&] (ll l, ll r) -> ll {
        CNT += 1;
        ll sz = r-l+1;
        ll bt = 63-__builtin_clzl(sz);
        return min(st[bt][l], st[bt][r-(1ll << bt)+1]);
    };
    auto is_first_greater = [&] (ll l1, ll r1, ll l2, ll r2) -> bool {
        if (l1 == l2) return false;
        ll rank1 = rank[l1];
        ll rank2 = rank[l2];
        //assert(rank1 != rank2);
        if (rank1 < rank2) return false;
        ll sz = r1-l1+1;
        //assert(sz == r2-l2+1);
        return get_minimum_lcp(rank2, rank1-1) < sz;
    };
    auto is_first_less = [&] (ll l1, ll r1, ll l2, ll r2) -> bool {
        if (l1 == l2) return false;
        ll rank1 = rank[l1];
        ll rank2 = rank[l2];
        //assert(rank1 != rank2);
        if (rank1 > rank2) return false;
        ll sz = r1-l1+1;
        //assert(sz == r2-l2+1);
        return get_minimum_lcp(rank1, rank2-1) < sz;
    };
    auto query = [&] (ll START, ll END) -> ll {
        assert(START <= END);
        ll sz = END-START+1;
        ll l = 0, r = n-1;
        ll first_equal = n-1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ll idx = sa[mid];
            if (is_first_greater(START, END, idx, idx+sz-1)) {
                l = mid+1;
                first_equal = mid+1;
            } else {
                r = mid-1;
            }
        }
        ll last_equal = n-1;
        l = 0, r = n-1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ll idx = sa[mid];
            if (is_first_less(START, END, idx, idx+sz-1)) {
                r = mid-1;
                last_equal = mid-1;
            } else {
                l = mid+1;
            }
        }
        ll kol = last_equal-first_equal+1;
        return kol;
    };
    ll sz = ll(s.size())-1;
//    cout << d1 << endl;
//    cout << d2 << endl;
    ll MAXI = 0;
    vpll shit(sz);
    for (ll i = 0; i < sz; i += 1) {
        shit[i].first = d1[i];
        shit[i].second = i;
    }
    sort(shit.rbegin(), shit.rend());
    clog << "b4 queries" << endl;
    stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
    for (ll i = 0; i < sz; i += 1) {
        ll l = 2*shit[i].first-1;
        if (n*l <= MAXI) break;
        ll ans = query(shit[i].second-(shit[i].first-1), shit[i].second+(shit[i].first-1));
        ll val = l*ans;
//        if (MAXI < val) {
//            cout << l << " " << ans << endl;
//        }
        MAXI = max(MAXI, val);
    }
    stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
    for (ll i = 0; i < sz; i += 1) {
        shit[i].first = d2[i];
        shit[i].second = i;
    }
    sort(shit.rbegin(), shit.rend());
    for (ll i = 0; i < sz; i += 1) {
        if (shit[i].first == 0) break;
        ll l = shit[i].first*2;
        if (n*l <= MAXI) break;
        ll ans = query(shit[i].second-shit[i].first+1, shit[i].second+shit[i].first);
        ll val = l*ans;
//        if (MAXI < val) {
//            cout << l << ",," << ans << endl;
//        }
        MAXI = max(MAXI, val);
    }
    cout << MAXI << endl;
    stop = chrono::high_resolution_clock::now();
    clog << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
    clog << CNT << "(cnt)" << endl;
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
        cin >> s;
        if (s.size() > 20) {
            solve();
        } else {
            solve2();
        }
    }
    return 0;
}
