#include <bits/stdc++.h>
using namespace std;
long long N = 3e5+1;
__int128 MOD = (1LL << 61) - 1;
long long mul(long long a, long long b) {
    __int128 val = __int128(a) * b;
    val = (val >> 61) + (val & MOD);
    if (val >= MOD) {
        val -= MOD;
    }
    return val;
}
signed main() {
    long long n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<long long> number_of_multiples(N);
    for (const auto &x : a) {
        number_of_multiples[x] += 1;
    }
    for (long long i = 1; i < N; i += 1) {
        for (long long j = 2*i; j < N; j += i) {
            number_of_multiples[i] += number_of_multiples[j];
        }
    }
    vector<long long> fact(N);
    fact[0] = 1;
    for (long long i = 1; i < N; i += 1) {
        fact[i] = mul(fact[i-1], i);
    }
    vector<long long> ifact(N);
    auto powm = [&] (long long a, long long b) -> long long {
        long long ans = 1;
        while (b) {
            if (b&1) {
                ans = mul(ans, a);
            }
            b >>= 1;
            a = mul(a, a);
        }
        return ans;
    };
    ifact.back() = powm(fact.back(), MOD-2);
    for (long long i = N-2; i >= 0; i -= 1) {
        ifact[i] = mul(ifact[i+1], i+1);
    }
    auto C = [&] (long long n, long long k) -> long long {
        if (k > n) {
            return 0;
        }
        return mul(mul(fact[n], ifact[n-k]), ifact[k]);
    };
    vector<vector<long long>> dp(24, vector<long long>(N));
    for (long long sz = 1; sz <= 23; sz += 1) {
        for (long long gcd = N-1; gcd >= 1; gcd -= 1) {
            dp[sz][gcd] = C(number_of_multiples[gcd], sz);
            for (long long j = 2 * gcd; j < N; j += gcd) {
                ((dp[sz][gcd] -= dp[sz][j]) += MOD) %= MOD;
            }
        }
        if (dp[sz][1]) {
            cout << sz << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
}
