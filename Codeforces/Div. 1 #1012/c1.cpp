#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXL 5005
#define MAXN 105
#define MOD 1000000007
 
ll n, k, l, pb[MAXL][MAXN];
 
void upd_pb(ll li, ll l, ll r, ll updv){
  pb[li][l] = (pb[li][l] + updv) % MOD;
  pb[li][r + 1] = (pb[li][r + 1] - updv + MOD) % MOD;
}
ll fpow(ll b, ll e){
  if(e == 0) return 1;
  ll ret = fpow(b, e / 2);
  return ret * ret % MOD * ((e % 2) ? b : 1) % MOD;
}
ll inv(ll x){
  return fpow(x, MOD - 2);
}
 
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
    
  ll t; cin >> t;
  while(t--) {
      cin >> n >> l >> k;
      FOR(li, 0, l) FOR(i, 0, n + 1) pb[li][i] = 0ll;
      pb[0][n] = 1ll;
      
      FOR(li, 0, l){
        if(li != 0){
          FOR(i, 1, n) pb[li][i] = (pb[li][i] + pb[li][i - 1] + MOD) % MOD;
        }
        if(li != l){
          FOR(i, 1, n){
            ll sz = l - (li + 1) + 1, osz = l - (li + 1) + 1;
            if(sz >= n){
              upd_pb(li + 1, 1, n, pb[li][i] * inv(sz) % MOD * (sz / n) % MOD);
              sz %= n;
            }
    
            if(sz){
              if(i + 1 <= n) {
                upd_pb(li + 1, i + 1, min(i + sz, n), pb[li][i] * inv(osz) % MOD);
              }
              if(n < i + sz) {
                upd_pb(li + 1, 1, (i + sz) - n, pb[li][i] * inv(osz) % MOD);
              }
            }
          }
        }
      }
      
      FOR(i, 1, n) {
        ll ri = 0ll;
        FOR(li, 1, l) ri = (ri + pb[li][i]) % MOD;
        cout << ri << ' ';
      }
      cout << '\n';
  }
}
