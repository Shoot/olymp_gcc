#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 69
#endif
const int N = 1e5+5;
const int8_t SIZE = 3;
const int8_t SIZE_SQ = 3*3;
void print(const int8_t a[SIZE_SQ]) {
    for (int8_t i=0; i<SIZE_SQ; i++) {
        if (a[i] == 1) cout << 'X';
        else if (a[i] == 2) cout << 'O';
        else cout << '.';
        if (i%3==SIZE-1)
            cout << endl;
    }
}
int8_t does_1_win_2_lose (int8_t a[SIZE_SQ], int8_t turn) {
    vector<vector<int8_t>> wins = {
        {a[0], a[1], a[2]},
        {a[3], a[4], a[5]},
        {a[6], a[7], a[8]},
        {a[0], a[3], a[6]},
        {a[1], a[4], a[7]},
        {a[2], a[5], a[8]},
        {a[0], a[4], a[8]},
        {a[2], a[4], a[6]},
    };
    for (vector<int8_t> &j: wins) {
        if (j[0] == j[1] && j[0] == j[2] && j[0] > 0) {
            if (j[0] == 1)
                return 1;
            return 0;
        }
    }
    int won = 0;
    int tot = 0;
    for (int8_t i=0; i<SIZE_SQ; i++){
        if (a[i] <= 0) {
            int8_t temp[SIZE_SQ];
            copy(a, a+SIZE_SQ, temp);
            temp[i] = turn;
            int8_t next_turn = (turn == 1)?2:1;
            won += does_1_win_2_lose(temp, next_turn);
            tot += 1;
            if (turn == 1 && won >= 1) return 1;
        }
    }
    return (tot == 0) ? (int8_t)0 : (int8_t)(turn == 2 && won == tot);
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int8_t a[SIZE_SQ];
    string s =
            "..."
            ".XO"
            "...";
    int8_t X_count = 0;
    int8_t O_count = 0;
    for (auto j: s) {
        if (j == 'X')
            X_count += 1;
        else if (j == 'O')
            O_count += 1;
    }
    for (int8_t i=0; i<SIZE; i++)
        a[i] = (int8_t)((s[i] == 'X')?1:(s[i] == 'O')?2:-1);
    if (O_count>X_count || abs(X_count-O_count)>1) {
        cout << "WRONG_BOARD";
        return 0;
    }
    cout << (does_1_win_2_lose(a, X_count==O_count?1:2)?"X wins":"IDK");
    return 0;
}