#include <bits/stdc++.h>
using namespace std;
#define MAXN 500005
#define MAXV 10000005
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)

int n, pf[MAXV], r[MAXN][2];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
  
    FOR(i, 1, 10000000) pf[i] = i;
    FOR(i, 2, 10000000) if(pf[i] == i){
        for(int j = i; j <= 10000000; j += i) pf[j] = i;
    }

    cin >> n;
    FOR(ni, 1, n){
        int q; cin >> q;
        int p = pf[q];

        while(q % p == 0 && q >= 1) q /= p;
        
        if(p != 1 && q != 1){
            tie(r[ni][0], r[ni][1]) = {p, q};
        }else{
            r[ni][0] = r[ni][1] = -1;
        }
    }
    
    FOR(j, 0, 1){
      FOR(i, 1, n) cout << r[i][j] << ' ';
      cout << '\n';
    }
}
 
