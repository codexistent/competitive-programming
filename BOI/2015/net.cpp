#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 500005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
 
ll n;
pair<ll, ll> dp[MAXN]; 
vector<ll> adj[MAXN];
vector<pair<ll, ll>> cn[MAXN];
 
void dfs(ll v, ll p){
    if(adj[v].size() == 1 && adj[v][0] == p){
        dp[v] = {1, v};
        return;
    }
 
    dp[v] = {2, -1};
    for(ll v2 : adj[v]) if(p != v2){
        dfs(v2, v);
        if(dp[v].first == 2){
            swap(cn[v], cn[v2]), dp[v] = dp[v2];
            continue;
        }
 
        if(dp[v].first == 0){
            if(dp[v2].first == 0){
                pair<ll, ll> bk = cn[v].back(), bk2 = cn[v2].back();
                cn[v].pop_back(), cn[v2].pop_back();
 
                cn[v].push_back({bk.first, bk2.first});
                cn[v2].push_back({bk.second, bk2.second});
            }else{
                pair<ll, ll> bk = cn[v].back();
                cn[v].pop_back();
                
                cn[v].push_back({bk.first, dp[v2].second});
 
                dp[v] = {1, bk.second};
            }
        }else{
            if(dp[v2].first == 0){
                pair<ll, ll> bk = cn[v2].back();
                cn[v2].pop_back();
 
                cn[v2].push_back({bk.first, dp[v].second});
                dp[v].second = bk.second;
            }else{
                cn[v].push_back({dp[v].second, dp[v2].second});
                dp[v].first = 0;
            }
        }
 
        if(cn[v].size() < cn[v2].size()) swap(cn[v], cn[v2]);
    }
}
 
int main(){
    cin >> n;
    FOR(i, 1, n - 1){
        ll a, b; cin >> a >> b;
        adj[a].push_back(b), adj[b].push_back(a);
    }
 
    dfs(1, -1);
    
    ll r = dp[1].first + (adj[1].size() == 1 && dp[1].first == 0);
    FOR(i, 1, n) r += (ll)cn[i].size();
 
    cout << r << endl;
 
    bool x1 = (adj[1].size() == 1 && dp[1].first == 0);
    FOR(i, 1, n){
        for(pair<ll, ll> pi : cn[i]){
            if(x1) {
                cout << pi.first << " " << 1 << endl;
                cout << pi.second << " " << 1 << endl;
                x1 = false;
                continue;
            }
            cout << pi.first << " " << pi.second << endl;
        }
    }
    if(dp[1].first) cout << dp[1].second << " " << 1 << endl;
}
