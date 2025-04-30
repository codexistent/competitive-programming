#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(ll icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(ll icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second
#define MAXD 605
#define MAXN 205

ll w, h, dp[MAXD][MAXD], n;

int main(){
  cin >> w >> h;
  FOR(i, 0, w) FOR(j, 0, h) dp[i][j] = i * j;

  cin >> n;
  FOR(i, 1, n){
    ll a, b; cin >> a >> b;
    dp[a][b] = 0;
  }

  FOR(i, 1, w){
    FOR(j, 1, h){
      dp[i][j] = min({dp[i][j], dp[i][j - 1] + i, dp[i - 1][j] + j});

      FOR(i2, 1, i - 1) dp[i][j] = min(dp[i][j], dp[i2][j] + dp[i - i2][j]);
      FOR(j2, 1, j - 1) dp[i][j] = min(dp[i][j], dp[i][j2] + dp[i][j - j2]);
    }
  }

  cout << dp[w][h] << endl;
}
