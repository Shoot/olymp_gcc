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
uniform_int_distribution<ll> distrib(100, 900);
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
ll cnt=0;
//set<ll> skip;
ll skip = distrib(rng);
ll previ;
ll ask(ll _1, ll _2, ll _3, ll _4) {
    if (_3 == skip) return previ;
    assert(cnt != 2007);
    if (_1 == 1 && _2 == 1 && _3 == n && _4 == n) {
        return 0;
    }
    cout << "? " << _1 << " " << _2 << " " << _3 << " " << _4 << endl;
    cout.flush();
    ll x;
    cin >> x;
    assert(x != -1);
    cnt += 1;
    previ = x;
    return x;
}
void solve() {
    cin >> n;
    ll sni[n+1];
    memset(sni, 0, sizeof(sni));
    ll spr[n+1];
    memset(spr, 0, sizeof(spr));
    ll spr_nech = 0;
    ll sni_nech = 0;
    forr(i, 1, n) {
        spr[i] = ask(1, 1, i, n);
        if (spr[i] % 2 == 1) {
            spr_nech = i;
            break;
        }
    }
    ll spr_ch = 0;
    if (spr_nech != 0) {
        forr(i, spr_nech+1, n) {
            spr[i] = ask(1, 1, i, n);
            if (spr[i] % 2 == 0) {
                spr_ch = i;
                break;
            }
            if (spr[i] == 0) break;
        }
    }
    forr(i, 1, n) {
        sni[i] = ask(1, 1, n, i);
        if (sni[i] % 2 == 1) {
            sni_nech = i;
            break;
        }
    }
    ll sni_ch = 0;
    if (sni_nech != 0)
        forr(i, sni_nech+1, n) {
            sni[i] = ask(1, 1, n, i);
            if (sni[i] % 2 == 0) {
                sni_ch = i;
                break;
            }
            if (sni[i] == 0) break;
        }
    if (spr_nech > 0 && sni_nech > 0 && ask(spr_nech, sni_ch, spr_nech, sni_ch) == 1) {
        swap(sni_nech, sni_ch);
    }
    if (spr_nech == 0 && sni_nech == 0) {
        cout << "! " << 1 << " " << 1 << " " << 2 << " " << 2 << endl;
        cout.flush();
        return;
    }
    if (spr_nech == 0) {
        // на одной горизонтальной линии
        ll l=1, r=n;
        ll good = -1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ll x = ask(1, sni_nech, mid, sni_nech);
            if (x%2==1) {
                good = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        spr_nech = spr_ch = good;
    }
    if (sni_nech == 0) {
        // на одной вертикальной линии
        ll l=1, r=n;
        ll good = -1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ll x = ask(spr_nech, 1, spr_nech, mid);
            if (x%2==1) {
                good = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        sni_nech = sni_ch = good;
    }
    cout << "! " << spr_nech << " " << sni_nech << " " << spr_ch << " " << sni_ch << endl;
    cout.flush();
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
    ll tt = 1;
//    fo(i, 0, 1) skip.insert(distrib(rng));
//    cin >> tt;
    while (tt--) solve();
    return 0;
}