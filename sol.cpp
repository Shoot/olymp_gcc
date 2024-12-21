#include <bits/stdc++.h>
using namespace std;
int main () {
//    ios::sync_with_stdio(false);
//    cin.tie(0);
    int n, k;
    vector<int> A;
    vector<int> d_vals;
    vector<vector<int>> ans;
    auto is_d_more = [&] (int shift) -> bool {
        int i = 0;
        int j = shift;
        for (int k = 0; k < n; k += 1) {
            if (A[i+k>=n?i+k-n:i+k] > d_vals[j+k>=n?j+k-n:j+k]) {
                return false;
            }
            if (A[i+k>=n?i+k-n:i+k] < d_vals[j+k>=n?j+k-n:j+k]) {
                return true;
            }
        }
        return false;
    };
    auto make_minus = [&] (vector<int>& x) -> void {
        for (auto &y : x) {
            y = -y;
        }
    };
    auto undo_minus = [&] (vector<int>& x) -> void {
        make_minus(x);
    };
    auto is_father = [&] () -> bool {
        d_vals = A;
        for (int shift = 0; shift < n; shift += 1) { // (nothing)
            if (is_d_more(shift)) {
                return false;
            }
        }
        make_minus(d_vals);
        for (int shift = 0; shift < n; shift += 1) { // minus
            if (is_d_more(shift)) {
                return false;
            }
        }
        reverse(d_vals.begin(), d_vals.end());
        for (int shift = 0; shift < n; shift += 1) { // rev, minus
            if (is_d_more(shift)) {
                return false;
            }
        }
        undo_minus(d_vals);
        for (int shift = 0; shift < n; shift += 1) { // rev
            if (is_d_more(shift)) {
                return false;
            }
        }
        return true;
    };
    auto out = [&] () -> void {
        cout << ans.size() << "\n";
        for (const auto &x : ans) {
            cout << "(";
            for (int i = 0; i < int(x.size()); i += 1) {
                cout << x[i];
                if (i == int(x.size())-1) {
                    cout << ")";
                } else {
                    cout << ",";
                }
            }
            cout << "\n";
        }
    };
    auto dfs = [&] (auto f, int idx) -> void {
        if (idx == n) {
            if (accumulate(A.begin(), A.end(), 0) == 0 && is_father()) {
                ans.push_back({A});
            }
            return;
        }
        for (int nxt = -k; nxt <= k; nxt += 1) {
            A[idx] = nxt;
            f(f, idx+1);
        }
    };
    int tt = 0;
    while (cin >> n >> k) {
        if (++tt > 1) {
            cout << "\n";
        }
        A.resize(n);
        dfs(dfs, 0);
        out();
        ans.clear();
    }
}
