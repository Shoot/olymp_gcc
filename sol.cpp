#include <bits/stdc++.h>
using namespace std;
#define int long long
#define placed_before max_pos_on_pref[i-1]
#define placed_after min_pos_on_pref[i-1]
constexpr int MOD = 1e9+7;
signed main() {
    int n;
    cin >> n;
    vector<int> pos(n);
    for (int i = 0; i < n; i += 1) {
        int x;
        cin >> x;
        pos[x] = i;
    }
    vector<int> fenw(1e6+10);
    auto set_place = [&] (int idx) -> void {
        for (idx = idx + 1; idx < fenw.size(); idx += idx & -idx) {
            fenw[idx] += 1;
        }
    };
    auto get_free_places = [&] (int idx) -> int {
        for (int idx_ = idx + 1, ones = 0; ; idx_ -= idx_ & -idx_) {
            if (idx_ == 0) {
                return idx+1-ones;
            }
            ones += fenw[idx_];
        }
    };
    vector<int> max_pos_on_pref(n, pos[0]), min_pos_on_pref(n, pos[0]);
    for (int i = 1; i < n; i += 1) {
        min_pos_on_pref[i] = min(pos[i], min_pos_on_pref[i-1]);
        max_pos_on_pref[i] = max(pos[i], max_pos_on_pref[i-1]);
    }
    int ans = 1;
    set_place(pos[0]);
    for (int i = 1; i < n; i += 1) {
        if (placed_before < pos[i] || placed_after > pos[i]) {
            set_place(pos[i]);
        } else {
            (ans *= get_free_places(placed_before)-get_free_places(placed_after-1)) %= MOD;
            set_place(pos[i]);
        }
    }
    cout << ans << "\n";
}