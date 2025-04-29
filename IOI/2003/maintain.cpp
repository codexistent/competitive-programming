#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(ll icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(ll icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second
#define MAXN 205

ll n, w, adj[MAXN][MAXN];
ll k[MAXN];
bool active[MAXN];

ll prims_mst(){
    ll wn = 0;
    FOR(i, 1, n) k[i] = LLONG_MAX, active[i] = false;

    k[1] = 0;
    FOR(i, 1, n){
        pair<ll, ll> kv = {LLONG_MAX, LLONG_MAX};
        FOR(j, 1, n) if(!active[j] && k[j] != LLONG_MAX) kv = min(kv, {k[j], j});
        if(kv.fs == LLONG_MAX) return -1;
        
        ll vi = kv.sc;
        
        wn += k[vi];
        active[vi] = true;
        FOR(j, 1, n) if(adj[vi][j] != LLONG_MAX && !active[j]){
            k[j] = min(k[j], adj[vi][j]);
        }
    }
    return wn;
}

int main(){
    cin >> n >> w;
    FOR(i, 1, n) FOR(j, 1, n) adj[i][j] = LLONG_MAX;
    FOR(i, 1, w){
        ll a, b, w; cin >> a >> b >> w;
        adj[a][b] = min(adj[a][b], w);
        adj[b][a] = min(adj[b][a], w);
        
        cout << prims_mst() << endl;
    }
}
