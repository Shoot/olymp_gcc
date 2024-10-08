#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
vector<int>sieve(2e6);
vector<int> fin_val(int x)
{
    set<int>st;
    while(x>1)
    {
        st.insert(sieve[x]);
        x/=sieve[x];
    }
    if(x>1)st.insert(x);
    vector<int>rs;
    for(auto &x:st)rs.push_back(x);
    return rs;
}
int main()
{
    for(int i=2;i<2e6;i++)
    {
        if(!sieve[i])
        {
            for(long long int j=i;j<2e6;j+=i)sieve[j]=i;
        }
    }
    vector<int>cnt(2e6);
    int n;
    cin>>n;
    vector<int>a(n);
    for(auto &x:a)cin>>x;
    for(int i=0;i<n;i++)
    {
        cout << a[i] << ":" << endl;
        vector<int>val=fin_val(a[i]);
        for (const auto &d : val) {
            cout << d << "." << endl;
        }
        for(int mask=0;mask<(1<<val.size());mask++)
        {
            int ans=1;
            for(int j=0;j<val.size();j++)if(mask&(1<<j))ans*=val[j];
            cout << ans << endl;
            cnt[ans]++;
        }
    }
    for(int i=0;i<n;i++)
    {
        vector<int>val=fin_val(a[i]);
        int cur_cnt=0;
        for(int mask=0;mask<(1<<val.size());mask++)
        {
            int ans=1;
            for(int j=0;j<val.size();j++)if(mask&(1<<j))ans*=val[j];
            if(__builtin_popcount(mask)%2==0)cur_cnt+=cnt[ans];
            else cur_cnt-=cnt[ans];
        }
        if(cur_cnt)
        {
            for(int j=0;j<n;j++)
            {
                if(j==i)continue;
                if(__gcd(a[i],a[j])==1)
                {
                    cout<<"NO"<<endl;
                    cout<<a[i]<<" "<<a[j]<<endl;
                    return 0;
                }
            }
            cout<<"this does not work";
        }
    }
    cout<<"YES"<<endl;
}
