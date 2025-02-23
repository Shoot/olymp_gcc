#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = (1ll << 61) - 1;
ll mod(__int128 x) {
    if (x >= 0 && x < MOD) {
        return x;
    }
    if (x-MOD >= 0 && x-MOD < MOD) {
        return x-MOD;
    }
    ll ret = (x & MOD) + (x >> 61);
    if (ret >= MOD) {
        ret -= MOD;
    }
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
#include <bits/stdc++.h>
using namespace std;
vector<long long> manacher_odd(string &s) {
    long long n = (long long) s.size();
    vector<long long> d(n, 1);
    long long l = 0, r = 0;
    for (long long i = 1; i < n; i++) {
        if (i < r)
            d[i] = min(r - i + 1, d[l + r - i]);
        while (i - d[i] >= 0 && i + d[i] < n && s[i - d[i]] == s[i + d[i]])
            d[i]++;
        if (i + d[i] - 1 > r)
            l = i - d[i] + 1, r = i + d[i] - 1;
    }
    return d;
}
vector<long long> manacher_even(string &s) {
    long long n = (long long) s.size();
    vector<long long> d(n, 0);
    long long l = -1, r = -1;
    for (long long i = 0; i < n - 1; i++) {
        if (i < r)
            d[i] = min(r - i, d[l + r - i - 1]);
        while (i - d[i] >= 0 && i + d[i] + 1 < n && s[i - d[i]] == s[i + d[i] + 1])
            d[i]++;
        if (i + d[i] > r)
            l = i - d[i] + 1, r = i + d[i];
    }
    return d;
}
signed main() {
    const ll base = 31;
    const ll ibase = powm(base, MOD-2);
    string s;
    cin >> s;
    int n = int(s.size());
    s = string(s.end()-n/2, s.end()) + s + string(s.begin(), s.begin()+n/2);
    auto d1 = manacher_odd(s);
    auto d2 = manacher_even(s);
    int maxi = 0;
    for (long long i = 0; i < s.size(); i += 1) {
        int chet = d2[i]*2;
        int nechet = d1[i]*2-1;
        if (nechet > n) {
            maxi = max(maxi, n - (n % 2 == 0));
        } else {
            maxi = max(maxi, nechet);
        }
        if (chet > n) {
            maxi = max(maxi, n - (n % 2 == 1));
        } else {
            maxi = max(maxi, chet);
        }
    }
    cout << maxi << endl;
}