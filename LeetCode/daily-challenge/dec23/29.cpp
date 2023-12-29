#define f first
#define s second
#define mp make_pair
#define FOR(i, a, b) for(int i = a; i <= b; i++)

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        pair<int, int> dp[2][d + 1][n + 1];
        FOR(i, 0, 1) FOR(j, 0, d) FOR(k, 0, n) dp[i][j][k].f = dp[i][j][k].s = INT_MAX;

        dp[0][0][0].f = 0, dp[0][0][0].s = INT_MAX;
        FOR(i, 1, n){
            FOR(j, 1, d){
                FOR(pi, 0, i - 1){
                    if(dp[(i - 1) % 2][j][pi] != mp(INT_MAX, INT_MAX)){
                        dp[i % 2][j][pi] = min(dp[i % 2][j][pi], mp(dp[(i - 1) % 2][j][pi].f - dp[(i - 1) % 2][j][pi].s + max(jobDifficulty[i - 1], dp[(i - 1) % 2][j][pi].s), 
                                                                 max(jobDifficulty[i - 1], dp[(i - 1) % 2][j][pi].s)));
                    }
                    if(dp[(i - 1) % 2][j - 1][pi] != mp(INT_MAX, INT_MAX)){
                        dp[i % 2][j][i] = min(dp[i % 2][j][i], mp(dp[(i - 1) % 2][j - 1][pi].f + jobDifficulty[i - 1], jobDifficulty[i - 1]));
                    }
                }
            }
            FOR(j, 0, d) FOR(k, 0, n) dp[(i - 1) % 2][j][k].f = dp[(i - 1) % 2][j][k].s = INT_MAX;
        }

        int R = INT_MAX;
        FOR(i, 1, n) R = min(R, dp[n % 2][d][i].f);

        return (R == INT_MAX) ? -1 : R;
    }
};
