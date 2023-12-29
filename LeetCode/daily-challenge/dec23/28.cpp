// STATE: dp[position][k used][cur. character][ct 2 or 1 taken] = min run-length
// BASE CASE: dp[0][0][0][0] = 0;
// TRANSITION: -> dp[i][k][c][t] <= dp[(i - 1) % 2][k][any char][prev t] + (add according to prev t) <- dont delete character & start new seg(t = 1)
//                               <= dp[(i - 1) % 2][k][c][t - 1] <- dont delete character & build off prev seg
//                               <= dp[(i - 1) % 2][k - 1][c][t] <- delete character & build off prev seg

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.length();
        int dp[2][k + 1][26][n + 1], dp2[2][k + 1];
        for(int i = 0; i < 2; ++i) for(int ku = 0; ku <= k; ++ku) for(int c = 0; c < 26; c++) for(int t = 0; t <= n; ++t) dp[i][ku][c][t] = INT_MAX;
        for(int i = 0; i < 2; ++i) for(int ku = 0; ku <= k; ++ku) dp2[i][ku] = INT_MAX;
        dp[0][0][0][0] = dp2[0][0] = 0;

        for(int i = 1; i <= n; i++){
            for(int ku = 0; ku <= min(i, k); ++ku){
                for(int pc = 0; pc < 26; ++pc){ // start new seg.
                    dp[i % 2][ku][s[i - 1] - 'a'][1] = min(dp[i % 2][ku][s[i - 1] - 'a'][1], dp2[(i - 1) % 2][ku]);
                }
                for(int t = 0; t <= s.length(); ++t){
                    if(t != 0) dp[i % 2][ku][s[i - 1] - 'a'][t] = min(dp[i % 2][ku][s[i - 1] - 'a'][t], dp[(i - 1) % 2][ku][s[i - 1] - 'a'][t - 1]); // add to prev seg.
                    if(ku != 0){
                        for(int c = 0; c < 26; c++){
                            dp[i % 2][ku][c][t] = min(dp[i % 2][ku][c][t], dp[(i - 1) % 2][ku - 1][c][t]); // delete char. and carry dp
                        }
                    }
                }
            }
            for(int ku = 0; ku <= k; ++ku) {
                for(int c = 0; c < 26; c++) {
                    for(int t = 0; t <= n; ++t) {
                        if(dp[i % 2][ku][c][t] != INT_MAX) dp2[i % 2][ku] = min(dp2[i % 2][ku], dp[i % 2][ku][c][t] + ((t <= 1) ? t : (2 <= t && t <= 9) ? 2 : (t == 100) ? 4 : 3));
                        dp[((i - 1) % 2) % 2][ku][c][t] = INT_MAX;
                    }
                }
            }
            for(int ku = 0; ku <= k; ++ku) dp2[(i - 1) % 2][ku] = INT_MAX;
        }

        int R = INT_MAX;
        for(int ku = 0; ku <= k; ++ku) R = min(R, (int)dp2[n % 2][ku]);

        return R;
    }
};
