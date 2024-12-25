#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b) {
    if (a%b==0) {
        return b;
    }
    return gcd(b,a%b);
}
long long x, z, k;
void solve() {
    x %= z, k %= z;
    long long O = 1, add = 0, g;
    while ((g = gcd(x, z)) > 1) {
        if (k == O) {
            cout << add << "\n";
            return;
        }
        if (k % g) {
            cout << "No Solution\n";
            return;
        }
        k /= g;
        z /= g;
        add += 1;
        O = (O * 1ll * x / g) % z;
    }

    long long sqrt_z = sqrt(z) + 1;
    long long x_pow_sqrt = 1;
    for (long long i = 0; i < sqrt_z; i += 1) {
        x_pow_sqrt = (x_pow_sqrt * 1ll * x) % z;
    }

    unordered_map<long long, long long> k_mult_by_x_pow;
    for (long long q = 0, cur = k; q <= sqrt_z; q += 1) {
        k_mult_by_x_pow[cur] = q;
        cur = (cur * 1ll * x) % z;
    }

    for (long long p = 1, cur = O; p <= sqrt_z; p += 1) {
        cur = (cur * x_pow_sqrt) % z;
        if (k_mult_by_x_pow.count(cur)) {
            long long ans = sqrt_z * p - k_mult_by_x_pow[cur] + add;
            cout << ans << "\n";
            return;
        }
    }
    cout << "No Solution\n";
    return;
}
int main() {
    while (true) {
        cin >> x >> z >> k;
        if (x == 0 && z == 0 && k == 0) {
            break;
        }
        solve();
    }
    return 0;
}