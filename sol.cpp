#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int T;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, s, k;
        cin >> n >> s >> k;
        int tot = n * (n + 1) / 2;
        auto get = [&] (int cnt) -> int {
            return cnt*k+(cnt+s-tot*cnt)*(cnt+s-tot*cnt)+(n-1)*cnt*cnt;
        };
        int maxi = -1;
        int cnt = 0;
        int l = 0, r = s/tot;
        int good = -1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (get(mid) < get(mid+1)) {
                l = mid+1;
            } else {
                r = mid;
            }
        }
        clog << l << r << "\n";
        cout << get(l) << "\n";
    }
}