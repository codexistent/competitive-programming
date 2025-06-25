#include <bits/stdc++.h>
using namespace std;
#define MAXN 500005
#define MOD 1000000007
#define ll long long 
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
 
ll w, h, fact[MAXN], nCk[715][715];

ll fpow(ll b, ll e) {
  if(e == 0) return 1ll;
  ll x = fpow(b, e / 2);
  return x * x % MOD * (1ll + (b - 1) * (e % 2)) % MOD;
}
 
ll inv(ll x){
  return fpow(x, MOD - 2);
}
 
ll nck(ll n, ll k){
  return fact[n] * inv(fact[n - k]) % MOD * inv(fact[k]) % MOD;
}

// VERY CLOSE TO TLEing
// LESSON: DON'T GET STUCK ON ONE PATH OF THINKING
// LESSON: PIE :D
int main(){
  
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  fact[0] = 1ll;
  FOR(i, 1, MAXN - 1) fact[i] = fact[i - 1] * i % MOD;
  FOR(i, 0, 710) FOR(j, 0, 710) nCk[i][j] = nck(i, j);
  
  cin >> w >> h;
  
  if(w < h || w <= 707){
    vector<ll> all(w + 1, 0ll), dp[2] = {vector<ll>(w + 1, 0ll), vector<ll>(w + 1, 0ll)};
    all[0] = all[1] = 1ll;
    FOR(i, 2, w) all[i] = (all[i - 1] + all[i - 2]) % MOD;
    
    dp[1][0] = dp[1][1] = 1ll;
    FOR(i, 2, w){
      all[i] = fpow(all[i], h);
      
      FOR(j, 1, i - 1) dp[0][i] = (dp[0][i] + all[j] * dp[1][i - j] % MOD) % MOD;
      dp[1][i] = (all[i] - dp[0][i] + MOD) % MOD;
    }
    
    cout << dp[1][w] << endl;
  }else{  // h >= sqrt(500005) = 710
    vector<vector<int>> dp(w + 1, vector<int>(h + 1, 0));
 
    dp[0][0] = 1;
    FOR(i, 1, w){
      FOR(j, 0, h){
        if(i != w && !j) continue;
        FOR(prvj, 0, h - j){
          ll sm = dp[i - 1][prvj] * nCk[h - prvj][j];
          if(sm >= MOD) sm %= MOD;
          
          dp[i][j] = (int)((dp[i][j] + (ll)sm) % MOD);
        }
      }
    }
    
    cout << dp[w][0] << '\n';
  }
}
