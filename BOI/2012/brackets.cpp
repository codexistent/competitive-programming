#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define MOD 1000000009
#define MAXN 30005

ll n, dp[2][MAXN];
string s;

int main(){
    cin.tie(0); 
    ios_base::sync_with_stdio(0);

    cin >> n >> s;
    FOR(i, 0, n - 1) dp[1][i] = 0;
    dp[1][1] = 1;

    FOR(i, 1, n - 1){
        FOR(j, 0, n - 1) dp[(i + 1) % 2][j] = 0;
        FOR(j, 0, n - 1) if(dp[i % 2][j]) {
            if(s[i] == '('){
                dp[(i + 1) % 2][j + 1] = (dp[(i + 1) % 2][j + 1] + dp[i % 2][j]) % MOD;
            }
            if(j >= 0){
                dp[(i + 1) % 2][j - 1] = (dp[(i + 1) % 2][j - 1] + dp[i % 2][j]) % MOD;
            } 
        }
    }

    cout << dp[n % 2][0] << endl;
}
