#include<bits/stdc++.h>
using namespace std;
#define maxm 100005
#define maxn 15
int a[maxn], s[maxm][maxn], b[maxn * 2], n, k, ans;
void put(int num[]) {
    printf("(%d", num[0]);
    for(int i = 1; i < n; i++)
        printf(",%d", num[i]);
    printf(")\n");
}
bool judge(int x) {
    for(int i = x, j = 0; j < n; i++, j++)
        if(a[j] != b[i])
            return b[i] > a[j];
    return false;
}
void check() {
    for(int i = 0; i < n; i++)
        b[i] = b[n + i] = a[i];
//move
    for(int i = 0; i < n; i++)
        if(b[i] == a[0] && judge(i))
            return ;
//res
    for(int i = 0; i < 2 * n; i++)
        b[i] = -b[i];
//opp and move
    for(int i = 0; i < n; i++)
        if(b[i] == a[0] && judge(i))
            return ;
//swap and opp
    for(int i = 0; i < n; i++)
        swap(b[i],b[2 * n - i - 1]);
//swap and opp and move
    for(int i = 0; i < n; i++)
        if(b[i] == a[0] && judge(i))
            return ;
//opp
    for(int i = 0; i < 2 * n; i++)
        b[i] = -b[i];
//swap and move
    for(int i = 0; i < n; i++)
        if(b[i] == a[0] && judge(i))
            return ;
    memcpy(s[ans++],a,sizeof(a));
}
void dfs(int cur, int Sum) {
    if(cur == n) {
        if(Sum == 0)
            check();
        return ;
    }
    if(abs(Sum) > ( (n - cur) * a[0]))
        return ;
    for(a[cur] = -a[0]; a[cur] < a[0]; a[cur]++) {
        if(a[cur - 1] == a[0] && a[cur] > a[1])
            return ;
        dfs(cur+1,Sum + a[cur]);
    }
    if(a[cur] == a[0] && a[cur - 1] <= a[1])
        dfs(cur+1,Sum + a[cur]);
}
int main() {
    int cas = 0;
    while(scanf("%d%d", &n, &k) != EOF && n) {
        ans = 1;
        for(a[0] = 1; a[0] <= k; a[0]++)
            dfs(1,a[0]);
        if(cas++)
            printf("\n");
        printf("%d\n", ans);
        for(int i = 0; i < ans; i++)
            put(s[i]);
    }
    return 0;
}