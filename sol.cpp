#include <bits/stdc++.h>
using namespace std;
vector<int> a(12);
int total;
void s(vector<int> &values, vector<bool> &used, int curr) {
    for (int i = 0; i < 12; i += 1) {
        if (!used[i]) {
            used[i] = true;
            values[curr] = a[i];
            s(values, used, curr + 1);
            used[i] = false;
            if (curr == 0) {
                break;
            }
        }
    }
    values[curr] = 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (true) {
        for (auto &x : a) {
            cin >> x;
            if (x == 0) {
                return 0;
            }
        }
        sort(a.begin(), a.end());
        total = 0;
        vector<bool> u(12);
        vector<int> v(12);
        s(v, u, 0);
        cout << total << "\n";
    }
}