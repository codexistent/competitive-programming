#include "traffic.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 1000005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll r[MAXN], s = 0, cgd[MAXN];
vector<ll> adj[MAXN];
pair<ll, ll> ans;

void dfs(ll i, ll p = -1){
    for(ll i2 : adj[i]) if(i2 != p) {
        dfs(i2, i);
        r[i] = max(r[i], cgd[i2]);
        cgd[i] += cgd[i2];
    }
    r[i] = max(r[i], s - cgd[i]);
}

int LocateCentre(int N, int pp[], int S[], int D[]) {
    FOR(i, 0, N - 2) adj[S[i]].push_back(D[i]), adj[D[i]].push_back(S[i]);
    FOR(i, 0, N - 1) cgd[i] = pp[i], s += pp[i];
    dfs(0);

    ans = {LLONG_MAX, LLONG_MAX};
    FOR(i, 0, N - 1) ans = min(ans, {r[i], i});

    return ans.second;
}
