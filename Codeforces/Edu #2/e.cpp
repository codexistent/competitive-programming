#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define MAXN 100005
#define fs first 
#define sc second
 
ll r[MAXN];
int n, d[MAXN], c[MAXN];
vector<int> adj[MAXN];
map<int, int> mp[MAXN];
 
void dfs(int i, int p = -1){ // LESSON: PASSING PARAMETERS TAKES DEEP COPY
    d[i] = 1ll; r[i] = c[i];
 
    mp[i].insert({c[i], 1});
    for(int i2 : adj[i]) if(i2 != p){
        dfs(i2, i);
        ll ri2 = r[i2];
 
        if(mp[i].size() < mp[i2].size()) swap(mp[i], mp[i2]), swap(d[i], d[i2]), swap(r[i], r[i2]);
        
        for(auto mp2i : mp[i2]) {
            if(mp[i].find(mp2i.fs) == mp[i].end()){
                mp[i].insert(mp2i);
            }else{
                mp[i][mp2i.fs] += mp2i.sc;
            }
            
            if(mp[i][mp2i.fs] > d[i]){
                d[i] = mp[i][mp2i.fs];
                r[i] = 0;
            }
            r[i] += (mp[i][mp2i.fs] == d[i]) * mp2i.fs;
        }

        r[i2] = ri2;
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    FOR(i, 1, n) cin >> c[i];
 
    FOR(i, 1, n - 1){
        int a, b; cin >> a >> b;
        adj[a].push_back(b), adj[b].push_back(a);
    }
 
    dfs(1);
 
    FOR(i, 1, n) cout << r[i] << " ";
}
