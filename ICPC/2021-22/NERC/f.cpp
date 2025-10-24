#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define RFOR(ict, ist, ied) for(ll ict = ist; ict >= ied; ict--)
const ll MAXN = 5005;
const ll MOD = 998244353;

// dp[idx][open positions][last odd same type] = # ways
// - at idx i, two decisions:
//      - add lvl i (odd)? (only if last odd not same type)
//          - insert one more open position but turn on last odd same type
//      - OR insert i to lvl (even)
//          - fill last open position? and decrement open positions?
// BASE: dp[0][0][0] = 1;
// 

// dp[type][open positions]
// - for type i, two decisions:
//      - add lvl i, insert (# type - 1)
//      - add none,  insert (# type)

ll fac[MAXN];
void init(){
    fac[0] = 1ll;
    FOR(i, 1, MAXN - 1) fac[i] = fac[i - 1] * i % MOD;
}
ll fpow(ll b, ll e){
    if(e == 0ll) return 1ll;
    ll e2 = fpow(b, e / 2);
    return e2 * e2 % MOD * ((e % 2) ? b : 1) % MOD;
}
ll inv(ll x){
    return fpow(x, MOD - 2);
}
ll choose(ll n, ll k){
    if(k == 0ll) return 1ll;
    return fac[n] * inv(fac[n - k] * fac[k] % MOD) % MOD;
}

void solve(){
    ll n; cin >> n;
    vector<ll> tp(n + 1, 0);
    FOR(i, 1, n){
        ll x; cin >> x;
        tp[x]++;
    }

    vector<ll> pfx(n + 1, 0);
    FOR(i, 1, n) pfx[i] = pfx[i - 1] + tp[i];

    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));
    dp[n + 1][0] = 1;
    RFOR(i, n + 1, 2){
        FOR(j, 0, n) if(dp[i][j]){
            if(j == pfx[i - 1]){
                dp[i - 1][j - tp[i - 1]] += dp[i][j] * choose(j, tp[i - 1]) % MOD, dp[i + 1][j - tp[i - 1]] %= MOD;
            }else{
                if(tp[i - 1] == 1){
                    dp[i - 1][j + 1] += dp[i][j], dp[i - 1][j + 1] %= MOD;
                }else if(tp[i - 1] > 1 && tp[i - 1] - 1 <= j - 1){
                    dp[i - 1][j - (tp[i - 1] - 1) + 1] += dp[i][j] * choose(j - 1, tp[i - 1] - 1) % MOD, dp[i - 1][j - (tp[i - 1] - 1) + 1] %= MOD;
                }

                if(tp[i - 1] == 0 || tp[i - 1] <= j - 1){
                    dp[i - 1][j - tp[i - 1]] += dp[i][j] * choose(j - 1, tp[i - 1]) % MOD, dp[i - 1][j - tp[i - 1]] % MOD;
                }
            }
        }
    }

    cout << dp[1][0] << endl;
}

int main(){
    init();

    ll t; cin >> t;
    while(t--) solve();
}
