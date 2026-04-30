#include "nile.h"
#include <bits/stdc++.h>
using namespace std;
const long long N=1e5+5,M=1e5+5;

long long n, m, sz[N], p[N], dq[N], sm[N], ri;
array<long long,2> q[M], rg[N], f[N], dp[N];
priority_queue<array<long long,2>, vector<array<long long,2>>, greater<array<long long,2>>> q2, q3;

long long find(long long x){ return (p[x]==x) ? p[x] : (p[x] = find(p[x])); }
void onion(long long a,long long b){
    a = find(a), b = find(b);
    if(a == b) return;

    if(rg[a][1] > rg[b][1]) swap(a,b);
    if(rg[a][0] < rg[a][1] && rg[a][1] < rg[b][1]) q3.push({f[rg[a][1]+1][0]-f[rg[a][1]-1][0], rg[a][1]});
    if(rg[a][0] < rg[b][0] && rg[b][0] < rg[b][1]) q3.push({f[rg[b][0]+1][0]-f[rg[b][0]-1][0], rg[b][0]});
    
    if(sz[a] < sz[b]) swap(a, b);
    ri -= sm[a]-(sz[a]%2)*max({dq[a],dp[a][rg[a][0]%2]});
    ri -= sm[b]-(sz[b]%2)*max({dq[b],dp[b][rg[b][0]%2]});
    sz[a]+=sz[b],dq[a]=max(dq[a],dq[b]),p[a]=p[b]=a,sm[a]+=sm[b];
    dp[a]={max(dp[a][0],dp[b][0]),max(dp[a][1],dp[b][1])};

    rg[a]={min(rg[a][0],rg[b][0]),max(rg[a][1],rg[b][1])};
    ri += sm[a]-(sz[a]%2)*max({dq[a],dp[a][rg[a][0]%2]});
}
void upd(long long x){
    long long y=find(x);
    ri -= sm[y]-(sz[y]%2)*max({dq[y],dp[y][rg[y][0]%2]});
    dq[y]=max(dq[y],f[x][1]);
    ri += sm[y]-(sz[y]%2)*max({dq[y],dp[y][rg[y][0]%2]});
}

std::vector<long long> calculate_costs(std::vector<int> W, std::vector<int> A, 
                                       std::vector<int> B, std::vector<int> E) {
    n=W.size(), m=E.size(), ri=0;
    for(int i=0;i<n;i++) f[i]={W[i],B[i]-A[i]}, ri+=A[i];
    sort(f,f+n);

    for(int i=0;i<n;i++){
        sz[i]=1, p[i]=i, dq[i]=LLONG_MIN, sm[i]=f[i][1], rg[i]={i,i}, dp[i]={LLONG_MIN, LLONG_MIN};
        dp[i][i%2]=f[i][1];
    }
    for(int i=0;i<m;i++) q[i]={E[i],i};
    sort(q,q+m);
    for(int i=0;i<n-1;i++) q2.push({f[i+1][0]-f[i][0],i});

    vector<long long> r(m);
    for(int i=0;i<m;i++){
        auto qi=q[i];
        while(q2.size() && q2.top()[0]<=qi[0])assert(q2.top()[0]>=0),onion(q2.top()[1],q2.top()[1]+1),q2.pop();
        while(q3.size() && q3.top()[0]<=qi[0])assert(q3.top()[0]>=0),upd(q3.top()[1]),q3.pop();

        r[qi[1]]=ri;
    }

    while(q2.size())q2.pop();
    while(q3.size())q3.pop();
    return r;
}
