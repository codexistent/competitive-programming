#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define RFOR(ict, ist, ied) for(int ict = ist; ict >= ied; ict--)
#define MAXN 100005
 
int n, k, a[MAXN];
long long pfx[MAXN], sfx[MAXN];
 
// LESSON: BE MORE PRECISE LMO
long long ops(int x, int y){
    long long r = 1, tp = 0;
    while(x % 2 == 0){
        if(x == y * 2) r--, tp = 1; 
        x /= 2, r *= 2;
    }
    
    return r + tp;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t; cin >> t;
    while(t--) {
        cin >> n >> k;
        FOR(i, 1, n) cin >> a[i];
 
        pfx[0] = 0;
        FOR(i, 1, n) pfx[i] = pfx[i - 1] + ops(a[i], (i == n) ? -1 : a[i + 1]);
 
        sfx[n + 1] = 0;
        RFOR(i, n, 1){
            sfx[i] = sfx[i + 1] + ops(a[i], (i == 1) ? -1 : a[i - 1]); 
        }
 
        long long mx = max({(long long)n, pfx[n], sfx[1]});
        FOR(i, 1, n){
            mx = max(mx, pfx[i - 1] + ops(a[i], -1) + sfx[i + 1]);
        }
 
        cout << (mx >= k ? "YES" : "NO") << '\n';
    }
}
