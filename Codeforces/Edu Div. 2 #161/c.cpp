#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

void solve(){
    ll n;
    cin >> n;
    ll pos[n + 1], dl[n + 1], dr[n + 1];
    FOR(i, 1, n) cin >> pos[i];
    FOR(i, 1, n - 1) dr[i] = pos[i + 1] - pos[i];
    FOR(i, 2, n) dl[i] = pos[i] - pos[i - 1];

    FOR(i, 1, n){
        ll closest = 0;
        if(i == 1) closest = 1;
        else if(i == n) closest = 0;
        else closest = (dl[i] < dr[i]) ? 0 : 1;

        if(closest == 0){
            dl[i] = 1;
        }else{
            dr[i] = 1;
        }
    }

    ll pfxl[n + 2], pfxr[n + 1];
    pfxr[1] = 0; FOR(i, 2, n) pfxr[i] = pfxr[i - 1] + dr[i - 1];
    pfxl[n] = 0; for(int i = n - 1; i >= 1; i--) pfxl[i] = pfxl[i + 1] + dl[i + 1];

    ll q;
    cin >> q;
    FOR(i, 1, q){
        int a, b;
        cin >> a >> b;
        if(a < b) cout << pfxr[b] - pfxr[a] << endl;
        if(a >= b)  cout << pfxl[b] - pfxl[a] << endl;
    }
}

int main() {
    int t;
    cin >> t;
    FOR(i, 1, t) solve();
}
