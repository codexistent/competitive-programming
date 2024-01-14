#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

int main(){
    string n;
    cin >> n;
    ll r = 0;
    FOR(s, 1, 9*14){
        ll dp[n.length() + 1][s + 1][s][2];
        FOR(d, 0, n.length()) FOR(i, 0, s) FOR(j, 0, s - 1) dp[d][i][j][0] = dp[d][i][j][1] = 0;
        dp[0][0][0][1] = 1;
        FOR(d, 0, n.length() - 1) FOR(i, 0, s) FOR(j, 0, s - 1) FOR(m, 0, 1) {
            FOR(d2, 0, 9) if(i + d2 <= s && !(m && d2 > n[d] - '0')) {
                dp[d + 1][i + d2][(j * 10 + d2) % s][m and n[d] - '0' == d2] += dp[d][i][j][m];
            }
        }

        r += dp[n.length()][s][0][0] + dp[n.length()][s][0][1];
    }
    
    cout << r << endl;
}
