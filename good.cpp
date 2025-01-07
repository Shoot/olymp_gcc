#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    struct Bowl {
        double h;
        double r;
        double R;
    };
    auto oper = [&] (const Bowl &up, const Bowl &down) -> double {
        if (up.R <= down.r) {
            return 0.;
        }
        if (up.r >= down.R) {
            return down.h;
        }
        double ans = 0.;
        if (up.r > down.r) {
            ans = max(ans, double((up.r-down.r) * down.h) / (down.R-down.r));
        }
        if (up.R < down.R) {
            ans = max(ans, double((up.R-down.r) * down.h) / (down.R-down.r) - up.h);
        } else {
            ans = max(ans, double(down.h) - double((down.R-up.r) * up.h / (up.R-up.r)));
        }
        return ans;
    };
    for (int tt = 0; tt < T; tt += 1) {
        int n;
        cin >> n;
        vector<Bowl> bowls(n);
        for (auto &[h, r, R] : bowls) {
            cin >> h >> r >> R;
        }
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        double ans = 1e18;
        do {
            vector<double> where(n);
            for (int i = 0; i < n; i += 1) {
                for (int o = 0; o < i; o += 1) {
                    where[i] = max(where[i], oper(bowls[order[i]], bowls[order[o]]) + where[o]);
                }
            }
            double this_perm_ans = 0;
            for (int i = 0; i < n; i += 1) {
                this_perm_ans = max(this_perm_ans, where[i] + bowls[order[i]].h);
            }
            ans = min(ans, this_perm_ans);
        } while (next_permutation(order.begin(), order.end()));
        cout << trunc(ans) << "\n";
    }
}