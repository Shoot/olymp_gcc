#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("popcnt")
#define int long long
__int128 MOD = (1LL << 61) - 1;
int mul(int a, int b) {
    __int128 res = __int128(a) * b;
    int ret = (res&MOD) + (res>>61);
    if (ret >= MOD) {
        ret -= MOD;
    }
    return ret;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    auto powm = [&] (int a, int b) -> int {
        int ret = 1;
        while (b) {
            if (b&1) {
                ret = mul(ret, a);
            }
            a = mul(a, a);
            b >>= 1;
        }
        return ret;
    };
    for (int tt = 0; tt < T; tt += 1) {
        string s;
        cin >> s;
        int n = s.size();
        vector<int> cost(n+1, 1e9);
        vector<int> p(n+1, -1);
        vector<int> L(n+1, -1);
        cost[0] = 0;
        int base = 401;
        vector<int> basepow(n);
        vector<int> ibasepow(n);
        basepow[0] = 1;
        for (int i = 1; i < n; i += 1) {
            basepow[i] = mul(basepow[i-1], base);
        }
        ibasepow.back() = powm(basepow.back(), MOD-2);
        for (int i = n-2; i >= 0; i -= 1) {
            ibasepow[i] = mul(ibasepow[i+1], base);
        }
        vector<int> h(n);
        for (int i = 0; i < n; i += 1) {
            h[i] = mul(s[i], basepow[i]);
            if (i) {
                h[i] += h[i-1];
                if (h[i] >= MOD) {
                    h[i] -= MOD;
                }
            }
        }
        auto hash = [&] (int l, int r) -> int {
            int res = h[r];
            if (l) {
                res += MOD-h[l-1];
                if (res >= MOD) {
                    res -= MOD;
                }
            }
            res = mul(res, ibasepow[l]);
            return res;
        };
        // символ за 9
        // последовательность за 20

        // damn(2, 3): daMn -> damNm -> damnMn -> damnmNm
        // damn(3, 3): dAmn -> daMna -> damNam -> damnAmn
        unordered_map<int, int> starts;
        starts.reserve(n*n+10);
        for (int i = n-1; i >= 0; i -= 1) {
            for (int j = i; j < n; j += 1) {
                starts[hash(i, j)] = i;
            }
        }
        for (int i = 1; i <= n; i += 1) {
            p[i] = i-1;
            cost[i] = cost[i-1] + 9;
            for (int prev = i-1; prev >= 0; prev -= 1) {
                int start_pointer = starts[hash(prev, i-1)];
                if (start_pointer < prev) {
                    if (cost[i] > cost[prev] + 20) {
                        L[i] = prev - start_pointer;
                        cost[i] = cost[prev] + 20;
                        p[i] = prev;
                    }
                }
            }
        }
        int curr = n;
        vector<string> ans;
        while (curr) {
            if (cost[p[curr]]+9==cost[curr]) {
                ans.push_back(string(1, s[p[curr]]));
            } else {
                ans.push_back("("+to_string(L[curr])+","+to_string(curr-p[curr])+")");
            }
            curr = p[curr];
        }
        reverse(ans.begin(), ans.end());
        for (const auto &x : ans) {
            cout << x;
        }cout << "\n";
//        cout << cost[n] << "\n";
    }
}
