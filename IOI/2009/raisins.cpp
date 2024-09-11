#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define MAXD 55
#define f first
#define s second

ll n, m, r[MAXD][MAXD], dp[MAXD][MAXD][MAXD][MAXD], R = LONG_LONG_MAX;

int main(){
    cin >> n >> m;
    FOR(i, 0, MAXD - 1) FOR(j, 0, MAXD - 1) {
        r[i][j] = 0;
        FOR(i2, 0, MAXD - 1) FOR(j2, 0, MAXD - 1) dp[i][j][i2][j2] = LLONG_MAX;
    }
    FOR(i, 1, n) FOR(j, 1, m) {
        cin >> r[i][j];
        r[i][j] += r[i - 1][j] + r[i][j - 1] - r[i - 1][j - 1];
        dp[i][j][i][j] = 0;
    }
    
    FOR(h, 1, n) FOR(w, 1, m){
        if(h == w && h == 1) continue;
        FOR(bl_h, 1, n - h + 1) FOR(bl_w, 1, m - w + 1) {
            pair<ll, ll> bl = {bl_h, bl_w}, tr = {bl_h + h - 1, bl_w + w - 1};
            ll cr = r[tr.f][tr.s] - r[tr.f][bl.s - 1] - r[bl.f - 1][tr.second] + r[bl.f - 1][bl.s - 1];
            // horizontal cut
            FOR(i, 1, h - 1){
                dp[bl.f][bl.s][tr.f][tr.s] = min(dp[bl.f][bl.s][tr.f][tr.s], cr + dp[bl.f][bl.s][bl.f + i - 1][tr.s] + dp[bl.f + i][bl.s][tr.f][tr.s]);
            }

            // vertical cut
            FOR(i, 1, w - 1){
                dp[bl.f][bl.s][tr.f][tr.s] = min(dp[bl.f][bl.s][tr.f][tr.s], cr + dp[bl.f][bl.s][tr.f][bl.s + i - 1] + dp[bl.f][bl.s + i][tr.f][tr.s]);
            }
        }
    }

    cout << dp[1][1][n][m] << endl;
}
