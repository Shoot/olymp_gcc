#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, W;
    cin >> n >> W;
    struct Worker {
        int Qual;
        int Bound;
        int idx;
    };
    vector<Worker> workers(n);
    int idx = 0;
    for (auto &[Q, B, i] : workers) {
        cin >> B >> Q;
        i = ++idx;
    }
    sort(workers.begin(), workers.end(), [](const Worker &a, const Worker &b) {
        return double(a.Bound)/a.Qual < double(b.Bound)/b.Qual;
    });
    priority_queue<int> qs;
    int qs_sum = 0;
    struct Ans {
        int Size;
        int Cost;
        bool operator<(const Ans& other) {
            if (Size != other.Size) {
                return Size < other.Size;
            }
            return Cost > other.Cost;
        }
    };
    Ans ans = {-1, 0};
    int Max_idx = -1;
    for (int i = 0; i < n; i += 1) {
        double Max = double(workers[i].Bound)/workers[i].Qual;
        qs.push(workers[i].Qual);
        qs_sum += workers[i].Qual;
        int limit_qs_sum = W / Max;
        while (qs_sum > limit_qs_sum) {
            qs_sum -= qs.top();
            qs.pop();
        }
        if (ans < Ans{(int)qs.size(), (int)(Max * qs_sum)}) {
            ans = Ans{(int)qs.size(), (int)(Max * qs_sum)};
            Max_idx = i;
        }
    }
    cout << ans.Size << "\n";
    priority_queue<pair<int,int>> qs_guys;
    qs_sum = 0;
    for (int i = 0; i <= Max_idx; i += 1) {
        qs_guys.push({workers[i].Qual, workers[i].idx});
        qs_sum += workers[i].Qual;
    }
    double Max = double(workers[Max_idx].Bound)/workers[Max_idx].Qual;
    int limit_qs_sum = W / Max;
    set<int> not_using;
    while (qs_sum > limit_qs_sum) {
        qs_sum -= qs_guys.top().first;
        not_using.insert(qs_guys.top().second);
        qs_guys.pop();
    }
    for (int i = 0; i <= Max_idx; i += 1) {
        if (!not_using.count(workers[i].idx)) {
            cout << workers[i].idx << "\n";
        }
    }
}