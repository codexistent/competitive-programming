#include <bits/stdc++.h>
using namespace std;
#define MAXN 5005
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int n, dp[3][MAXN];
string s;

int main(){
    cin >> n >> s;
    FOR(i, 1, n) dp[0][i] = dp[1][i] = 0, dp[2][i] = MAXN; 
    
    FOR(ln, 2, n){
        FOR(i, 1, n - ln + 1) dp[2][i] = MAXN; 
        for(int i = 1, j = ln; j <= n; i++, j++){
            // expand one left
            dp[2][i] = min(dp[2][i], dp[1][i + 1] + 1);

            // expand one right
            dp[2][i] = min(dp[2][i], dp[1][i] + 1);

            // expand both left and right
            dp[2][i] = min(dp[2][i], dp[0][i + 1] + 2 * (s[i - 1] != s[j - 1]));
        }
        swap(dp[0], dp[1]), swap(dp[1], dp[2]);
    }

    cout << dp[1][1] << endl;
}
