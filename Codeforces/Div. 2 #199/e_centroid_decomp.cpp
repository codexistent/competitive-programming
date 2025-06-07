#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define MAXN 100005
#define MXLOG 55

int n, m, dp[MAXN], ct[MAXN], cp[MAXN][MXLOG], cd[MAXN][MXLOG], csz[MAXN];
vector<int> adj[MAXN];
bool rmv[MAXN];

// LESSON: FOR CENTROID DECOMP, FIND SUBTREE SZ'S RIGHT BEFORE UPDATE
void build_csz(int i, int p = -1){
    csz[i] = 1;
    for(int i2 : adj[i]) if(i2 != p && !rmv[i]) {
        build_csz(i2, i);
        csz[i] += csz[i2];
    }
}
int find_cent(int i, int sz, int p = -1){
    for(int i2 : adj[i]) if(i2 != p && !rmv[i2]) {
        if(csz[i2] * 2 > sz) return find_cent(i2, sz, i); // WRONG
    }
    return i;
}
void build_dist(int i, int p, int cent, int cdist){
    cd[i][ct[i]] = cdist;
    cp[i][ct[i]] = cent;
    ct[i]++;
    if(ct[i] > 50) exit(0);

    for(int i2 : adj[i]) if(i2 != p && !rmv[i2]) {
        build_dist(i2, i, cent, cdist + 1);
    }
}
void build_centd(int i){
    build_csz(i);
    int cent = find_cent(i, csz[i]);

    for(int i2 : adj[cent]) if(!rmv[i2]) build_dist(i2, cent, cent, 1); 

    rmv[cent] = true;
    for(int i2 : adj[cent]) if(!rmv[i2]) build_centd(i2);
}

void paint(int i){
    dp[i] = 0;
    FOR(pi, 0, ct[i] - 1){
        dp[cp[i][pi]] = min(dp[cp[i][pi]], cd[i][pi]);
    }
}
int query(int i){
    int r = dp[i];
    FOR(pi, 0, ct[i] - 1) if(dp[cp[i][pi]] != INT_MAX){
        r = min(r, cd[i][pi] + dp[cp[i][pi]]);
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    FOR(i, 0, MAXN - 1) rmv[i] = false, dp[i] = INT_MAX, ct[i] = 0ll;

    cin >> n >> m;
    FOR(i, 1, n - 1){
        int a, b; cin >> a >> b;
        adj[a].push_back(b), adj[b].push_back(a);
    }

    build_centd(1);

    paint(1);
    FOR(qi, 1, m){
        int t, i; cin >> t >> i;
        if(t == 1){
            paint(i);
        }else{
            cout << query(i) << '\n';
        }
    }
}
