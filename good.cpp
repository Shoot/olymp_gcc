#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        int c, d, m;
        cin >> c >> d >> m;
        std::vector<int> best(d + 1, 0);
        best[0] = c;
        for (int i = 1; i <= d; i++) {
            if (m < 1) break;
            int x = best[i - 1];
            int count = 0;
            while (x > m) {
                x -= m;
                count += m - 1;
                if (count > best[i])
                    best[i] = count;
                count--;
            }
            count += x - 1;
            if (count > best[i])
                best[i] = count;
        }
        std::cout << best[d] << std::endl;
    }
    return 0;
}

