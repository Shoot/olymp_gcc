#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b) {
    if (a%b==0) {
        return b;
    }
    return gcd(b,a%b);
}
long long x, z, k;
void solve2() {
    long long a = x;
    long long m = z;
    long long b = k;
    long long K = 1;
    long long C = sqrt(m);
    long long a_pow_sqrt = 1;
    for (long long i = 0; i < C; i += 1) {
        a_pow_sqrt = (a_pow_sqrt * a) % m;
    }
    unordered_map<long long, long long> mp;
    long long curr = 1;
    for (long long i = 0; i <= C; i += 1) {
        mp[curr] = i;
        curr = (curr * a_pow_sqrt) % m;
    }
    curr = b;
    for (long long j = 0; j < C; j += 1) {
        cout << "j = " << j << endl;
        if (mp.count(curr)) {
            cout << mp[curr]*C-j << endl;
        }
        curr = (curr * a) % m;
    }
}
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
        O /= g;
        z /= g;
        add += 1;
        O = (O * x / g) % z;
    }

    long long sqrt_z = sqrt(z) + 1;
    long long x_pow_sqrt = 1;
    for (long long i = 0; i < sqrt_z; i += 1) {
        x_pow_sqrt = (x_pow_sqrt * x) % z;
    }

    unordered_map<long long, long long> k_mult_by_x_pow;
    for (long long q = 0, cur = k; q <= sqrt_z; q += 1) {
        k_mult_by_x_pow[cur] = q;
        cur = (cur * x) % z;
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
        solve2();
    }
    return 0;
}