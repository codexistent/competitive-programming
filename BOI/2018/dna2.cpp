#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 200005
#define FOR(i, a, b) for(ll i = a; i  <= b; i++)

ll n, k, r, g[MAXN], rq[MAXN], rv = 0, ans = MAXN;

int main(){
    cin >> n >> k >> r;
    FOR(i, 1, n){
        rq[0] = 0;
        cin >> g[i];
    }
    FOR(i, 1, r){
        ll gi; 
        cin >> gi;
        cin >> rq[gi];
    }

    for(ll a = 1, b = 0; a <= n; a++){
        while(b + 1 <= n && rv != r){
            b++;
            rv += (rq[g[b]] == 1);
            rq[g[b]]--;
        }

        if(rv == r){
            ans = min(ans, b - a + 1);
        }

        rv -= (rq[g[a]] == 0);
        rq[g[a]]++;
    }

    if(ans == MAXN){
        cout << "impossible" << endl;
    }else{
        cout << ans << endl;
    }
}
