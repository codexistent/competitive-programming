#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(ll icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(ll icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second
#define MAXQ 150005
#define MAXM 2005

ll q, m, k, f[MAXM], s[MAXM], dp[MAXQ][2];

int main(){
  cin >> q >> m >> k;
  FOR(i, 1, m) cin >> f[i];
  FOR(i, 1, k) cin >> s[i];

  FOR(j, 0, 1) FOR(i, 0, q)  dp[i][j] = -1;
  dp[0][0] = 0;
  
  pair<ll, ll> cr = {0, 0};
  FOR(fi, 0, m - 1) {
    FOR(qi, 0, q)  if(dp[qi][fi % 2] != -1){
      // use field fi
      if(qi + f[fi + 1] <= q) dp[qi + f[fi + 1]][(fi + 1) % 2] = max(dp[qi + f[fi + 1]][(fi + 1) % 2], dp[qi][fi % 2]);
      
      // don't use field fi
      dp[qi][(fi + 1) % 2] = max(dp[qi][(fi + 1) % 2], max(dp[qi][fi % 2], f[fi % 2]));
      
      cr = max(cr, {qi, dp[qi][fi % 2]});
      
      dp[qi][fi % 2] = -1;
    }
  }
  
  FOR(qi, 0, q) FOR(fi, 0, 1) if(dp[qi][fi] != -1) cr = max(cr, {qi, dp[qi][fi]});
  
  multiset<ll> ms;
  FOR(i, 1, k) ms.insert(s[i]);
  if(cr.sc) ms.insert(cr.second);

  ll qr = q - cr.fs, r = cr.fs;
  while(qr && ms.size()){
    ll lg = *ms.rbegin();
    ms.erase(ms.find(lg));

    r += min(lg, qr) - 1;
    qr -= min(lg, qr);
  }
  cout << r << endl;
}
