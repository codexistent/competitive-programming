#include "treasure.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 105
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
 
ll pfx[MAXN][MAXN];
 
void findTreasure (int N) {
    ll m = N / 2;
    FOR(i, 0, N) FOR(j, 0, N) pfx[i][j] = 0;
    for(ll i = N; i >= 1; i--){
        for(ll j = N; j >= 1; j--){
            if(i > m & j > m) {
                pfx[i][j] = countTreasure(1, 1, i, j);
            } else if(i > m && j <= m){
                pfx[i][j] = pfx[i][N] - countTreasure(1, j + 1, i, N);
            } else if(i <= m && j > m){
                pfx[i][j] = pfx[N][j] - countTreasure(i + 1, 1, N, j);
            } else if(i <= m && j <= m){
                pfx[i][j] = pfx[N][j] + pfx[i][N] - (pfx[N][N] - countTreasure(i + 1, j + 1, N, N));
            }
        }
    }
    
    FOR(i, 1, N){
        FOR(j, 1, N){
            if(pfx[i][j] - pfx[i - 1][j] - pfx[i][j - 1] + pfx[i - 1][j - 1]){
                Report(i, j);
            }
        }
    }
}
