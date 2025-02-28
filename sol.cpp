#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;
signed main() {
    long long n, k;
    map<pair<long long,long long>,long long> mem;
    auto C = [&] (auto f, long long n, long long k) -> long long {
        if (mem.count({n, k})) {
            return mem[{n, k}];
        }
        if (k == 0) {
            return mem[{n, k}] = 1;
        }
        if (n == 0) {
            return mem[{n, k}] = 0;
        }
        return mem[{n, k}] = f(f, n-1, k)+f(f, n-1, k-1);
    };
    cin >> n >> k;
    vector<long long> a(k);
    for (auto &x : a) {
        cin >> x;
    }
    auto gen = [&] (long long order) -> vector<long long> {
        vector<long long> ret(k);
        order -= 1;
        long long curr = 1;
        for (long long i = 0; i < k; i += 1) {
            while (curr != n-(k-i-1) && order >= C(C, n-curr, k-i-1)) {
                order -= C(C, n-curr, k-i-1);
                curr += 1;
            }
            ret[i] = curr;
            curr = curr + 1;
        }
        return ret;
    };
    long long good = -1;
    long long l = 1, r = C(C, n, k);
    while (l <= r) {
        long long mid = (l + r) >> 1;
        auto g = gen(mid);
        if (g <= a) {
            good = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (good == C(C, n, k)) {
        cout << 0 << "\n";
        return 0;
    }
    for (const auto &x : gen(good+1)) {
        cout << x << " ";
    }cout << "\n";
}