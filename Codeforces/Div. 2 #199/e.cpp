#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define RFOR(ict, ist, ied) for(ll ict = ist; ict >= ied; ict--)
#define MAXN 100005
#define MXLOG 25

ll n, sqm, m, d[MAXN], jp[MAXN][MXLOG], dp[MAXN];
vector<ll> adj[MAXN];
bool c[MAXN], v[MAXN];

void dfs(ll i, ll p = -1){
    jp[i][0] = p;
    for(ll j = 1, jsz = 2; jsz <= d[i]; j++, jsz *= 2){
        jp[i][j] = jp[jp[i][j - 1]][j - 1];
    }
    
    for(ll i2 : adj[i]) if(i2 != p){
        d[i2] = d[i] + 1, dfs(i2, i);
    }
}
ll jmp(ll a, ll jsz){
    FOR(j, 0, MXLOG - 1) if(jsz & (1 << j)){
        a = jp[a][j];
    }
    return a;
}
ll lca(ll a, ll b){
    if(d[a] > d[b]) swap(a, b);
    b = jmp(b, d[b] - d[a]);

    if(a == b) return a;
    
    RFOR(j, MXLOG - 1, 0){
        if(jp[a][j] != jp[b][j]){
            a = jp[a][j], b = jp[b][j];
        }
    }
    return jp[a][0];
}
void bfs(){
    queue<ll> q;

    FOR(i, 1, n) {
        if(c[i]) q.push(i), dp[i] = 0;
        else dp[i] = LLONG_MAX;
        v[i] = false;
    }

    while(q.size()){
        ll qi = q.front(); q.pop();
        if(v[qi]) continue;
        v[qi] = true;

        for(ll i2 : adj[qi]) if(dp[i2] == LLONG_MAX){
            dp[i2] = dp[qi] + 1;
            q.push(i2);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    FOR(i, 0, MAXN - 1) FOR(j, 0, MXLOG - 1) jp[i][j] = -1;

    cin >> n >> m;
    FOR(i, 1, n - 1){
        ll a, b; cin >> a >> b;
        adj[a].push_back(b), adj[b].push_back(a);
    }
    sqm = sqrt(m);

    FOR(i, 1, n) c[i] = false;
    d[1] = 0, dfs(1);
    c[1] = true;

    vector<ll> sqc;
    FOR(mi, 0, m - 1){
        if(mi % sqm == 0){
            bfs();
            sqc.clear();
        }

        ll t, i; cin >> t >> i;
        if(t == 1){
            c[i] = true;
            sqc.push_back(i);
        }else{
            ll r = dp[i];
            for(ll i2 : sqc){
                ll lcai = lca(i, i2);
                r = min(r, d[i] + d[i2] - 2 * d[lcai]);
            }
            cout << r << endl;
        }
    }
}
