#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <cassert>
#include <set>
using namespace std;
signed main() {
    map<pair<long long,long long>, long long> mem;
    auto number_by_len_and_su = [&] (auto f, long long len, long long su) -> long long {
        if (mem.count({len, su})) {
            return mem[{len, su}];
        }
        if (len == 0) {
            if (su == 0) {
                return mem[{len, su}] = 1;
            }
            return mem[{len, su}] = 0;
        }
        long long ret = 0;
        for (long long rem = 0; rem <= su; rem += 1) {
            ret += f(f, len-1, su-rem);
        }
        return mem[{len, su}] = ret;
    };
    auto get = [&] (long long len, long long su, long long order) -> vector<long long> {
        vector<long long> ret;
        order -= 1;
        for (long long i = 0; i < len; i += 1) {
            long long curr = su;
            su -= curr;
            while (curr) {
                long long cnt = number_by_len_and_su(number_by_len_and_su, len-i-1, su);
                if (order >= cnt) {
                    curr -= 1;
                    su += 1;
                    order -= cnt;
                } else {
                    break;
                }
            }
            ret.push_back(curr);
        }
        return ret;
    };
    long long tp;
    cin >> tp;
    if (tp == 0) {
        long long len, su, order;
        cin >> len >> su >> order;
        for (const auto &x : get(len, su, order)) {
            cout << x << " ";
        }cout << "\n";
    } else {
        long long sz;
        cin >> sz;
        vector<long long> our(sz);
        long long su = 0;
        for (auto &x : our) {
            cin >> x;
            su += x;
        }
        long long l = 1, r = 1e18;
        long long good = -1;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (get(sz, su, mid) > our) {
                l = mid + 1;
            } else {
                good = mid;
                r = mid - 1;
            }
        }
        cout << good << "\n";
    }
}