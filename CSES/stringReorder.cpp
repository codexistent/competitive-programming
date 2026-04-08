#include<bits/stdc++.h>
using namespace std;
#define int long long 

string s;
map<char,int>mp;
set<pair<int,char>>st;
vector<char>r;

void go(char c){
    st.erase({mp[c],-c}),mp[c]--;
    if(mp[c]) st.insert({mp[c],-c}); else mp.erase(c);
    r.push_back(c);
}

void takesm(){
  if(mp.size()>=2&&r.size()&&mp.begin()->first==r.back()){
    auto mpi=*mp.begin(); mp.erase(mpi.first);
    go(mp.begin()->first);
    mp.insert(mpi);
    return;
  }
  go(mp.begin()->first);
}

main(){
    cin>>s;
    for(char c:s)mp[c]++;
    sort(begin(s),end(s));

    for(auto mpi:mp)st.insert({mpi.second,-mpi.first});

    int n=s.length();
    while(n--){
        n++;
        if(n%2){
          if(st.size()>=2&&r.size()&&-(*st.rbegin()).second==r.back()){
              auto sti=*st.rbegin(); st.erase(sti);
              if((*st.rbegin()).first==(n+1)/2)go(-(*st.rbegin()).second);
              else takesm();
              st.insert(sti);
          }else if(st.size()&&(*st.rbegin()).first==(n+1)/2){
              go(-(*st.rbegin()).second);
          }else takesm();
        }else takesm();
        n--;
    }

    for(int i=1;i<r.size();i++)if(r[i-1]==r[i])return cout<<"-1\n",0;
    for(char c:r)cout<<c;
}
