#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(ll icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(ll icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second
#define MAXN 20005

int n, p[MAXN][2], dp[2][2][2005];

int main(){
    cin >> n;
    FOR(i, 1, n) {
        cin >> p[i][0] >> p[i][1];
        p[i][0] += 1000, p[i][1] += 1000;
    }

    FOR(i, 0, 1) FOR(t, 0, 1) FOR(j, 0, 2000) dp[i][t][j] = INT_MAX;

    dp[1][0][1000] = abs(1000 - p[1][0]), dp[1][1][1000] = abs(1000 - p[1][1]);
    FOR(i, 1, n - 1) {
      FOR(t, 0, 1) FOR(j, 0, 2000) if(dp[i % 2][t][j] != INT_MAX){
        // go into t next
        dp[(i + 1) % 2][t][j] = min(dp[(i + 1) % 2][t][j], dp[i % 2][t][j] + (int)abs(p[i + 1][t] - p[i][t]));

        // go into !t next
        dp[(i + 1) % 2][!t][p[i][t]] = min(dp[(i + 1) % 2][!t][p[i][t]], dp[i % 2][t][j] + (int)abs(j - p[i + 1][!t]));
        
        dp[i % 2][t][j] = INT_MAX;
      }
    }

    int r = INT_MAX;
    FOR(t, 0, 1) FOR(j, 0, 2000) r = min(r, dp[n % 2][t][j]);
    cout << r << endl;
}
