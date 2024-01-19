#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define mp make_pair

void solve(){
    int n, x;
    cin >> n >> x;
    int dp[n + 1][n + 1][x + 1], mn[n + 1][n + 1][x + 1], a[n + 1];
    FOR(i, 0, n) FOR(j, 0, n) FOR(k, 0, x) dp[i][j][k] = mn[i][j][k] = n;
    FOR(i, 1, n) {
        cin >> a[i];
        dp[i][i][a[i]] = 0;
        FOR(c, 1, x) if (c != a[i]) mn[i][i][c] = 0;
    }

    FOR(l, 2, n) for(int i = 1, j = l; j <= n; i++, j++){
        FOR(c, 1, x){
            FOR(k, i, j - 1) {
                dp[i][j][c] = min(dp[i][j][c], dp[i][k][c] + dp[k + 1][j][c]);
                dp[i][j][c] = min(dp[i][j][c], mn[i][k][c] + dp[k + 1][j][c] + 1);
                dp[i][j][c] = min(dp[i][j][c], dp[i][k][c] + mn[k + 1][j][c] + 1);
                mn[i][j][c] = min(mn[i][j][c], mn[i][k][c] + mn[k + 1][j][c]);
            }
        }

        FOR(c, 1, x) FOR(c2, 1, x) if(c != c2) mn[i][j][c] = min(mn[i][j][c], dp[i][j][c2]);
        
        FOR(c, 1, x) dp[i][j][c] = min(dp[i][j][c], mn[i][j][c] + 1);    

    }

    int r = n;
    FOR(c, 1, x) r = min(r, dp[1][n][c]);
    cout << r << endl;
}

int main() {
    int t;
    cin >> t;
    FOR(i, 1, t) solve();
}
