#include <bits/stdc++.h>
using namespace std;
int main () {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    struct suffix {
        int idx;
        int high_priority_class, low_priority_class;
    };
    function<int(suffix,suffix)> comp = [] (suffix a, suffix b){
        if (a.high_priority_class == b.high_priority_class) {
            return a.low_priority_class < b.low_priority_class;
        }
        return a.high_priority_class < b.high_priority_class;
    };
    a.push_back(-1);
    n += 1;
    vector<suffix> curr(n);
    for (int i = 0; i < n; i += 1) {
        curr[i].idx = i;
        curr[i].high_priority_class = a[i];
        curr[i].low_priority_class = a[i];
    }
    sort(curr.begin(), curr.end(), comp);
    int classes_cnt = 1;
    vector<int> c(n);
    for (int i = 0; i < n; i += 1) {
        if (i > 0 && (curr[i].high_priority_class!=curr[i-1].high_priority_class ||
                      curr[i].low_priority_class!=curr[i-1].low_priority_class)) {
            classes_cnt += 1;
        }
        c[curr[i].idx] = classes_cnt;
    }
    for (int k = 0; classes_cnt < n; k += 1) {
        int two_pow_k = 1ll << k;
        for (int i = 0; i < n; i += 1) {
            curr[i].idx = i;
            curr[i].high_priority_class = c[i];
            curr[i].low_priority_class = c[(i+two_pow_k)%n];
        }
        sort(curr.begin(), curr.end(), comp);
        classes_cnt = 1;
        for (int i = 0; i < n; i += 1) {
            if (i > 0 && (curr[i].high_priority_class!=curr[i-1].high_priority_class ||
                          curr[i].low_priority_class!=curr[i-1].low_priority_class)) {
                classes_cnt += 1;
            }
            c[curr[i].idx] = classes_cnt;
        }
    }
    vector<int> rank(n);
    vector<int> sa(n);
    vector<int> lcp(n-1);
    for (int i = 0; i < n; i+=1) {
        rank[i] = c[i]-1;
        sa[c[i]-1] = i;
    }
    int k = 0;
    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {
            k=0;
            continue;
        }
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && a[i+k]==a[j+k]) k++;
        lcp[rank[i]]=k;
    }
    int X = accumulate(lcp.begin(), lcp.end(), 0);
    n -= 1;
    // одна входнит в другую суффиксом, остальное нули - этот случай дает равенство
    int cnt0 = 0;
    int zero_subseg = 0;
    for (int i = 0; i < n; i += 1) {
        if (a[i] != 0) {
            zero_subseg += cnt0 * (cnt0 + 1) / 2;
            cnt0 = 0;
        } else {
            cnt0 += 1;
        }
    }
    zero_subseg += cnt0 * (cnt0 - 1) / 2;
    cout << "zero_subseg = " << zero_subseg << endl;
    cout << (n*(n+1)/2*n*(n+1)/2 - X - zero_subseg)/2 << "\n";
    return 0;
}