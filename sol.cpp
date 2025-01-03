#include <iostream>
#include <vector>
#include <stack>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    char S[40001];
    while (true) {
        int M;
        cin >> M;
        if (!M) {
            return 0;
        }
        cin >> S;
        string s;
        int it = 0;
        while (S[it] != '\0') {
            s.push_back(S[it]);
            it += 1;
        }
//        string s;
//        cin >> s;
        s.push_back('\0');
        int n = int(s.size());
        if (M == 1) {
            cout << n-1 << " " << 0 << "\n";
            continue;
        }
        vector<int> rank(n);
        vector<int> sa(n);
        vector<int> lcp(n - 1);
        int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = make_pair(c[p[i]], c[(p[i] + (1 << h)) % n]);
                pair<int, int> prev = make_pair(c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]);
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        for (int i = 0; i < n; i += 1) {
            rank[i] = c[i];
            sa[c[i]] = i;
        }
        int k = 0;
        for (int i = 0; i < n; i += 1, k ? k -= 1 : 0) {
            if (rank[i] == n-1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i]+1];
            while (i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
        }
        n -= 1;
        vector<int> left(n), right(n);
        stack<int> stck;
        for (int j = 0; j < n; j += 1) {
            while (!stck.empty() && lcp[stck.top()] >= lcp[j]) stck.pop();
            if (stck.empty()) left[j] = -1;
            else left[j] = stck.top();
            stck.push(j);
        }
        while (!stck.empty()) stck.pop();
        for (int j = n - 1; j >= 0; j -= 1) {
            while (!stck.empty() && lcp[stck.top()] >= lcp[j]) stck.pop();
            if (stck.empty()) right[j] = n;
            else right[j] = stck.top();
            stck.push(j);
        }
        int maxi = -66;
        int last = -66;
        vector<vector<int>> st(20, vector<int>(n));
        st[0] = sa;
        for (int b = 1; b < 20; b += 1) {
            for (int i = 0; i < n; i += 1) {
                st[b][i] = st[b-1][i];
                int nxt = i+(1 << (b-1));
                if (nxt < n) st[b][i] = max(st[b][i], st[b-1][nxt]);
            }
        }
        for (int i = 0; i < n; i += 1) {
            int width = right[i]-left[i]-1;
            int height = lcp[i];
            if (width >= M - 1 && height >= maxi) {
                if (height > maxi) {
                    last = -1;
                }
                maxi = height;
                int r = right[i];
                int l = left[i] + 1;
                int sz = r-l+1;
                int bt = 0;
                int btval = 1;
                while (btval*2 <= sz) {
                    btval *= 2;
                    bt += 1;
                }
                last = max(last, max(st[bt][l], st[bt][r-(1ll << bt)+1]));
            }
        }
        if (maxi == 0) {
            cout << "none\n";
        } else {
            cout << maxi << " " << last << "\n";
        }
    }
}