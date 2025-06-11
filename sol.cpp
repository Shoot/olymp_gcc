#include <bits/stdc++.h>
using namespace std;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int p, s;
        cin >> p >> s;
        int g = __gcd(p, s);
        p /= g, s /= g;
        if (p%2) {
            p *= 2, s *= 2;
        }
        bool done = false;
        for (int S = s, P = p; S <= (int)5e4; S += s, P += p) {
            // make rectangle with "eaten" part (not hole), p=const
            int side1 = P/2/2, side2 = P/2/2+(P/2)%2;
            // sides equal as possible for gt area variabiliy
            if (S >= side1+side2-1 /* eaten as possible, looks like a 90deg corner */
            && S <= side1*side2 /* not eaten at all */) {
                /* start constructing from "90deg corner" to "not eaten at all" */
                done = true;
                cout << S << "\n";
                for (int i = 0; i < side1; i += 1, S -= 1) {
                    cout << i << " " << 0 << "\n";
                }
                for (int i = 0; i < side1; i += 1) {
                    for (int j = 1; j < side2 && S; j += 1, S -= 1) {
                        cout << i << " " << j << "\n";
                    }
                }
                break;
            }
        }
        if (!done) {
            cout << -1 << "\n";
        }
    }
}