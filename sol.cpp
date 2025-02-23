#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = (1ll << 61) - 1;
ll mod(__int128 x) {
    ll ret = (x & MOD) + (x >> 61);
    if (ret >= MOD) {
        ret -= MOD;
    }
    assert(ret >= 0 && ret < MOD);
    return ret;
}
ll mul(ll a, ll b) {
    return mod(__int128(a)*b);
}
ll sum(ll a, ll b) {
    return mod(a+b);
}
ll powm(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b&1) {
            ans = mul(ans, a);
        }
        b >>= 1;
        a = mul(a, a);
    }
    return ans;
}
signed main() {
    const ll base = 31;
    const ll ibase = powm(base, MOD-2);
    string s;
    cin >> s;
    int n = int(s.size());
    s = s + s + s;
    auto is = s;
    reverse(is.begin(), is.end());
    vector<ll> hash(s.size());
    vector<ll> ihash(s.size());
    vector<ll> basepow(s.size());
    vector<ll> ibasepow(s.size());
    basepow[0] = 1;
    for (int i = 1; i < s.size(); i += 1) {
        basepow[i] = mul(basepow[i-1], base);
    }
    ibasepow[0] = 1;
    for (int i = 1; i < s.size(); i += 1) {
        ibasepow[i] = mul(ibasepow[i-1], ibase);
    }
    for (int i = 0; i < s.size(); i += 1) {
        hash[i] = mul(s[i]-'A'+1, basepow[i]);
        if (i) {
            hash[i] = sum(hash[i], hash[i-1]);
        }
    }
    for (int i = 0; i < s.size(); i += 1) {
        ihash[i] = mul(is[i]-'A'+1, basepow[i]);
        if (i) {
            ihash[i] = sum(ihash[i], ihash[i-1]);
        }
    }
    auto get = [&] (int l, int r) -> ll {
        if (!(l <= r)) {
            return 0ll;
        }
        ll temp = hash[r];
        if (l) {
            temp = sum(temp, mod(-hash[l-1]+MOD));
        }
        temp = mul(temp, ibasepow[l]);
        return temp;
    };
    auto iget = [&] (int l, int r) -> ll {
        int nwl = s.size()-r-1;
        int nwr = s.size()-l-1;
        l = nwl;
        r = nwr;
        if (!(l <= r)) {
            return 0ll;
        }
        ll temp = ihash[r];
        if (l) {
            temp = sum(temp, mod(-ihash[l-1]+MOD));
        }
        temp = mul(temp, ibasepow[l]);
        return temp;
    };
    int ans = 0;
    for (int i = n; i-n < n; i += 1) {
        int l = 0, r = n / 2 - (n % 2 == 0);
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (get(i-mid, i-1) == iget(i+1, i+mid)) {
                ans = max(ans, 1+2*mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    for (int i = n; i-n < n; i += 1) {
        int l = 1, r = n / 2;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (get(i-mid+1, i) == iget(i+1, i+mid)) {
                ans = max(ans, 2*mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    cout << ans << "\n";
}