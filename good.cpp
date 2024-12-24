#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b)
{
    if (a%b==0) return b;
    else return gcd(b,a%b);
}
void solve(long long a, long long b, long long m) {
    a %= m, b %= m;
    long long k = 1, add = 0, g;
    while ((g = gcd(a, m)) > 1) {
        if (b == k) {
            cout << add << "\n";
            return;
        }
        if (b % g) {
            cout << "No Solution\n";
            return;
        }
        b /= g, m /= g, add += 1;
        k = (k * 1ll * a / g) % m;
    }

    long long n = sqrt(m) + 1;
    long long an = 1;
    for (long long i = 0; i < n; i += 1)
        an = (an * 1ll * a) % m;

    unordered_map<long long, long long> vals;
    for (long long q = 0, cur = b; q <= n; q += 1) {
        vals[cur] = q;
        cur = (cur * 1ll * a) % m;
    }

    for (long long p = 1, cur = k; p <= n; p += 1) {
        cur = (cur * 1ll * an) % m;
        if (vals.count(cur)) {
            long long ans = n * p - vals[cur] + add;
            cout << ans << "\n";
            return;
        }
    }
    cout << "No Solution\n";
    return;
}
int32_t main() {
    while (true) {
        long long a, m, b;
        cin >> a >> m >> b;
        if (a == 0 && m == 0 && b == 0) {
            break;
        }
        solve(a, b, m);
    }
    return 0;
}