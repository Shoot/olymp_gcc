//#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
//using namespace __gnu_pbds;
//template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
//#define double long double
#define YES(x) cout << (x?"YES\n":"NO\n")
#define ALICE(x) cout << (x?"Alice\n":"Bob\n")
#define BOB(x) cout << (x?"Bob\n":"Alice\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
constexpr int INF = 1e18;
signed main() {
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
            assert(type == 3);
            return m-j;
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
//        auto rect_sum_ = [&] (const vector<vector<int>>& v, int lr, int lc, int rr, int rc, int mnozh) -> int {
//            if (mnozh == 1) {
//                swap(lr, rr);
//                swap(lc, rc);
//            }
//            return rect_sum(v, lr, lc, rr, rc);
//        };
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
                    SU[k][3][0][i][j] = SU[k][3][1][i][j] = rect_sum(R[k], i, j, i, n-1);
                    SU_A[k][3][0][i][j] = SU_A[k][3][1][i][j] = rect_sum(R_A[k], i, j, i, n-1);
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
//        for (int i = 0; i < n; i += 1) {
//            for (int j = 0; j < m; j += 1) {
//                cout << val(0, i, j)*a[i][j] << " ";
//            }cout << "\n";
//        }cout << "\n";
//        for (int i = 0; i < n; i += 1) {
//            for (int j = 0; j < m; j += 1) {
//                cout << rect_sum(R[0], i, j, i, j) << " ";
//            }cout << "\n";
//        }cout << "\n";
//        for (int i = 0; i < n; i += 1) {
//            for (int j = 0; j < m; j += 1) {
//                cout << SU[0][1][0][i][j] << " ";
//            }cout << "\n";
//        }
        // 0 = down, 1 = left, 2 = up, 3 = right
        map<int, function<int(int, int, int, int, const vector<vector<int>>, const vector<vector<int>>&)>> f;
        f[1] = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(r+(c-end)*mnozh+mnozh, end-1)?s[r+(c-end)*mnozh+mnozh][end-1]:0) - (mnozh==-1?rect_sum(rect, r+(c-end)*mnozh, 0, r, end-1):rect_sum(rect, r, 0, r+(c-end)*mnozh, end-1));
        };
        f[3] = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(r+(end-c)*mnozh+mnozh, end+1)?s[r+(end-c)*mnozh+mnozh][end+1]:0) - (mnozh==-1?rect_sum(rect, r+(end-c)*mnozh, end+1, r, n-1):rect_sum(rect, r, end+1, r+(end-c)*mnozh, m-1));
        };
        f[0] = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(end+1, c+(end-r)*mnozh+mnozh)?s[end+1][c+(end-r)*mnozh+mnozh]:0) - (mnozh==-1?rect_sum(rect, end+1, c+(end-r)*mnozh, n-1, c):rect_sum(rect, end+1, c, n-1, c+(end-r)*mnozh));
        };
        f[2] = [&] (int r, int c, int end, int mnozh, const vector<vector<int>>& s, const vector<vector<int>>& rect) -> int {
            return s[r][c] - (valid(end-1, c+(r-end)*mnozh+mnozh)?s[end-1][c+(r-end)*mnozh+mnozh]:0) - (mnozh==-1?rect_sum(rect, 0, c+(r-end)*mnozh, end-1, c):rect_sum(rect, 0, c, end-1, c+(r-end)*mnozh));
        };
        auto treug = [&] (int r, int c, int end, int i, int j, int k) -> int {
            int mnozh = k?1:-1;
            int cancel=i==0?min(n-1-end, n-1-r):i==3?min(m-1-end, m-1-c):i==2?min(end, r):min(end, c);
//            if (j == 2) {
//                int su = SU     [i][j][k][r][c] - (valid(end-1, c+(r-end)*mnozh+mnozh)?SU  [i][j][k][end-1][c+(r-end)*mnozh+mnozh]:0);
//                int sum_a = SU_A[i][j][k][r][c] - (valid(end-1, c+(r-end)*mnozh+mnozh)?SU_A[i][j][k][end-1][c+(r-end)*mnozh+mnozh]:0);
//                return su - sum_a*cancel;
//            }
//            if (j == 0) {
//                int su = SU     [i][j][k][r][c] - (valid(end+1, c+(end-r)*mnozh+mnozh)?SU  [i][j][k][end+1][c+(end-r)*mnozh+mnozh]:0);
//                int sum_a = SU_A[i][j][k][r][c] - (valid(end+1, c+(end-r)*mnozh+mnozh)?SU_A[i][j][k][end+1][c+(end-r)*mnozh+mnozh]:0);
//                return su - sum_a*cancel;
//            }
            return f[j](r, c, end, mnozh, SU[i][j][k], R[i]) - f[j](r, c, end, mnozh, SU_A[i][j][k], R_A[i])*cancel;
//            if (j == 3) {
//                return t3(r, c, end, mnozh, SU[i][j][k], R[i]) - t3(r, c, end, mnozh, SU_A[i][j][k], R_A[i])*cancel;
//            }
//            assert(false);
        };
        for (int ii = 0; ii < q; ii += 1) {
            int lr, lc, rr, rc;
            cin >> lr >> lc >> rr >> rc;
            lr -= 1, rr -= 1, lc -= 1, rc -= 1;
            int w = rc - lc + 1;
            int h = rr - lr + 1;
            int nizp = treug(rr, rc, rc+1-min(w/2, h/2), 0, 1, 0);
            cout << nizp << "!!\n";
            assert(nizp == treug(rr, rc, rc, 0, 1, 0));
//            int niz = treug(rr, rc, rc+1-min(w/2, h/2), 0, 1, 0) + treug(rr, lc, lc-1+min(w/2, h/2), 0, 3, 0); // нижняя сторона сделана
//            int verh = treug(lr, lc, lc-1+min(w/2, h/2), 2, 3, 1) + treug(lr, rc, rc+1-min(w/2, h/2), 2, 1, 1);
//            int levo = treug(rr, lc, rr+1-min(w/2, h/2), 1, 2, 0) + treug(lr, lc, lr-1+min(w/2, h/2), 1, 0, 0);
//            int pravo = treug(rr, rc, rr+1-min(w/2, h/2), 3, 2, 1) + treug(lr, rc, lr-1+min(w/2, h/2), 3, 0, 1);
//            cout << niz << " " << verh << " " << levo << " " << pravo << "\n";
//            cout << niz+verh+levo+pravo << "\n";
        }
    }
}