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
ll maxi_init = 1e9;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
struct shit {
    ll chet, nechet;
};
void solve() {
    ll k; cin >> k;
    ll max_length = 0;
    vector<pair<ll, ll>> DELETE;
    vector<pair<vector<shit>, vector<shit>>> G (k);
    fo(ii, 0, k) {
        ll n, m; cin >> n >> m;
        G[ii].first.resize(n);
        G[ii].second.resize(n);
        vector<pair<ll, ll>> a (n+1);
        forr(i, 0, n) {
            a[i].first = maxi_init;
            a[i].second = maxi_init;
        }
        vector<vector<ll>> sm(n+1);
        fo(i, 0, m) {
            ll u, v; cin >> u >> v;
            sm[u].push_back(v);
            sm[v].push_back(u);
        }
        queue<pair<ll, ll>> q;
        q.push(make_pair(1, 0));
        while(!q.empty()) {
            auto tp = q.front();
//            clog << "got " << tp.first << " " << tp.second << endl;
            q.pop();
            if (tp.second % 2 == 0 && a[tp.first].first == maxi_init) {
                a[tp.first].first = tp.second;
//                clog << "setting " << tp.first << "[0]=" << tp.second << endl;
            } else if (tp.second % 2 == 1 && a[tp.first].second == maxi_init) {
                a[tp.first].second = tp.second;
//                clog << "setting " << tp.first << "[1]=" << tp.second << endl;
            } else {
                continue;
            }
            for (ll nxt: sm[tp.first]) {
                q.push(make_pair(nxt, tp.second+1));
            }
        }
        clog << "G_" << ii << " start" << endl;
        forr(i, 1, n) {
            G[ii].first[i-1] = shit(a[i].first, a[i].second);
            G[ii].second[i-1] = shit(a[i].first, a[i].second);
            max_length = max({max_length, a[i].first, a[i].second});
            clog << a[i].first << " " << a[i].second << endl;
        }
        clog << endl;
        if (DELETE.empty()) {
            forr(i, 1, n) {
                DELETE.push_back(a[i]);
            }
        } else {
            vector<pair<ll, ll>> DELETE2;
            for(auto [i, j]: DELETE) {
                forr(iii, 1, n) {
                    DELETE2.push_back(make_pair(max(i, a[iii].first), max(j, a[iii].second)));
                }
            }
            DELETE = DELETE2;
        }
    }
    fo(ii, 0, k) {
        sort(all(G[ii].first), [](shit a, shit b) {
            return a.chet < b.chet;
        });
        sort(all(G[ii].second), [](shit a, shit b) {
            return a.nechet < b.nechet;
        });
    }
    ll OG = 0;
    map<ll, ll> ls;
    for(auto [i, j]: DELETE) {
        ll l = min(i, j);
        if (l != maxi_init) {
            ls[l] += 1;
            OG += l;
        }
    }
    for(auto [i, j] : ls) {
        clog << "l=" << i << ", count = " << j << endl;
    }
    cout << "OG = " << OG << endl;
    forr(x, 1, max_length) {
        if (x%2==1) {
            continue;
        } else {
            vector<ll> both(k, 0);
            vector<ll> first_cond(k, 0);
            vector<ll> second_cond(k, 0);
            vector<ll> good_length(k, 0);
            fo(ii, 0, k) {
                ll l=0, r=G[ii].first.size()-1;
                while (l <= r) {
                    ll mid = (l+r) >> 1;
                    if (G[ii].first[mid].chet <= x) {
                        good_length[ii] = mid+1;
                        l = mid+1;
                    } else {
                        r = mid-1;
                    }
                }
                clog << "good_length = " << good_length[ii] << endl;
                fo(ji, 0, good_length[ii]) {
                    if (G[ii].first[ji].nechet <= x) {
                        second_cond[ii] += 1;
                        clog << "second_cond ++" << endl;
                    }
                }
                fo(ji, 0, good_length[ii]) {
                    if (G[ii].first[ji].chet != x && G[ii].first[ji].nechet <= x) {
                        both[ii] += 1;
                    }
                }
                l=0; r=good_length[ii]-1;
                ll posl_vh = good_length[ii];
                while (l <= r) {
                    ll mid = (l+r) >> 1;
                    if (G[ii].first[mid].chet > x) {
                        posl_vh = mid;
                        r = mid-1;
                    } else {
                        l = mid+1;
                    }
                }
                l=0; r=good_length[ii]-1;
                ll perv_vh = -1;
                while (l <= r) {
                    ll mid = (l+r) >> 1;
                    if (G[ii].first[mid].chet < x) {
                        perv_vh = mid;
                        l = mid+1;
                    } else {
                        r = mid-1;
                    }
                }
//                assert(posl_vh != -1);
//                assert(perv_vh != -1);
//                assert(less_or_eq != -1);
                first_cond[ii] = good_length[ii]-(posl_vh-perv_vh-1);
                clog << "G_" << ii << ": first_cond = " << first_cond[ii] << endl;
                clog << "G_" << ii << ": second_cond = " << second_cond[ii] << endl;
                clog << "G_" << ii << ": both_conds = " << both[ii] << endl;
            }
            ll ALL = 1;
            ll FIRST_COND_NOT_MET = 1;
            ll SECOND_COND_NOT_MET = 1;
            ll BOTH_CONDs_NOT_MET = 1;
            fo(ii, 0, k) {
                ALL *= good_length[ii];
                FIRST_COND_NOT_MET *= first_cond[ii];
                SECOND_COND_NOT_MET *= second_cond[ii];
                BOTH_CONDs_NOT_MET *= both[ii];
            }
            clog << "length = " << x << ": count = " << ALL - FIRST_COND_NOT_MET - SECOND_COND_NOT_MET + BOTH_CONDs_NOT_MET << endl;
        }
    }
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