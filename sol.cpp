#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;
signed main() {
    int n, k, p1, v1, p2, v2;
    cin >> n >> k >> p1 >> v1 >> p2 >> v2;
    if (p1%3 == p2%3) {
        int rest = k - v1;
        int cnt = 0;
        for (int i = 1; i <= k; i += 1) {
            for (int j = 1; j <= k; j += 1) {
                if (i + j == rest) {
                    cnt += 1;
                }
            }
        }
        if (v1 != v2) {
            cnt = 0;
        }
        cout << cnt << "\n";
        return 0;
    }
    if (v1 + v2 < k) {
        cout << 1 << "\n";
    } else {
        cout << 0 << "\n";
    }
}