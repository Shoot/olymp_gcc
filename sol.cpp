#include <bits/stdc++.h>
using namespace std;
vector<int> a(12);
vector<bool> used(12, false);
int total;
void s(vector<int> &values, int curr) {
    int fixed = curr - 1;
    int su = values[0] + values[1] + values[2] + values[3];
    // мы не можем проверять так как там нули
    if (fixed >= 8 && values[3] + values[8] + values[7] + values[6] != su) {
        return;
    }
    if (fixed >= 6 && values[6] + values[5] + values[4] + values[0] != su) {
        return;
    }
    if (fixed >= 10 && values[9] + values[4] + values[1] + values[10] != su) {
        return;
    }
    if (fixed >= 11 && values[10] + values[2] + values[8] + values[11] != su) {
        return;
    }
    if (fixed >= 11 && values[11] + values[7] + values[5] + values[9] != su) {
        return;
    }
    if (curr == 12) {
        total += 1;
        return;
    }
    for (int i = 0; i < 12; i += 1) {
        if (!used[i]) {
            used[i] = true;
            values[curr] = a[i];
            s(values, curr + 1);
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
        }
        sort(a.begin(), a.end());
        fill(used.begin(), used.end(), false);
        if (accumulate(a.begin(), a.end(), 0) == 0) {
            return 0;
        }
        // нужно получать +x-тую относительно текущей перестановки
        total = 0;
        vector<int> v(12);
        s(v, 0);
        cout << total << "\n";
    }
}