#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;

int n,m,d[N],rd[N],ch[N];
vector<int>e[N],re[N];
bool v[N];

main(){
    cin>>n>>m,fill(d,d+n,1e9),fill(ch,ch+n,1e9),fill(rd,rd+n,1e9);
    for(int i=1,a,b;i<=m;i++)cin>>a>>b,e[a].push_back(b),re[b].push_back(a);

    queue<int>q;
    q.push(0),rd[0]=0;
    while(q.size()){
        int i=q.front();q.pop();
        if(v[i])continue; v[i]=true;
        for(auto i2:e[i])if(!v[i2]&&rd[i2]>rd[i]+1){
            rd[i2]=rd[i]+1,q.push(i2);
        }
    }

    priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>>pq;
    fill(v,v+n,false),pq.push({d[n-1]=0,n-1});
    while(pq.size()){
        int i=pq.top()[1]; pq.pop();
        if(v[i])continue;v[i]=true;

        for(int i2:re[i])if(!v[i2]&&d[i]<ch[i2]){
            ch[i2]=d[i],d[i2]=max(rd[i2],1+ch[i2]);
            pq.push({max(rd[i2],1+ch[i2]),i2});
        }
    }

    for(int i=0;i<n-1;i++)cout<<d[i]<<' ';
}
