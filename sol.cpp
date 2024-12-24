#include <bits/stdc++.h>
using namespace std;
int main() {
    cout << fixed << setprecision(10);
    long long d, tot, cap;
    cin >> d >> tot >> cap;
    double can_get = 0;
    double last_part = tot % cap;
    for (int k = 1; ;k += 1) {
        if (k == tot / cap + 1) {
            can_get += last_part / (2 * k - 1);
            break;
        } else {
            can_get += double(cap) / (2 * k - 1);
        }
    }
    if (can_get < d) {
        cout << 0 << "\n";
    } else {
        double ans = can_get - d;
        cout << ans << "\n";
    }
    return 0;
}