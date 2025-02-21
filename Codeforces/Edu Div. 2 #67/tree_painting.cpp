#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define MAXN 200005
#define FOR(icounter, istart, iend) for(ll icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(ll icounter = istart; icounter >= iend; icounter--)
#define fs first
#define sc second

ll n, sz[MAXN], r[MAXN], R = 0;
vector<ll> adj[MAXN];

void dfs1(ll i, ll p){
    sz[i] = 1, r[i] = 0;
    for(ll i2 : adj[i]) if(i2 != p) {
        dfs1(i2, i);
        sz[i] += sz[i2];
        r[i] += r[i2];
    }
    r[i] += sz[i];
}

void dfs2(ll i, ll p){
    if(i != p) r[i] = r[p] + n - 2 * sz[i];

    R = max(r[i], R);

    for(ll i2 : adj[i]) if(i2 != p){
        dfs2(i2, i);
    }
}

int main(){
    cin >> n;
    FOR(i, 1, n - 1){
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    cout << R << endl;
}
