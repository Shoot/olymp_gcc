#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MOD = 1e9+7;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    int n_ = n;
    while (n&(n-1)) {
        a.push_back(0);
        n += 1;
    }
    vector<vector<pair<int,int>>> val_and_cnt(20, vector<pair<int,int>>(n));
    auto go = [&] (auto f, int l, int r, int layer) -> void {
        if (layer < 0) {
            return;
        }
        int pos = l + (1 << layer) - 1;
        auto curr = pair<int,int>{-1, 0};
        for (int i = pos; i >= l; i -= 1) {
            if (a[i] > curr.first) {
                curr.first = a[i];
                curr.second = 1;
            } else {
                curr.second += a[i] == curr.first;
            }
            val_and_cnt[layer][i] = curr;
        }
        curr = pair<int,int>{-1, 0};
        for (int i = pos+1; i <= r; i += 1) {
            if (a[i] > curr.first) {
                curr.first = a[i];
                curr.second = 1;
            } else {
                curr.second += a[i] == curr.first;
            }
            val_and_cnt[layer][i] = curr;
        }
        f(f, l, pos, layer-1);
        f(f, pos+1, r, layer-1);
    };
    go(go, 0, n-1, 31-__builtin_clz(n)-1);
//    for (const auto &x : val_and_cnt) {
//        for (const auto &y : x) {
//            cout << y.first << "," << y.second << " ";
//        }cout << "\n";
//    }
    int q, x, y, z, t;
    cin >> q >> x >> y >> z >> t;
    int last = 0;
    int tot = 1;
    for (int ii = 0; ii < q; ii += 1) {
        int l = (last*x+y)%n_;
        int r = (last*z+t)%n_;
        if (l > r) {
            swap(l, r);
        }
        if (l == r) {
            last = 1;
        } else {
            int bt = 31-__builtin_clz(l^r);
            auto one = val_and_cnt[bt][l];
            auto another = val_and_cnt[bt][r];
            if (one.first < another.first) {
                swap(one, another);
            }
            if (one.first == another.first) {
                last = one.second + another.second;
            } else {
                last = one.second;
            }
        }
        (tot *= last) %= MOD;
    }cout << tot << "\n";
}
//1 2 2 2 | 1 2 1