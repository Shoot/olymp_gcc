#include <iostream>
#include <vector>
#include <map>
using namespace std;
signed main() {
    map<pair<long long, long long>, long long> dp;
    auto do_dp = [&] (auto f, long long sz, long long first) -> long long {
        if (sz == 1) {
            return 1;
        }
        if (dp.count({sz, first})) {
            return dp[{sz, first}];
        }
        long long ans = 0;
        for (long long nxt = first; nxt <= 9; nxt += 1) {
            ans += f(f, sz - 1, nxt);
        }
        return dp[{sz, first}] = ans;
    };
    long long n;
    cin >> n;
    long long sz = 1;
    while (do_dp(do_dp, sz + 1, 0) <= n) {
        sz += 1;
    }
    long long nxt = 0;
    long long alr_more_than = 0;
    vector<long long> res;
    for (; sz >= 1; sz -= 1) {
        for (; nxt <= 9; nxt += 1) {
            if (alr_more_than + do_dp(do_dp, sz, nxt) > n) {
                break;
            }
            alr_more_than += do_dp(do_dp, sz, nxt);
        }
        res.push_back(nxt);
    }
    for (const auto &x : res) {
        cout << x;
    }cout << "\n";
}