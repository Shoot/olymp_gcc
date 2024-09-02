#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1ll, 200000ll);
constexpr ll N = (ll)(1e15);
constexpr ll MOD99 = 998244353;
constexpr ll MOD7 = 1e9 + 7;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
ll tot=0;
//ll n, x;
//ll n=1e5, x=distrib(rng);
ll n=1e5, x=3e14;
ll query (ll index, vector<ll> & tree)  {
    ll sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}

ll get_segment_sum(ll left, ll right, vector<ll> & tree) {
    return query(right+2, tree) - query(left+2 - 1, tree);
}

void increment_point(ll index, vector<ll> & tree) {
    index += 2;
    while (index < tree.size()) {
        tree[index] += 1ll;
        index += index & -index;
    }
}
void compute(ll l, ll r, vector<ll> & a, vector<ll> & b) {
    //clog << "L,R: " << l <<  "," << r << endl;
    if (l == r) {
        ll single_good = (a[l]+b[l] <= x);
        //clog << "l=r=" << l << ", adding " << single_good << endl;
        tot += single_good;
        return;
    }
    ll sz = (r-l+1)/2;
    ll mid = (l+r) >> 1;
    vector<ll> su_l (sz, N);
    vector<ll> su_r (sz, N);
    vector<ll> mi_l (sz, N);
    vector<ll> mi_r (sz, N);
    ll su = 0;
    ll mini = N;
    fo(i, 0, sz) {
        su += b[mid-i];
        mini = min(mini, a[mid-i]);
        if (su >= N) {
            break;
        }
        su_l[i] = su;
        mi_l[i] = mini;
    }
    su = 0;
    mini = N;
    fo(i, 0, sz) {
        su += b[mid+1+i];
        mini = min(mini, a[mid+1+i]);
        if (su >= N) {
            break;
        }
        su_r[i] = su;
        mi_r[i] = mini;
    }
    vector<ll> mi_l_szh = mi_l;
    vector<ll> su_l_szh = su_l;
    vector<ll> mi_r_szh = mi_r;
    vector<ll> su_r_szh = su_r;
    sort(all(mi_l_szh));
    sort(all(su_l_szh));
    sort(all(mi_r_szh));
    sort(all(su_r_szh));
    mi_l_szh.erase(unique(all(mi_l_szh)), mi_l_szh.end());
    su_l_szh.erase(unique(all(su_l_szh)), su_l_szh.end());
    mi_r_szh.erase(unique(all(mi_r_szh)), mi_r_szh.end());
    su_r_szh.erase(unique(all(su_r_szh)), su_r_szh.end());
    //clog << "su_l: ";
//    for (ll j: su_l) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "mi_l: ";
//    for (ll j: mi_l) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "su_r: ";
//    for (ll j: su_r) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "mi_r: ";
//    for (ll j: mi_r) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "su_l_szh: ";
//    for (ll j: su_l_szh) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "mi_l_szh: ";
//    for (ll j: mi_l_szh) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "su_r_szh: ";
//    for (ll j: su_r_szh) {
    //clog << j << ' ';
//    }
    //clog << endl;
    //clog << "mi_r_szh: ";
//    for (ll j: mi_r_szh) {
    //clog << j << ' ';
//    }
    //clog << endl;
    vector<vector<pair<ll, ll>>> starts (mi_r_szh.size()+1);
    vector<pair<ll, ll>> finishes;
    vector<vector<ll>> points (mi_r_szh.size()+1);
    vector<ll> tree(su_r_szh.size()+10);
    fo(i, 0, sz) {
        if (su_r[i] >= N) {
            break;
        }
        //clog << "adding to mp_r: " << mi_r[i] << "," << su_r[i] << endl;
        ll lb_min = lower_bound(all(mi_r_szh), mi_r[i])-mi_r_szh.begin();
        ll lb_sum = lower_bound(all(su_r_szh), su_r[i])-su_r_szh.begin();
        //clog << "lb_min: " << lb_min << endl;
        //clog << "lb_sum: " << lb_sum << endl;
        points[lb_min].push_back(lb_sum);
    }
    fo(i, 0, sz) {
        ll minimum = mi_l[i];
        ll summa = su_l[i];
        if (su_r_szh[0] <= x-summa-minimum) {
            ll looking_lb_min = lower_bound(all(mi_r_szh), minimum)-mi_r_szh.begin();
            ll looking_lb_sum = lower_bound(all(su_r_szh), x-summa-minimum)-su_r_szh.begin();
            if (su_r_szh[looking_lb_sum] > x-summa-minimum) looking_lb_sum -= 1;
            //clog << minimum << "," << summa << " looking for lb_min>=" << looking_lb_min << " and lb_sum<=" << looking_lb_sum;
            starts[looking_lb_min].push_back(make_pair(0, looking_lb_sum));
            finishes.push_back(make_pair(0, looking_lb_sum));
            //clog << " (l -> r) from " << i << ": " << from_here << endl;
        } else {
            //clog << "(l -> r) from " << i << ": " << "su_r_szh[0] > x-summa-minimum=" << x-summa-minimum << endl;
        }
    }
    fo(i, 0, mi_r_szh.size()+1) {
        for (auto [ll, rr] : starts[i]) {
            tot -= get_segment_sum(ll, rr, tree);
        }
        for (ll coord : points[i]) {
            increment_point(coord, tree);
        }
    }
    for(auto [lll, rrr] : finishes) {
        tot += get_segment_sum(lll, rrr, tree);
    }
    vector<vector<pair<ll, ll>>> starts2 (mi_l_szh.size()+1);
    vector<pair<ll, ll>> finishes2;
    vector<vector<ll>> points2 (mi_l_szh.size()+1);
    vector<ll> tree2(su_l_szh.size()+10);
    fo(i, 0, sz) {
        if (su_l[i] >= N) {
            break;
        }
        //clog << "adding to mp_l: " << mi_l[i] << "," << su_l[i] << endl;
        ll lb_min = lower_bound(all(mi_l_szh), mi_l[i])-mi_l_szh.begin();
        ll lb_sum = lower_bound(all(su_l_szh), su_l[i])-su_l_szh.begin();
        //clog << "lb_min: " << lb_min << endl;
        //clog << "lb_sum: " << lb_sum << endl;
        points2[lb_min].push_back(lb_sum);
    }
    fo(i, 0, sz) {
        ll minimum = mi_r[i];
        ll summa = su_r[i];
        if (su_l_szh[0] <= x-summa-minimum) {
            ll looking_lb_min = lower_bound(all(mi_l_szh), minimum+1)-mi_l_szh.begin();
            ll looking_lb_sum = lower_bound(all(su_l_szh), x-summa-minimum)-su_l_szh.begin();
            if (su_l_szh[looking_lb_sum] > x-summa-minimum) looking_lb_sum -= 1;
            //clog << minimum << "," << summa << " looking for lb_min>=" << looking_lb_min << " and lb_sum<=" << looking_lb_sum;
            starts2[looking_lb_min].push_back(make_pair(0, looking_lb_sum));
            finishes2.push_back(make_pair(0, looking_lb_sum));
            //clog << " (l <- r) from " << i << ": " << from_here << endl;
        } else {
            //clog << "(l <- r) from " << i << ": " << "su_l_szh[0] > x-summa-minimum=" << x-summa-minimum << endl;
        }
    }
    fo(i, 0, mi_l_szh.size()+1) {
        for (auto [ll, rr] : starts2[i]) {
            tot -= get_segment_sum(ll, rr, tree2);
        }
        for (ll coord : points2[i]) {
            increment_point(coord, tree2);
        }
    }
    for(auto [lll, rrr] : finishes2) {
        tot += get_segment_sum(lll, rrr, tree2);
    }
    compute(l, mid, a, b);
    compute(mid+1, r, a, b);
}
void solve() {
    cin >> n >> x;
    ll oldn = n;
    forr(i, 0, 20) {
        if ((1 << i) >= n) {
            n = (1 << i);
            break;
        }
    }
    assert((n & (n-1)) == 0);
    vector<ll> a(n, N);
    vector<ll> b(n, N);
    fo(i, 0, oldn) {
        a[i] = distrib(rng);
        cin >> a[i];
//        assert(a[i] > 0);
    }
    fo(i, 0, oldn) {
        b[i] = distrib(rng);
        cin >> b[i];
//        assert(b[i] > 0);
    }
    auto start = chrono::high_resolution_clock::now();
    compute(0, n-1, a, b);
    cout << tot << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::microseconds>(stop - start);
    clog << "Time taken by function: " << duration.count() << " microseconds" << endl;
//    clog << queries << " queries" << endl;
//    //clog << (double)queries_time/(double)queries*2e5/1e6 << endl;
}
int32_t main (int32_t argc, char* argv[]) {
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
        //clog.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}