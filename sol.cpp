#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
    cin >> T;
    vector<int> div(1'000'001);
    for (int i = 2; i < div.size(); i += 1) {
        if (!div[i]) {
            div[i] = i;
            for (int j = i*i; j < div.size(); j += i) {
                if (!div[j]) {
                    div[j] = i;
                }
            }
        }
    }
    bitset<1'000'001> prime;
    for (int i = 2; i < prime.size(); i += 1) {
        if (i/div[i] == 1) {
            prime[i] = true;
        }
    }
    bitset<1'000'001> good;
    for (int i = 2; i < good.size(); i += 1) {
        if (!prime[i] && prime[i/div[i]]) {
            good[i] = true;
        }
    }
    for (int tt = 0; tt < T; tt += 1) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) {
            cin >> x;
        }
        sort(a.begin(), a.end());
        int ans = 0;
        int cnt_prime = 0;
        vector<int> cnt(n+1), cnt_div_by_i(n+1);
        vector<int> primes;
        primes.reserve(1000);
        auto get_primes = [&] (const int x) -> void {
            primes.clear();
            int last_lp = 0;
            int temp = x;
            while (temp != 1) {
                if (div[temp] != last_lp) {
                    last_lp = div[temp];
                    primes.push_back(last_lp);
                }
                temp /= div[temp];
            }
        };
        int sz = 0;
        for (int i = 0; i < n; i += 1) {
            cnt_prime += prime[a[i]];
            cnt[a[i]] += 1;
            get_primes(a[i]);
            if (i && a[i-1] != a[i]) {
                for (int j = a[i-1]; j <= n; j += a[i-1]) {
                    cnt_div_by_i[j] += sz;
                }
                sz = 1;
            } else {
                sz += 1;
            }
            if (prime[a[i]]) {
                ans += cnt_prime - cnt[a[i]];
            } else if (good[a[i]]) {
                ans += cnt[a[i]];
                ans += cnt_div_by_i[a[i]];
            }
        }
        cout << ans << "\n";
    }
}