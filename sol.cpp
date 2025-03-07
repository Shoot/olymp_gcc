#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, k, s;
    cin >> n >> k >> s;
    s -= 1;
    string S;
    cin >> S;
    int maxi = 0;
    auto rightleftleft = [&] () -> void {
        vector<int> left; // hodov-by-cnt
        vector<int> leftval;
        for (int i = s-1; i >= 0; i -= 1) {
            if (S[i] == '#') {
                left.push_back(s-i);
                leftval.push_back(i);
            }
        }
        vector<int> next_to_the_right(n), next_to_the_left(n);
        int to_the_right = n;
        for (int i = n-1; i >= 0; i -= 1) {
            next_to_the_right[i] = to_the_right;
            if (S[i] == '#') {
                to_the_right = i;
            }
        }
        int to_the_left = -1;
        for (int i = 0; i < n; i += 1) {
            next_to_the_left[i] = to_the_left;
            if (S[i] == '#') {
                to_the_left = i;
            }
        }
        int curr = 0;
        for (int i = s; i < n; i += 1) {
            curr += S[i] == '#';
            int done = i-s;
            int left_available = k-2*done;
            auto it = upper_bound(left.begin(), left.end(), left_available);
            if (it != left.begin()) {
                it--;
                int from = next_to_the_left[leftval[it-left.begin()]]+1;
                int to = next_to_the_right[i]-1;
                maxi = max(maxi, to-from+1);
            } else if (k-done >= 0) {
                int from = next_to_the_left[s]+1;
                int to = next_to_the_right[i]-1;
                maxi = max(maxi, to-from+1);
            }
        }
    };
    rightleftleft();
    reverse(S.begin(), S.end());
    s = n - s - 1;
    rightleftleft();
    cout << maxi << "\n";
}