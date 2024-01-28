#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define ll long long

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[n + 1];
    ll d[n + 1][n + 1];
    FOR(i, 1, n) FOR(j, 1, n) d[i][j] = LLONG_MAX;
    FOR(i, 1, n) d[i][i] = 0;
    FOR(i, 1, m){
        ll a, b, w; cin >> a >> b >> w;
        adj[b].push_back(make_pair(a, w));
        d[a][b] = min(d[a][b], w);
    }
    
    // floyd-warshalls
    FOR(i, 1, n) FOR(j, 1, n) FOR(k, 1, n) if(d[i][k] != LLONG_MAX && d[k][j] != LLONG_MAX) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    ll mxm = pow(2, n) - 1, msk[n + 1][mxm + 1];
    FOR(i, 1, n) fill(msk[i], msk[i] + mxm + 1, LLONG_MAX);
    FOR(i, 1, n) msk[i][(int)(1 << (i - 1))] = 0; 
    FOR(m, 1, mxm) {
        FOR(i, 1, n) if(m & (1 << (i - 1)) && m ^ (1 << (i - 1))) {
            FOR(j, 1, n) if(i != j && m & (1 << (j - 1)) && msk[j][(int)(m ^ (1 << (i - 1)))] != LLONG_MAX) {
                if(d[i][j] != LLONG_MAX) msk[i][m] = min(msk[i][m], msk[j][(int)(m ^ (1 << (i - 1)))] + d[i][j]);
            }
        }
    }

    ll mn = LLONG_MAX;
    FOR(i, 1, n) mn = min(mn, msk[i][mxm]);

    if(mn == LLONG_MAX) cout << "No" << endl;
    else cout << mn << endl;
}
