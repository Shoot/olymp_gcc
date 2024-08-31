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
uniform_int_distribution<ll> distrib(1, 10);
constexpr ll N = (ll)(2005);
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
ll n;
vector<ll> findLISIndices(const ll arr[]) {
    vector<ll> dp;
    vector<ll> parent(n, -1);
    vector<ll> lisIndices;

    for (ll i = 0; i < n; ++i) {
        auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
        ll pos = it - dp.begin();
        if (it == dp.end()) {
            dp.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
        if (pos > 0) {
            parent[i] = lisIndices[pos - 1];
        }
        if (pos == lisIndices.size()) {
            lisIndices.push_back(i);
        } else {
            lisIndices[pos] = i;
        }
    }
    vector<ll> result;
    ll k = lisIndices.back();
    for (ll i = (ll)dp.size() - 1; i >= 0; --i) {
        result.push_back(k);
        k = parent[k];
    }
    reverse(result.begin(), result.end());
    return result;
}
void computeLIS(ll arr[], ll output[]) {
    vector<ll> lis;
    for (ll i = 0; i < n; ++i) {
        auto it = lower_bound(lis.begin(), lis.end(), arr[i]);
        if (it == lis.end()) {
            lis.push_back(arr[i]);
            output[i] = lis.size();
        } else {
            *it = arr[i];
            output[i] = it-lis.begin()+1;
        }
    }
}
struct shit {
    ll ind, znach, lis;
};
void solve () {
//    cin >> n;
    n = 10;
    ll a[n];
    clog << "new: ";
    fo(i, 0, n) {
        a[i] = distrib(rng);
//        cin >> a[i];
        clog << a[i] << ' ';
    }
    clog << endl;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    ll pref[n];
    ll suffrev[n];
    ll suff[n];
    ll rev[n];
    fo(i, 0, n) {
        rev[i] = -a[n-1-i];
    }
    computeLIS(a, pref);
    computeLIS(rev, suffrev);
    fo(i, 0, n) {
        suff[i] = suffrev[n-1-i];
    }
    fo(i, 0, n) {
        clog << pref[i] << ' ';
    }
    clog << endl;
    fo(i, 0, n) {
        clog << suff[i] << ' ';
    }
    clog << endl;

    ll maxi = 0;
    fo(i, 0, n) {
        fo(j, i+2, min(n, i+100)) {
            if (a[j]-a[i] > 1) {
                maxi = max(maxi, pref[i]+suff[j]+1);
            }
        }
    }
//    cout << maxi << endl;
    ll prev = -1;
    ll prevprev = -1;
    bool good = false;
    vector<ll> inds = findLISIndices(a);
    if (inds[0] != 0) good = true;
    ll ind = 0;
    for (ll j: inds) {
        ind += 1;
        clog << j << endl;
        if (prevprev == -1 && prev != -1 && prev != j-1) {
            forr(mezhdu0, prev+1, j-1) {
                if (a[mezhdu0] < a[j]) {
                    clog << "mezhdu prev i j: " << mezhdu0 << endl;
                    good = true;
                    break;
                }
            }
            if (good) break;
        }
        if (prev != -1 && prevprev != -1 && prevprev != prev-1) {
            forr(mezhdu, prevprev+1, prev-1) {
                if (a[mezhdu] > a[prevprev] && a[mezhdu] < a[j] && a[mezhdu] < a[prev]) {
                    clog << "mezhdu prevprev i prev: " << mezhdu << endl;
                    good = true;
                    break;
                }
            }
            if (good) break;
        }
        if (prev != -1 && a[prev] != a[j]-1 && prev-prevprev>1 && a[prevprev] !=a[prev]-1) {
            clog << a[prev] << "!!!" << a[j] << endl;
            good = true;
            break;
        }
        if (prevprev != -1 && prev != -1 && a[prevprev] !=a[prev]-1 && prevprev!=prev-1 && prev != j-1) {
            clog << a[prevprev] << "!!!!" << a[prev] << endl;
            good = true;
            break;
        }
        if (prevprev != -1 && a[prevprev] != a[prev]-1 && prevprev != prev-1) {
            clog << a[prevprev] << "!!" << a[prev] << endl;
            good = true;
            break;
        }
        if (prev > 0 && a[prev-1] == a[prev] && a[j]-a[prev] > 1) {
            good = true;
            break;
        }
        if (j - prev > 1 && prev != -1 && a[j] != a[prev]+1) {
            good = true;
            break;
        }
        if (ind >= 2) prevprev = prev;
        prev = j;
    }
    if (prev != n-1) good = true;
    fo(i, 0, n-1) {
        if (pref[i] == (ll)inds.size()) {
            good = true;
            break;
        }
    }
    maxi = max(maxi, (ll)inds.size()+good);
    clog << "THE SIZE: " << inds.size() << endl;
    if (inds.size() == n) {
        maxi = n;
    }
    fo(i, 0, n-2) {
        if (a[i+2]-a[i]>1) {
            if (pref[i]+suff[i+2]+1 > maxi) {
                clog << i << ":)" << endl;
                maxi = pref[i]+suff[i+2]+1;
            }
        }
    }
    clog << "maxi: " << maxi << endl;
//    cout << maxi << endl;
    ll ogmaxi = 0;
    fo(i, 0, n) {
        ll og = a[i];
        forr(shit, -11, 11) {
            a[i] = shit;
            ogmaxi = max(ogmaxi, (ll)findLISIndices(a).size());
            if (ogmaxi > maxi) {
                clog << "ogmaxi (better): " << ogmaxi << " :::: ";
                fo(iii, 0, n) {
                    clog << a[iii] << ' ';
                }
                clog << endl;
                assert(false);
            }
        }
        a[i] = og;
    }
    clog << "ogmaxi: " << ogmaxi << endl;
    assert(ogmaxi == maxi);
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
        clog.tie(nullptr);
    }
//    ll tt = 1;
    ll tt = 100000;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}