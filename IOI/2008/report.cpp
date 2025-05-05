#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ++ict)
#define RFOR(ict, ist, ied) for(int ict = ist; ict >= ied; --ict)
int MOD;

int n, dp[2][5][5][5][3];
string s;

int main() 
{
  cin >> n >> MOD >> s;
  FOR(i, 0, 1) FOR(j, -2, 2) FOR(k, -2, 2) FOR(l, -2, 2) FOR(m, 0, 2) dp[i][j + 2][k + 2][l + 2][m] = 0;
  
  dp[0][0 + 2][0 + 2][0 + 2][1] = 1;
  FOR(i, 0, n - 1){
    FOR(j, -2, 2) FOR(k, -2, 2) FOR(l, -2, 2) FOR(m, 0, 2) {
      if(dp[i % 2][j + 2][k + 2][l + 2][m] != 0){

        if(l != -2){
        // add L
          int m2 = (m == 1) ? ((s[i] == 'L') ? 1 : 0) : m;
          int l2 = l - 1, j2 = min(j, l2), k2 = max(k, l2);
          
          if(k2 - j2 <= 2){
            dp[(i + 1) % 2][j2 + 2][k2 + 2][l2 + 2][m2] = (dp[(i + 1) % 2][j2 + 2][k2 + 2][l2 + 2][m2] + dp[i % 2][j + 2][k + 2][l + 2][m]) % MOD;
          }
        }
        
        if(l != 2){
        // add P
          int m2 = (m == 1) ? ((s[i] == 'L') ? 2 : 1) : m;
          int l2 = l + 1, j2 = min(j, l2), k2 = max(k, l2);
          
          if(k2 - j2 <= 2){
            dp[(i + 1) % 2][j2 + 2][k2 + 2][l2 + 2][m2] = (dp[(i + 1) % 2][j2 + 2][k2 + 2][l2 + 2][m2] + dp[i % 2][j + 2][k + 2][l + 2][m]) % MOD;
          }
        }
        
        dp[i % 2][j + 2][k + 2][l + 2][m] = 0;
      }
    }
  }
  
  int r = 0;
  FOR(j, -2, 2) FOR(k, -2, 2) FOR(l, -2, 2) FOR(m, 0, 1) {
    r = (r + dp[n % 2][j + 2][k + 2][l + 2][m]) % MOD;
  }
  cout << r << endl;
}
