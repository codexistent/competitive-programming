#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MOD 1000000007

ll n, m, k;

ll fpow(ll b, ll e){
    if(e == 0) return 1ll;
    ll r = fpow(b, e / 2);
    return (r * r % MOD) * ((e % 2) ? b : 1ll) % MOD; 
}

ll inv(ll x){
    return fpow(x, MOD - 2);
}

// LESSON: CHECK WHAT DP IS DEPENDENT ON & IF CAN SIMPLIFY PROBLEM
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;
    while(t--) {
        cin >> n >> m >> k;
        FOR(i, 1, n) { ll x; cin >> x; }
        
        // sequence is not dependent must have at least n '1's
        // count complement (sequences with only 0...n-1 '1's)

        ll r = fpow(k, m), xCy = 1;
        FOR(i, 0, n - 1){
            r = (r - xCy * fpow(k - 1, m - i) % MOD + MOD) % MOD;
            xCy = xCy * ((m - i) * inv(i + 1) % MOD) % MOD;
        }

        cout << r << endl;
    }
}
