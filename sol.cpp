#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) {
        cin >> x;
        x += 1;
    }
    n += 1;
    a.push_back(0);
    vector<long long> rank(n);
    vector<long long> sa(n);
    vector<long long> lcp(n - 1);
    long long alphabet = 12;
    vector<long long> p(n), c(n), cnt(max(alphabet, n), 0);
    for (long long i = 0; i < n; i += 1) {
        cnt[a[i]] += 1;
    }
    for (long long i = 1; i < alphabet; i += 1) {
        cnt[i] += cnt[i - 1];
    }
    for (long long i = 0; i < n; i += 1) {
        p[--cnt[a[i]]] = i;
    }
    c[p[0]] = 0;
    long long classes = 1;
    for (long long i = 1; i < n; i += 1) {
        if (a[p[i]] != a[p[i - 1]]) {
            classes += 1;
        }
        c[p[i]] = classes - 1;
    }
    vector<long long> pn(n), cn(n);
    for (long long h = 0; (1 << h) < n; h += 1) {
        for (long long i = 0; i < n; i += 1) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) {
                pn[i] += n;
            }
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (long long i = 0; i < n; i += 1) {
            cnt[c[pn[i]]] += 1;
        }
        for (long long i = 1; i < classes; i += 1) {
            cnt[i] += cnt[i - 1];
        }
        for (long long i = n - 1; i >= 0; i--) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        classes = 1;
        for (long long i = 1; i < n; i += 1) {
            pair<long long, long long> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<long long, long long> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev) {
                classes += 1;
            }
            cn[p[i]] = classes - 1;
        }
        swap(c, cn);
    }
    for (long long i = 0; i < n; i += 1) {
        rank[i] = c[i];
        sa[c[i]] = i;
    }
    for (long long i = 0, k = 0; i < n; i += 1, k ? k -= 1 : 0) {
        if (rank[i] == n-1) {
            k = 0;
            continue;
        }
        long long j = sa[rank[i]+1];
        while (i+k < n && j+k < n && a[i+k] == a[j+k]) k++;
        lcp[rank[i]] = k;
    }
    n -= 1;
    long long decr = 0;
    long long incr = 0;
    for (auto &x : a) {
        x -= 1;
    }
    for (long long i = 0; i < n; i += 1) {
        if (a[i] == 0) {
            decr += n - i;
            incr = 1;
        }
    }
    for (long long i = 1; i < n; i += 1) {
        if (a[sa[i]] != 0) {
            decr += lcp[i];
        }
    }
    long long UNIQUE_SUBSTRINGS = n*(n+1)/2-decr+incr;
    return 0;
}