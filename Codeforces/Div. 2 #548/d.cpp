// MATH, PIE
// LESSON: YOU CAN DP OVER MANY THINGS NOT JUST INDICIES. YOU CAN DP OVER THINGS THERE ARE ONLY LOG OR SQRT OF SUCH AS GCD
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 100005
#define MOD 1000000007
 
ll n, dp[MAXN]; // dp[i] = expected additional steps when gcd of #s = 1
vector<ll> f[MAXN], pf[MAXN];
bool p[MAXN];
 
ll oc(ll x, ll fi){ // return ct of #s from i = 1...n such that gcd(x, i) = fi
    ll ret = n / fi;
 
    // fi can't be multiplied w/ any other factors of x
    ll pfn = pf[x / fi].size();
    ll mxmsk = pow(2, (ll)pf[x / fi].size()) - 1;
    FOR(m, 1, mxmsk){
        ll ct = 0, dv = 1;
        FOR(pv, 0, pfn - 1) if(m & (1 << pv)) dv *= pf[x / fi][pv], ct++;
 
        if(ct % 2){
            ret -= (n / fi) / dv;
        }else{
            ret += (n / fi) / dv;
        }
    }
 
    return ret;
}
 
ll fpow(ll b, ll e){
    if(e == 0) return 1;
    ll r = fpow(b, e / 2);
    return ((r * r) % MOD * (e % 2 ? b : 1)) % MOD;
}
ll inv(ll x) { return fpow(x, MOD - 2); }
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    FOR(i, 1, MAXN - 1) p[i] = true;
    p[1] = false;
    FOR(i, 2, MAXN - 1) if(p[i]) for(ll j = i * 2; j <= MAXN - 1; j += i) p[j] = false;
 
    cin >> n;
    FOR(i, 1, n) {
        dp[i] = 0;
        FOR(j, 1, sqrt(i)) if(i % j == 0){
            f[i].push_back(j);
            if(p[j]) pf[i].push_back(j);
 
            if(i / j != j) {
                f[i].push_back(i / j);
                if(p[i / j]) pf[i].push_back(i / j);
            }
        }
    }
 
    FOR(i, 2, n){
        for(ll fi : f[i]) if(fi != i) dp[i] += dp[fi] * oc(i, fi) % MOD, dp[i] %= MOD;
        dp[i] *= inv(n), dp[i] %= MOD;
 
        dp[i] += 1;
        dp[i] *= n * inv(n - oc(i, i)) % MOD, dp[i] %= MOD;
    }
 
    ll r = 1ll;
    FOR(i, 1, n){
        r += dp[i] * inv(n) % MOD, r %= MOD;
    }
    cout << r << endl;
}
