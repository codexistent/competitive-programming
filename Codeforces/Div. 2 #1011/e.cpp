#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 10005

ll n, a[MAXN], b[MAXN], a2[MAXN], sm;

void prt(ll r){ cout << r << '\n'; }
bool check(ll k){
    FOR(i, 1, n) a2[i] = a[i] % k;
    sort(a2 + 1, a2 + 1 + n);

    FOR(i, 1, n) if(a2[i] != b[i]){
        return false;
    }
    return true;
}

// LESSON: MEMORIZE SEQUENCES?? + OEIS, ESP. FOR CT. DIVISORS
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;
    nx: while(t--) {
        cin >> n;
        sm = 0ll;
        FOR(i, 1, n) cin >> a[i];
        FOR(i, 1, n) cin >> b[i];
        FOR(i, 1, n) sm = (sm + a[i] - b[i]);
        sm = abs(sm);

        sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);

        if(sm < 0) {
            prt(-1); goto nx;
        }else if(sm == 0){
            FOR(i, 1, n) if(a[i] != b[i]){
                prt(-1); goto nx;
            }
            prt(1000001); goto nx;
        }

        FOR(i, 1, sqrt(sm)) if(sm % i == 0){
            if(check(i)){
                prt(i); goto nx;
            }
            if(check(sm / i)){
                prt(sm / i); goto nx;
            }
        }

        prt(-1);
    }
}
