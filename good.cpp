#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 1e5;

int N;
pii A[MAXN+10], B[MAXN+10];
int ans[MAXN+10];

struct BIT
{
    int tree[MAXN*2+10];
    void update(int i, int k) { for(; i<=N+N; i+=(i&-i)) tree[i]+=k; }
    int query(int i) { int ret=0; for(; i>0; i-=(i&-i)) ret+=tree[i]; return ret; }
}bit;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<int> comp;
    for(int i=1; i<=N; i++) cin >> A[i].first >> A[i].second;
    for(int i=1; i<=N; i++) cin >> B[i].first >> B[i].second;
    for(int i=1; i<=N; i++) comp.push_back(A[i].second), comp.push_back(B[i].second);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(int i=1; i<=N; i++) A[i].second=lower_bound(comp.begin(), comp.end(), A[i].second)-comp.begin()+1;
    for(int i=1; i<=N; i++) B[i].second=lower_bound(comp.begin(), comp.end(), B[i].second)-comp.begin()+1;

    set<pii> S;
    vector<pii> V;
    for(int i=1; i<=N; i++) V.push_back({A[i].first, -i});
    for(int i=1; i<=N; i++) V.push_back({B[i].first, i});
    sort(V.begin(), V.end());

    for(auto [x, p] : V)
    {
        if(p<0)
        {
            S.insert({A[-p].second, -p});
        }
        else
        {
            auto it=S.upper_bound({B[p].second, N+1});
            if(it==S.begin()) return !(cout << "syntax error\n");
            it--;
            ans[it->second]=p;
            S.erase(it);
        }
    }

    vector<array<int, 4>> V2;
    for(int i=1; i<=N; i++)
    {
        auto [xl, yl] = A[i];
        auto [xr, yr] = B[ans[i]];
        V2.push_back({xl, -1, yl, yl});
        V2.push_back({xl, -1, yr, yr});
        V2.push_back({xr, 1, yl, yl});
        V2.push_back({xr, 1, yr, yr});
        V2.push_back({xl, 0, yl, yr});
        V2.push_back({xr, 0, yl, yr});
    }
    sort(V2.begin(), V2.end());
    for(auto [x, ty, yl, yr] : V2)
    {
        if(ty==-1) bit.update(yl, 1);
        else if(ty==1) bit.update(yl, -1);
        else
        {
            if(bit.query(yr)-bit.query(yl-1)>2) return !(cout << "syntax error\n");
        }
    }
    for(int i=1; i<=N; i++) cout << ans[i] << '\n';
}