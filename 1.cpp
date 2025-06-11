#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=305;
int T,n,r,k,a[N][N],cnt,dx[8]={0,-1,0,1,-1,-1,1,1},dy[8]={1,0,-1,0,-1,1,1,-1},p[N*N];
ll dis[N][N],v[N][N];
pair<int,int>prt[N][N];
bool f[N][N],g[N][N],vis[N][N];
char c[N][N];
struct nn{
    int x,y,val;
}b[N*N];
struct node{
    int x,y;ll d;
    bool operator<(const node &b)const{return d>b.d;}
}tmp;
bool cmp(nn s,nn t){return s.val<t.val;}
int getfa(int x)
{
    if(p[x]==x)return x;
    return p[x]=getfa(p[x]);
}
void dfs(int x,int y,int op)
{
    vis[x][y]=1;
    for(int i=0;i<4;i++)
    {
        int kx=x+dx[(i+op)%4],ky=y+dy[(i+op)%4];
        if(kx<1||kx>n||ky<1||ky>n||vis[kx][ky]||!f[kx][ky])continue;
        prt[kx][ky]=make_pair(x,y),dfs(kx,ky,(i+op)%4==3);
    }
}
ll solve(int lim,int op)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            vis[i][j]=0,dis[i][j]=1e18;
            if((c[i][j]=='0'||(op&&g[i][j]))&&a[i][j]<lim)v[i][j]=1e18;
            else v[i][j]=max(0,lim-a[i][j]);
        }
    }
    priority_queue<node>pq;
    for(int i=1;i<=n;i++)if(!g[i][1]||!op)dis[i][1]=v[i][1],pq.emplace((node){i,1,v[i][1]});
    for(int i=2;i<=n;i++)if(!g[1][i]||!op)dis[1][i]=v[1][i],pq.emplace((node){1,i,v[1][i]});
    for(int i=2;i<=r;i++)if(!g[i][n]||!op)dis[i][n]=v[i][n],pq.emplace((node){i,n,v[i][n]});
    while(!pq.empty())
    {
        tmp=pq.top(),pq.pop();
        int x=tmp.x,y=tmp.y;
        if(vis[x][y])continue;
        vis[x][y]=1;
        for(int i=0;i<8;i++)
        {
            int kx=x+dx[i],ky=y+dy[i];
            if(kx<1||kx>n||ky<1||ky>n)continue;
            if(dis[x][y]+v[kx][ky]<dis[kx][ky])
            {
                dis[kx][ky]=dis[x][y]+v[kx][ky];
                pq.emplace((node){kx,ky,dis[kx][ky]});
            }
        }
    }
    ll ans=1e18;
    for(int i=1;i<=n;i++)ans=min(ans,dis[n][i]);
    for(int i=r;i<=n;i++)ans=min(ans,dis[i][n]);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--)
    {
        cin>>n>>r>>k,cnt=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)f[i][j]=g[i][j]=vis[i][j]=0;
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)cin>>a[i][j],b[++cnt]=(nn){i,j,a[i][j]};
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)cin>>c[i][j];
        }
        sort(b+1,b+cnt+1,cmp);
        for(int i=1;i<=n*n;i++)p[i]=i;
        int ansm=-1;
        for(int i=1;i<=cnt;i++)
        {
            f[b[i].x][b[i].y]=1;
            for(int j=0;j<4;j++)
            {
                int kx=b[i].x+dx[j],ky=b[i].y+dy[j];
                if(kx<1||kx>n||ky<1||ky>n||!f[kx][ky])continue;
                int fx=getfa((b[i].x-1)*n+b[i].y),fy=getfa((kx-1)*n+ky);
                if(fx!=fy)p[fy]=fx;
                if(getfa(1)==getfa(r*n)){ansm=b[i].val;break;}
            }
            if(ansm!=-1)break;
        }
        for(int i=1;i<=cnt;i++)if(b[i].val<=ansm)f[b[i].x][b[i].y]=1;
        dfs(r,n,0);
        int px=1,py=1;
        while(px!=r||py!=n)
        {
            g[px][py]=1;
            int tx=prt[px][py].first,ty=prt[px][py].second;
            px=tx,py=ty;
        }
        g[r][n]=1;
        int l=1,r=2e6;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(solve(mid,mid>ansm)<=k)l=mid+1;
            else r=mid-1;
        }
        cout<<ansm<<' '<<r<<'\n';
    }
    return 0;
}
