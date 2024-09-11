#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
#define LOGN 25
#define FOR(i, a, b) for(int i = a; i <= b; i++)
 
char l[MAXN];
int ln, qn;
int sz[MAXN], lj[MAXN][LOGN], dp[MAXN];
 
void Init() {
    qn = 0;
    sz[0] = 0;
    l[0] = 'X', ln = 0;
    dp[0] = 0;
}
 
void TypeLetter(char L) {
    qn++, ln++;
    sz[ln] = sz[dp[qn - 1]] + 1, l[ln] = L;
    dp[qn] = ln;
 
    lj[ln][0] = dp[qn - 1];
    for(int ji = 1, jsz = 2; jsz <= sz[ln] - 1; ji++, jsz *= 2){
        lj[ln][ji] = lj[lj[ln][ji - 1]][ji - 1];
    }
}
 
void UndoCommands(int U) {
    qn++;
    dp[qn] = dp[qn - U - 1];
}
 
char GetLetter(int P) {
    int szi = sz[dp[qn]];
    int rmj = szi - P - 1;
 
    int r = dp[qn];
    FOR(i, 0, 20){
        if((1 << i) & rmj){
            r = lj[r][i];
        }
    }
 
    return l[r];
}
