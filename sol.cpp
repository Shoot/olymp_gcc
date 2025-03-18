#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> lp(2e5+1);
    for (long long i = 2; i < lp.size(); i += 1) {
        if (lp[i] == 0) {
            lp[i] = i;
            for (long long j = i*i; j < lp.size(); j += i) {
                if (!lp[j]) {
                    lp[j] = i;
                }
            }
        }
    }
    vector<vector<int>> shit(2e5+1);
    for (int i = 1; i <= 2e5; i += 1) {
        int last_lp = 0;
        int temp = i;
        while (temp != 1) {
            if (lp[temp] != last_lp) {
                last_lp = lp[temp];
                shit[i].push_back(last_lp);
            }
            temp /= lp[temp];
        }
    }
    vector<int> last_mul_of(2e5+1, -1);
    vector<int> not_coprime_to_L(n, -1);
    for (int i = 0; i < n; i += 1) {
        for (const auto &x : shit[a[i]]) {
            not_coprime_to_L[i] = max(not_coprime_to_L[i], last_mul_of[x]);
            last_mul_of[x] = i;
        }
    }
    last_mul_of.assign(2e5+1, n);
    vector<int> not_coprime_to_R(n, n);
    for (int i = n-1; i >= 0; i -= 1) {
        for (const auto &x : shit[a[i]]) {
            not_coprime_to_R[i] = min(not_coprime_to_R[i], last_mul_of[x]);
            last_mul_of[x] = i;
        }
    }
    map<int,vector<pair<int,int>>> by_r;
    for (int i = 0; i < n; i += 1) {
        by_r[not_coprime_to_R[i]].push_back({not_coprime_to_L[i], i});
    }
    struct Query {
        int l;
        int r;
        int idx;
    };
    vector<vector<Query>> Q_by_r(n+1);
    vector<Query> Q;
    for (int ii = 0; ii < q; ii += 1) {
        int l, r;
        cin >> l >> r;
        l -= 1;
        r -= 1;
        Q_by_r[r].push_back({l,r,ii});
//        int ans = 0;
//        for (int i = l; i <= r; i += 1) {
//            ans += not_coprime_to_L[i] < l && not_coprime_to_R[i] > r;
//        }
//        cout << ans << "\n";
    }
    vector<int> ans(q);
    vector<int> fenw(n+10);
    auto inc = [&] (int idx, int val) -> void {
        for (; idx < fenw.size(); idx += idx & -idx) {
            fenw[idx] += val;
        }
    };
    auto gt = [&] (int idx) -> int {
        int ret = 0;
        for (; idx; idx -= idx & -idx) {
            ret += fenw[idx];
        }
        return ret;
    };
    for (int ii = 0; ii <= n; ii += 1) {
        if (ii < n) {
            inc((not_coprime_to_L[ii]+1)+2, 1);
            inc((ii+1)+2, -1);
        }
        for (const auto &[Li, i] : by_r[ii]) {
            inc((Li+1)+2, -1);
            inc((i+1)+2, 1);
        }
        for (const auto &[l, r, idx] : Q_by_r[ii]) {
            ans[idx] = gt(l+2);
        }
    }
    for (const auto &x : ans) {
        cout << x << "\n";
    }
}