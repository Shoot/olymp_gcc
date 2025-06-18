#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
//constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T=1;
//    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n;
        cin >> n;
        vector<int> a(n+1), a2(n+1);
        for (int i = 1; i <= n; i += 1) {
            cin >> a[i];
            a2[i] = -a[i];
        }
        vector<int> r_gt(n+1, n+1);
        vector<int> st;
        for (int i = n; i >= 1; i -= 1) {
            while (!st.empty() && a[st.back()] <= a[i]) {
                st.pop_back();
            }
            if (!st.empty()) {
                r_gt[i] = st.back();
            }
            st.push_back(i);
        }
        vector<int> r_lt(n+1, n+1); // considering_only_values_after__r_gt
        st.clear();
        vector<vector<int>> qs(n+2);
        for (int i = n; i >= 1; i -= 1) {
            qs[r_gt[i]].push_back(i);
        }
        vector<int> st_vals;
        for (int i = n; i >= 1; i -= 1) {
            while (!st.empty() && a[st.back()] >= a[i]) {
                st.pop_back();
                st_vals.pop_back();
            }
            for (const auto &j : qs[i]) {
                int it = upper_bound(st_vals.begin(), st_vals.end(), a[j])-st_vals.begin()-1;
                if (it != -1) {
                    r_lt[j] = st[it];
                }
            }
            st.push_back(i);
            st_vals.push_back(a[i]);
        }
        vector<vector<int>> max_r_lt(20, vector<int>(n+1));
        vector<vector<int>> get_to(20, vector<int>(n+1));
        max_r_lt[0] = r_lt;
        get_to[0] = r_gt;
        for (int i = 1; i < 20; i += 1) {
            for (int j = 1; j <= n; j += 1) {
                get_to[i][j] = (get_to[i-1][j]==n+1)?(n+1):get_to[i-1][get_to[i-1][j]];
                max_r_lt[i][j]=(get_to[i-1][j]==n+1)?(n+1):max(max_r_lt[i-1][j], max_r_lt[i-1][get_to[i-1][j]]);
            }
        }
        int q;
        cin >> q;
        for (int ii = 0; ii < q; ii += 1) {
            int l, r;
            cin >> l >> r;
            for (int bt = 19; bt >= 0; bt -= 1) {
                if (max_r_lt[bt][l] <= r) {
                    l = get_to[bt][l];
                }
            }
            YES(max_r_lt[0][l] > r && get_to[0][l] <= r);
            cout << endl;
        }
    }
}