#include <bits/stdc++.h>
using namespace std;
#define MAXC 1001
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first
#define s second

int c, n, dp[MAXC][MAXC][2];
bool adj[MAXC][MAXC];

int madd(int x, int a){
    return (x + a - 1) % c + 1;
}

int msub(int x, int s){
    if((x + c - s) % c) return (x + c - s) % c;
    return c;
}

void result(int i, int j, bool lr){
    while(i != j && dp[i][j][lr]  != -1){
        if(lr == 0){
            cout << i << endl;
            lr = dp[i][j][lr];
            i = madd(i, 1);
        }else{
            cout << j << endl;
            lr = dp[i][j][lr];
            j = msub(j, 1);
        }
    }
    cout << i << endl;
}

int main(){
    cin >> c >> n;
    FOR(i, 1, c) FOR(j, 1, c) adj[i][j] = false;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        adj[a][b] = adj[b][a] = true;
    }

    FOR(i, 1, c){
        FOR(j, 0, c - 1){
            dp[i][madd(i, j)][0] = dp[i][madd(i, j)][1] = -1;
        }
    }

    FOR(i, 1, c) dp[i][i][0] = dp[i][i][1] = i;

    FOR(len, 2, c){
        for(int i = 1, j = madd(i, len - 1); i <= c; i++, j = madd(i, len - 1)){
            // APPROACH FROM i
            //   i + 1 is open
            if(dp[madd(i, 1)][j][0] != -1 && adj[madd(i, 1)][i]){
                dp[i][j][0] = 0;
            }
            //   j is open
            if(dp[madd(i, 1)][j][1] != -1 && adj[j][i]){
                dp[i][j][0] = 1;
            }

            // APPROACH FROM j
            //   i is open
            if(dp[i][msub(j, 1)][0] != -1 && adj[i][j]){
                dp[i][j][1] = 0;
            }
            //   (0, 1)
            if(dp[i][msub(j, 1)][1] != -1 && adj[msub(j, 1)][j]){
                dp[i][j][1] = 1;
            }
        }
    }

    FOR(i, 1, c){
        if(dp[i][madd(i, c - 1)][0] != -1){
            result(i, madd(i, c - 1), 0);
            return 0;
        }
        if(dp[i][madd(i, c - 1)][1] != -1){
            result(i, madd(i, c - 1), 1);
            return 0;
        }
    }

    cout << "-1" << endl;
}
