#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 1000005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, m[MAXN], dp[MAXN][2];
vector<ll> adj[MAXN];
pair<ll, ll> r = {-1, -1};

void dfs(ll v, ll p){
    dp[v][0] = dp[v][1] = -1; 

    ll z1 = -1, z2 = -1, o1 = -1, o2 = -1;
    ll idz = -1, ido = -1;
    for(ll v2 : adj[v]) if(v2 != p) {
        dfs(v2, v);
        if(m[v] >= 3) continue;
        if(dp[v2][0] != -1){
            if(m[v] == 2){
                dp[v][1] = max(dp[v][1], dp[v2][0] + 1);
                if(r.first == -1 || r.first * dp[v][1] > 2 * r.second){
                    r = {2, dp[v][1]};
                }
            }else if(m[v] == 1){
                dp[v][0] = max(dp[v][0], dp[v2][0] + 1);
                if(r.first == -1 || r.first * dp[v][0] > r.second){
                    r = {1, dp[v][0]};
                }
            }

            if(dp[v2][0] > z1) {
                z2 = z1;
                z1 = dp[v2][0], idz = v2;
            }else if(dp[v2][0] > z2){
                z2 = dp[v2][0];
            }
        }
        if(dp[v2][1] != -1){
            if(m[v] == 1){
                dp[v][1] = max(dp[v][1], dp[v2][1] + 1);
                if(r.first == -1 || r.first * dp[v][1] > 2 * r.second){
                    r = {2, dp[v][1]};
                }
            }

            if(dp[v2][1] > o1) {
                o2 = o1;
                o1 = dp[v2][1], ido = v2;
            }else if(dp[v2][1] > o2){
                o2 = dp[v2][1];
            }
        }
    }

    if(m[v] == 1){
        // 2 on one side, 1 on the other -- MAY CONFLICT
        if(ido != idz){
            if((z1 != -1 && o1 != -1) && (r.first == -1 || r.first * (1 + z1 + o1) > 2 * r.second)){
                r = {2, 1 + z1 + o1};
            }
        }else{
            if((z1 != -1 && o2 != -1) && (r.first == -1 || r.first * (1 + z1 + o2) > 2 * r.second)){
                r = {2, 1 + z1 + o2};
            }
            if((z2 != -1 && o1 != -1) && (r.first == -1 || r.first * (1 + z2 + o1) > 2 * r.second)){
                r = {2, 1 + z2 + o1};
            }
        }

        // 1 on both sides -- NO CONFLICT
        if((z1 != -1 && z2 != -1) && (r.first == -1 || r.first * (1 + z1 + z2) > r.second)){
            r = {1, 1 + z1 + z2};
        }

        // start own dp[v][0]
        dp[v][0] = max(dp[v][0], 1ll);
    }

    if(m[v] == 2){
        // 1 on both sides -- NO CONFLICT
        if((z1 != -1 && z2 != -1) && (r.first == -1 || r.first * (1 + z1 + z2) > 2 * r.second)){
            r = {2, 1 + z1 + z2};
        }
        
        // start own dp[v][1]
        dp[v][1] = max(dp[v][1], 1ll);
    }

    if(m[v] >= 3){
        if(r.first == -1 || r.first > m[v] * r.second){
            r = {m[v], 1};
        }
    }
}

int main(){
    cin >> n;
    FOR(i, 1, n - 1) {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    FOR(i, 1, n) cin >> m[i];

    dfs(1, -1);
    if(r.first == 2 && r.second % 2 == 0) r.first /= 2, r.second /= 2;

    cout << r.first << "/" << r.second << endl;
}
