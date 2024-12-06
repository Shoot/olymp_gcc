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
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;

void solve(){
    string l, r; cin >> l >> r;
    reverse(l.begin(), l.end());
    reverse(r.begin(), r.end());
    while (l.size() != r.size()) {
        l.push_back('0');
    }
    ll dp[10][20][2][2][2]; // dp[][][][][] = kolvo_sposobov_popast_v_sostoyaniye
    ll been[10][20][2][2][2][20]; // dp[][][][][][x] = dlya dliny x — eto kolvo chisel u kotorih est otrezok iz x odinakovih cifr
    ll dp_nw[10][20][2][2][2];
    ll been_nw[10][20][2][2][2][20];
    reverse(l.begin(), l.end());
    reverse(r.begin(), r.end());
    clog << l << "," << r << endl;
    ll n = l.size();
    memset(dp, 0, sizeof(dp));
    memset(been, 0, sizeof(been));
    dp[0][1][0][0][0] = 1;
    been[0][1][0][0][0][1] = 1;
    vector<ll> kol_by_length(20);
    for (ll i = 0; i < n; i += 1) {
        clog << "i = " << i << ".." << endl;
        memset(dp_nw, 0, sizeof(dp_nw));
        memset(been_nw, 0, sizeof(been_nw));
        for (ll last = 0; last <= 9; last += 1) {
            for (ll kol = 0; kol <= 19; kol += 1) {
                for (ll more_than_l = 0; more_than_l < 2; more_than_l += 1) {
                    for (ll less_than_r = 0; less_than_r < 2; less_than_r += 1) {
                        for (ll was_non_zero = 0; was_non_zero < 2; was_non_zero += 1) {
                            if (!dp[last][kol][more_than_l][less_than_r][was_non_zero]) continue;
                            for (ll nw = 0; nw <= 9; nw += 1) {
                                if (nw < (l[i]-'0') && !more_than_l) continue;
                                if (nw > (r[i]-'0') && !less_than_r) continue;
                                ll nwkol = 1;
                                if (nw == last && (nw != 0 || was_non_zero)) nwkol += kol;
                                dp_nw[nw][nwkol][more_than_l||nw>(l[i]-'0')][less_than_r||nw<(r[i]-'0')][was_non_zero || nw != 0] += dp[last][kol][more_than_l][less_than_r][was_non_zero];
                                for (ll trkol = 0; trkol <= 19; trkol += 1) {
                                    been_nw[nw][nwkol][more_than_l||nw>(l[i]-'0')][less_than_r||nw<(r[i]-'0')][was_non_zero || nw != 0][trkol] += been[last][kol][more_than_l][less_than_r][was_non_zero][trkol];
                                }
                                been_nw[nw][nwkol][more_than_l||nw>(l[i]-'0')][less_than_r||nw<(r[i]-'0')][was_non_zero || nw != 0][nwkol] += dp[last][kol][more_than_l][less_than_r][was_non_zero]-been[last][kol][more_than_l][less_than_r][was_non_zero][nwkol];
                            }
                        }
                    }
                }
            }
        }
        swap(dp, dp_nw);
        swap(been, been_nw);
    }
    for (ll last = 0; last <= 9; last += 1) {
        for (ll kol = 0; kol <= 19; kol += 1) {
            for (ll more_than_l = 0; more_than_l < 2; more_than_l += 1) {
                for (ll less_than_r = 0; less_than_r < 2; less_than_r += 1) {
                    for (ll was_non_zero = 0; was_non_zero < 2; was_non_zero += 1) {
                        for (ll been_sz = 0; been_sz <= 19; been_sz += 1) {
                            ll shit = been[last][kol][more_than_l][less_than_r][was_non_zero][been_sz];
                            kol_by_length[been_sz] += shit;
                        }
                    }
                }
            }
        }
    }
    for (ll i = 19; i >= 0; i -= 1) {
        if (kol_by_length[i] != 0) {
            cout << i << " " << kol_by_length[i] << endl;
            return;
        }
    }
    assert(false);
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
    cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}