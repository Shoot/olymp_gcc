#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    mt19937 mt(time(0));
    uniform_int_distribution<int> idx(0, n-1);
    uniform_real_distribution<double> _01(0, 1);
    shuffle(a.begin(), a.end(), mt);

    // https://informatics.msk.ru/mod/statements/view.php?id=1975#1
    // find permutation with cost 0
    auto cost = [&] () -> int {
        int cost = 0;
        for (int i = 0; i < n; i += 1) {
            for (int j = i+1; j < n; j += 1) {
                if (abs(a[i]-a[j])==j-i) {
                    cost += 1;
                }
            }
        }
        return cost;
    };
    double t = 1;
    int curr_cost = cost();
//    cout << curr_cost << "!!\n";
    int from = clock();
    int ops = 0;
    while (curr_cost) {
        t *= 0.99;
        ops += 1;
        int one = idx(mt);
        int another = idx(mt);
        swap(a[one], a[another]);
        int c = cost();
        if (c < curr_cost || exp((curr_cost-c)/t) > _01(mt)) {
            curr_cost = c;
        } else {
            swap(a[one], a[another]);
        }
        if (double(clock()-from)/CLOCKS_PER_SEC > 10) {
            break;
        }
    }
    cout << ops << ":D\n";
    cout << curr_cost << "!!\n";
    for (auto &x : a) {
        cout << x << " ";
    }cout << "\n";
}