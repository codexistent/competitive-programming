#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second
 
int n, ec[MAXN];
string st[MAXN], nx[MAXN];
map<string, int> idx;
set<int> adj[MAXN];
bool d[MAXN], v[MAXN];
 
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> n;
    FOR(i, 1, n) ec[i] = 0;
    FOR(i, 1, n){
        cin >> st[i];
        idx.insert({st[i], i});
        cin >> nx[i];
    }
 
    if(n % 2) {
        cout << -1 << endl;
        return 0;
    }
 
    int r = 0;
    FOR(i, 1, n){
        d[i] = (idx[nx[idx[nx[i]]]] == i && idx[nx[i]] != i);
    }
 
    FOR(i, 1, n){
        if(i == idx[nx[i]] || d[i] || d[idx[nx[i]]]) continue;
        ec[i]++, ec[idx[nx[i]]]++;
    }
 
    FOR(i, 1, n){
        if(i == idx[nx[i]] || d[i] || d[idx[nx[i]]]) continue;
        adj[i].insert(idx[nx[i]]);
        adj[idx[nx[i]]].insert(i);
    }
 
    set<pair<int, int>> se;
    FOR(i, 1, n) if(!d[i]) se.insert({ec[i], i});
    
    FOR(i, 1, n) v[i] = false;
    while(se.size()){
        auto si = *se.begin();
        se.erase(se.begin());
        v[si.s] = true;
 
        if(si.f == 0){
            r++;
        }else{
            int j = 0, jmn = INT_MAX;
            for(int i : adj[si.s]){
                if(jmn > ec[i]) j = i, jmn = ec[i];
            }
            r++;
 
            se.erase({jmn, j});
            v[j] = true;

            for(int j2 : adj[j]) if(!v[j2]) {
                se.erase({ec[j2], j2});
                adj[j2].erase(j), ec[j2]--;
                se.insert({ec[j2], j2});
            }
        }
 
        for(int i2 : adj[si.s]) if(!v[i2]) {
            se.erase({ec[i2], i2});
            adj[i2].erase(si.s), ec[i2]--;
            se.insert({ec[i2], i2});
        }
    }

 
    cout << r << "\n";
}
