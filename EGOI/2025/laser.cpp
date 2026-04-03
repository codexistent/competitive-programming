#include <bits/stdc++.h>
using namespace std;

void ann(){
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    vector<int>deg(n),xors(n);
    for(int i=1,x,y;i<=n-1;i++){
        cin>>x>>y,deg[x]++,deg[y]++,xors[x]^=y,xors[y]^=x;
        g[x].emplace_back(y),g[y].emplace_back(x);
    }

    list<int>todo; // leaves to process
    vector<vector<int>>lf(n);
    for(int i=0;i<n;i++)if(deg[i]==1)lf[xors[i]].push_back(i);

    auto cut = [&](int p,int i){
        cout<<i<<endl,deg[p]--,deg[i]--,xors[p]^=i,xors[i]^=p;
        if(deg[p]==1){
            todo.push_back(p),lf[xors[p]].push_back(p);
        }
    };
    auto trim = [&](int p){
        for(auto i:lf[p])if(deg[i])cut(p,i);
        lf[p].clear();
    };

    vector<array<int,2>>gr,ls;
    for(int p=0;p<n;p++)if(lf[p].size()){
        int i=lf[p][0];
        if(p<i)gr.push_back({p,i});
        else ls.push_back({i,p});
    }
    sort(begin(gr),end(gr)),sort(begin(ls),end(ls));
    
    bool bit=(ls.empty() || (gr.size() && gr.back()>ls[0]));
    cout<<(int)bit<<endl;
    if(bit)for(auto [p,i]:gr)trim(p);
    for(auto [i,p]:ls)trim(p);
    if(!bit)for(auto [p,i]:gr)trim(p);

    for(int i:todo)if(deg[i])trim(xors[i]);
}

void kath(){
    int n,t=1;
    bool bit;
    cin>>n>>bit;
    vector<int>v(n);
    array<int,2>llf={-1,-1};
    for(int i=1,a,b;i<=n-1;i++){
        cin>>a>>b;
        bool r=(v[a]==t || (v[a]<v[b] && v[b]<t));
        if(!v[a]&&!v[b]){
            array<int,2>arr={a,b};
            if(arr<llf)bit=!bit;
            llf=arr,r=bit;
        }
        v[a]=v[b]=++t;
        cout<<(r?b:a)<<endl;
    }
}

main(){
    int p; cin>>p;
    if(p==1)ann();else kath();
}
