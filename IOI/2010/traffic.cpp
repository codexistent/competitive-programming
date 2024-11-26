#include <iostream>
#include <vector>
#include <traffic.h>
using namespace std;
#define MAXN 1000005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
 
int t = 0, sum[MAXN], p[MAXN];
pair<int, int> r = make_pair(-1, 2000000005);
vector<int> e[MAXN];
 
int dfs(int i = 0, int par = 0){
    sum[i] = p[i];
    int mx = 0;
    for(int i2 : e[i]) if(i2 != par){
        sum[i] += dfs(i2, i);
 
        mx = max(mx, sum[i2]);
    }
    mx = max(mx, t - sum[i]);
 
    if(mx < r.second){
        r.first = i;
        r.second = mx;
    }
 
    return sum[i];
}
 
int LocateCentre(int N, int P[], int S[], int D[]){
    if(N == 1) return 0;
 
    FOR(i, 0, N - 1) t += P[i], p[i] = P[i];
    FOR(i, 0, N - 2) {
        e[S[i]].push_back(D[i]);
        e[D[i]].push_back(S[i]);
    }
    dfs();
 
    return r.first;
}
