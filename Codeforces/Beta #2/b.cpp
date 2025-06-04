#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define fs first 
#define sc second 
#define MAXN 1005

int n, gd[MAXN][MAXN];
pair<int, bool> dp[MAXN][MAXN];

int logx_b(int x, int b){
    int r = 0;
    while(x >= b && b * (int)(x / b) == x){
        r++;
        x /= b;
    }
    return r;
}

tuple<int, vector<bool>> solve(int p){
    FOR(i, 0, n) FOR(j, 0, n) dp[i][j] = {INT_MAX, true};

    dp[1][1] = {logx_b(gd[1][1], p), false};
    FOR(i, 1, n){
        FOR(j, 1, n) if(dp[i][j].fs != INT_MAX){
            if(i + 1 <= n){
                dp[i + 1][j] = min(dp[i + 1][j], {dp[i][j].fs + logx_b(gd[i + 1][j], p), false});
            }
            if(j + 1 <= n){
                dp[i][j + 1] = min(dp[i][j + 1], {dp[i][j].fs + logx_b(gd[i][j + 1], p), true});
            }
        }
    }

    vector<bool> dir;
    int i = n, j = n;
    while(!(i == 1 && j == 1)){
        dir.push_back(dp[i][j].sc);
        if(!dp[i][j].sc){
            i--;
        }else{
            j--;
        }
    }
    reverse(begin(dir), end(dir));

    return {dp[n][n].fs, dir};
}

int main(){
    cin >> n;
    int ct2, ct5, ct0 = INT_MAX;
    pair<int, int> tr0;
    vector<bool> dir2, dir5;

    FOR(i, 1, n) FOR(j, 1, n) {
        cin >> gd[i][j];
        if(gd[i][j] == 0){
            ct0 = 1;
            tr0 = {i, j};
        }
    }

    tie(ct2, dir2) = solve(2);
    tie(ct5, dir5) = solve(5);

    if(ct2 == min({ct2, ct5, ct0})){
        cout << ct2 << endl;
        for(bool b : dir2) cout << (b ? 'R' : 'D');
    }else if(ct5 == min({ct2, ct5, ct0})){
        cout << ct5 << endl;
        for(bool b : dir5) cout << (b ? 'R' : 'D');
    }else{
        cout << ct0 << endl;
        FOR(i, 1, tr0.fs - 1) cout << 'D';
        FOR(j, 1, tr0.sc - 1) cout << 'R';
        FOR(i, tr0.fs + 1, n) cout << 'D';
        FOR(j, tr0.sc + 1, n) cout << 'R';
    }
}
