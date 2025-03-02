#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    vector<int> lp(1e7+1);
    for (int i = 2; i < lp.size(); i += 1) {
        if (lp[i] == 0) {
            lp[i] = i;
            for (int j = i*i; j < lp.size(); j += i) if (!lp[j]) {
                lp[j] = i;
            }
        }
    }
    vector<int> primes;
    primes.reserve(1000);
    auto get_primes = [&] (const int x) -> void {
        primes.clear();
        int last_lp = 0;
        int temp = x;
        while (temp != 1) {
            if (lp[temp] != last_lp) {
                last_lp = lp[temp];
                primes.push_back(last_lp);
            }
            temp /= lp[temp];
        }
    };
    vector<int> cnt(n+1);
    for (const auto &x : a) {
        get_primes(x);
        int sz = int(primes.size());
        for (int m = 1; m < (1LL << sz); m += 1) {
            int val = 1;
            for (int bt = 0; bt < sz; bt += 1) if (m&(1LL << bt)) {
                val *= primes[bt];
            }
            cnt[val] += 1;
        }
    }
    auto get_number_of_not_coprime_with_x = [&] (const int x) -> int {
        int tot = 0;
        get_primes(x);
        int sz = int(primes.size());
        for (int m = 1; m < (1LL << sz); m += 1) {
            int val = 1;
            for (int bt = 0; bt < sz; bt += 1) if (m&(1LL << bt)) {
                val *= primes[bt];
            }
            clog << val << ": " << cnt[val] * (__builtin_popcount(m)%2?1:-1) << "\n";
            tot += cnt[val] * (__builtin_popcount(m)%2?1:-1);
        }
        return tot;
    };
    cout << n-get_number_of_not_coprime_with_x(k) << "\n";
}
