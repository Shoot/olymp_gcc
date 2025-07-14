#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        for (auto &x : a) {
            for (auto &y : x) {
                cin >> y;
            }
        }
        int q;
        cin >> q;
        // [к какой стенке][куда идет треугольник ч1 (нлвп)][куда идет треугольник ч2: += по той коорде которая меняется или -= ]
        vector<vector<vector<vector<vector<int>>>>> SU(4, vector<vector<vector<vector<int>>>>(4, vector<vector<vector<int>>>(2, vector<vector<int>>(n, vector<int>(m)))));
        vector<vector<vector<vector<vector<int>>>>> SU_A(4, vector<vector<vector<vector<int>>>>(4, vector<vector<vector<int>>>(2, vector<vector<int>>(n, vector<int>(m)))));
        vector<vector<vector<int>>> R(4, vector<vector<int>>(n, vector<int>(m)));
        vector<vector<vector<int>>> R_A(4, vector<vector<int>>(n, vector<int>(m)));
        auto val = [&] (int type, int i, int j) -> int {
            if (type == 0) {
                return n-i;
            }
            if (type == 1) {
                return j+1;
            }
            if (type == 2) {
                return i+1;
            }
            if (type == 3) {
                return m-j;
            }
            assert(false);
        };
        for (int k = 0; k < 4; k += 1) {
            for (int i = 0; i < n; i += 1) {
                for (int j = 0; j < m; j += 1) {
                    R[k][i][j] = val(k, i, j)*a[i][j];
                    R_A[k][i][j] = a[i][j];
                    if (i) {
                        R[k][i][j] += R[k][i-1][j];
                        R_A[k][i][j] += R_A[k][i-1][j];
                    }
                    if (j) {
                        R[k][i][j] += R[k][i][j-1];
                        R_A[k][i][j] += R_A[k][i][j-1];
                    }
                    if (i && j) {
                        R[k][i][j] -= R[k][i-1][j-1];
                        R_A[k][i][j] -= R_A[k][i-1][j-1];
                    }
                }
            }
        }
        auto rect_sum = [&] (const vector<vector<int>>& v, int lr, int lc, int rr, int rc) -> int {
            lr = max(lr, 0ll);
            lc = max(lc, 0ll);
            rr = min(rr, n-1);
            rc = min(rc, m-1);
            if (lr > rr || lc > rc) {
                return 0;
            }
            int ans = v[rr][rc];
            ans -= lc?v[rr][lc-1]:0;
            ans -= lr?v[lr-1][rc]:0;
            ans += lc&&lr?v[lr-1][lc-1]:0;
            return ans;
        };
        auto valid = [&] (int i, int j) -> bool {
            return i>=0&&i<n&&j>=0&&j<m;
        };
        for (int k = 0; k < 4; k += 1) {
            for (int i = n-1; i >= 0; i -= 1) {
                for (int j = 0; j < m; j += 1) {
                    SU[k][0][0][i][j] = SU[k][0][1][i][j] = rect_sum(R[k], i, j, n-1, j);
                    SU_A[k][0][0][i][j] = SU_A[k][0][1][i][j] = rect_sum(R_A[k], i, j, n-1, j);
                    if (valid(i+1, j+1)) {
                        SU[k][0][1][i][j] += SU[k][0][1][i+1][j+1];
                        SU_A[k][0][1][i][j] += SU_A[k][0][1][i+1][j+1];
                    }
                    if (valid(i+1, j-1)) {
                        SU[k][0][0][i][j] += SU[k][0][0][i+1][j-1];
                        SU_A[k][0][0][i][j] += SU_A[k][0][0][i+1][j-1];
                    }
                }
            }
            for (int i = 0; i < n; i += 1) {
                for (int j = 0; j < m; j += 1) {
                    SU[k][2][0][i][j] = SU[k][2][1][i][j] = rect_sum(R[k], 0, j, i, j);
                    SU_A[k][2][0][i][j] = SU_A[k][2][1][i][j] = rect_sum(R_A[k], 0, j, i, j);
                    if (valid(i-1, j+1)) {
                        SU[k][2][1][i][j] += SU[k][2][1][i-1][j+1];
                        SU_A[k][2][1][i][j] += SU_A[k][2][1][i-1][j+1];
                    }
                    if (valid(i-1, j-1)) {
                        SU[k][2][0][i][j] += SU[k][2][0][i-1][j-1];
                        SU_A[k][2][0][i][j] += SU_A[k][2][0][i-1][j-1];
                    }
                }
            }
            for (int j = 0; j < m; j += 1) {
                for (int i = 0; i < n; i += 1) {
                    SU[k][1][0][i][j] = SU[k][1][1][i][j] = rect_sum(R[k], i, 0, i, j);
                    SU_A[k][1][0][i][j] = SU_A[k][1][1][i][j] = rect_sum(R_A[k], i, 0, i, j);
                    if (valid(i+1, j-1)) {
                        SU[k][1][1][i][j] += SU[k][1][1][i+1][j-1];
                        SU_A[k][1][1][i][j] += SU_A[k][1][1][i+1][j-1];
                    }
                    if (valid(i-1, j-1)) {
                        SU[k][1][0][i][j] += SU[k][1][0][i-1][j-1];
                        SU_A[k][1][0][i][j] += SU_A[k][1][0][i-1][j-1];
                    }
                }
            }
            for (int j = m-1; j >= 0; j -= 1) {
                for (int i = 0; i < n; i += 1) {
                    SU[k][3][0][i][j] = SU[k][3][1][i][j] = rect_sum(R[k], i, j, i, m-1);
                    SU_A[k][3][0][i][j] = SU_A[k][3][1][i][j] = rect_sum(R_A[k], i, j, i, m-1);
                    if (valid(i+1, j+1)) {
                        SU[k][3][1][i][j] += SU[k][3][1][i+1][j+1];
                        SU_A[k][3][1][i][j] += SU_A[k][3][1][i+1][j+1];
                    }
                    if (valid(i-1, j+1)) {
                        SU[k][3][0][i][j] += SU[k][3][0][i-1][j+1];
                        SU_A[k][3][0][i][j] += SU_A[k][3][0][i-1][j+1];
                    }
                }
            }
        }
        // 0 = down, 1 = left, 2 = up, 3 = right
        auto t0 = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(end+1, c+(end-r)*mnozh+mnozh)?s[end+1][c+(end-r)*mnozh+mnozh]:0) - (mnozh==-1?rect_sum(rect, end+1, c+(end-r)*mnozh, n-1, c):rect_sum(rect, end+1, c, n-1, c+(end-r)*mnozh));
        };
        auto t1 = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(r+(c-end)*mnozh+mnozh, end-1)?s[r+(c-end)*mnozh+mnozh][end-1]:0) - (mnozh==-1?rect_sum(rect, r+(c-end)*mnozh, 0, r, end-1):rect_sum(rect, r, 0, r+(c-end)*mnozh, end-1));
        };
        auto t2 = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(end-1, c+(r-end)*mnozh+mnozh)?s[end-1][c+(r-end)*mnozh+mnozh]:0) - (mnozh==-1?rect_sum(rect, 0, c+(r-end)*mnozh, end-1, c):rect_sum(rect, 0, c, end-1, c+(r-end)*mnozh));
        };
        auto t3 = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(r+(end-c)*mnozh+mnozh, end+1)?s[r+(end-c)*mnozh+mnozh][end+1]:0) - (mnozh==-1?rect_sum(rect, r+(end-c)*mnozh, end+1, r, m-1):rect_sum(rect, r, end+1, r+(end-c)*mnozh, m-1));
        };
        auto treug = [&] (int r, int c, int end, int i, int j, int k) -> int {
            int mnozh = k?1:-1;
            int cancel=i==0?n-1-r:i==3?m-1-c:i==2?r:c;
            if (j == 0) {
                return t0(r, c, end, mnozh, SU[i][j][k], R[i]) - t0(r, c, end, mnozh, SU_A[i][j][k], R_A[i])*cancel;
            }
            if (j == 1) {
                return t1(r, c, end, mnozh, SU[i][j][k], R[i]) - t1(r, c, end, mnozh, SU_A[i][j][k], R_A[i])*cancel;
            }
            if (j == 2) {
                return t2(r, c, end, mnozh, SU[i][j][k], R[i]) - t2(r, c, end, mnozh, SU_A[i][j][k], R_A[i])*cancel;
            }
            if (j == 3) {
                return t3(r, c, end, mnozh, SU[i][j][k], R[i]) - t3(r, c, end, mnozh, SU_A[i][j][k], R_A[i])*cancel;
            }
            assert(false);
        };
        for (int ii = 0; ii < q; ii += 1) {
            int lr, lc, rr, rc;
            cin >> lr >> lc >> rr >> rc;
            lr -= 1, rr -= 1, lc -= 1, rc -= 1;
//            lr = mt()%n;
//            rr = mt()%(n-lr)+lr;
//            lc = mt()%m;
//            rc = mt()%(m-lc)+lc;
//            cout << ii << " " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count() << endl;
            int w = rc - lc + 1;
            int h = rr - lr + 1;
            int C = min(h/2, w/2);
            if (h <= w) {
                int levo = (h>2?treug(rr-1, lc, rr-C+((min(h, w)&1)==0), 1, 2, 1):0) + (h>3?treug(lr+1, lc, lr+C-1, 1, 0, 1):0);
                int pravo = (h>2?treug(rr-1, rc, rr-C+((min(h, w)&1)==0), 3, 2, 0):0) + (h>3?treug(lr+1, rc, lr+C-1, 3, 0, 0):0);
                int niz = treug(rr, rc, rc+1-C, 0, 1, 0) + treug(rr, lc, lc-1+C, 0, 3, 0);
                niz += rect_sum(R[0], lr+C, lc+C, rr, rc-C)-rect_sum(R_A[0], lr+C, lc+C, rr, rc-C)*(n-1-rr);
                int ans = levo+pravo+niz;
                if (h > 1) {
                    int verh = treug(lr, lc, lc-1+C, 2, 3, 1) + treug(lr, rc, rc+1-C, 2, 1, 1);
                    verh += rect_sum(R[2], lr, lc+C, lr+C-1, rc-C) - rect_sum(R_A[2], lr, lc+C, lr+C-1, rc-C)*(lr);
                    ans += verh;
                }
                cout << ans << "\n";
            } else {
                int niz = (w>2?treug(rr, rc-1, rc-C+((min(h, w)&1)==0), 0, 1, 0):0) + (w>3?treug(rr, lc+1, lc+C-1, 0, 3, 0):0);
                int verh = (w>2?treug(lr, lc+1, lc+C-((min(h, w)&1)==0), 2, 3, 1):0) + (w>3?treug(lr, rc-1, rc-C+1, 2, 1, 1):0);
                int levo = treug(rr, lc, rr+1-C, 1, 2, 1) + treug(lr, lc, lr-1+C, 1, 0, 1);
                levo += rect_sum(R[1], lr+C, lc, rr-C, rc-C)-rect_sum(R_A[1], lr+C, lc, rr-C, rc-C)*(lc);
                int ans = niz+verh+levo;
                if (w > 1) {
                    int pravo = treug(rr, rc, rr+1-C, 3, 2, 0) + treug(lr, rc, lr-1+C, 3, 0, 0);
                    pravo += rect_sum(R[3], lr+C, rc-C+1, rr-C, rc)-rect_sum(R_A[3], lr+C, rc-C+1, rr-C, rc)*(m-1-rc);
                    ans += pravo;
                }
                cout << ans << "\n";
            }
        }
    }
}