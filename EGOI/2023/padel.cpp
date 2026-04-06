#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N=2e5+5;

int n,m,x[N],y[N],r[N],t[N];
bool s[N];
vector<int>v[N],c[N];
multiset<array<int,2>>ms;

void dfs(int i,int d=m){
    s[i]=true;
    if(t[x[i]])ms.erase({t[x[i]],-x[i]});
    t[x[i]]+=d-i,ms.insert({t[x[i]],-x[i]});
    
    r[-(*ms.rbegin())[1]]++;
    for(auto i2:c[i])dfs(i2,i);

    ms.erase({t[x[i]],-x[i]}),t[x[i]]-=d-i;
    if(t[x[i]])ms.insert({t[x[i]],-x[i]});
}

main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>x[i]>>y[i],v[x[i]].push_back(i);
        for(auto j:v[y[i]])c[i].push_back(j);
        v[y[i]].clear(); 
    }
    for(int i=m-1;i>=0;i--)if(!s[i])dfs(i);

    for(int i=0;i<n;i++)cout<<r[i]<<' ';
}
