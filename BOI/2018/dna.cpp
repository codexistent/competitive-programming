#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 200005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, b, ksz, s[MAXN];
pair<ll, ll> k[MAXN];

bool valid(ll sz){
    if(sz == n + 1) return true;

    ll v = b - ksz, c[b]; 
    FOR(i, 0, b - 1) c[i] = 0;
    FOR(i, 1, ksz) c[k[i].f] = k[i].s;

    FOR(i, 1, sz){
        c[s[i]]--;
        if(c[s[i]] == 0) v++;
    }

    if(v == b) return true;

    FOR(i, sz + 1, n){
        c[s[i - sz]]++;
        if(c[s[i - sz]] == 1) v--;

        c[s[i]]--;
        if(c[s[i]] == 0) v++;

        if(v == b) return true;
    }
    return false;
}

int main(){
    cin >> n >> b >> ksz;
    FOR(i, 1, n) cin >> s[i];
    FOR(i, 1, ksz) cin >> k[i].f >> k[i].s;

    ll a = 1, b = n + 1;
    while(a < b){
        ll m = (a + b) / 2;
        if(valid(m)){
            b = m;
        }else{
            a = m + 1;
        }
    }

    if(a == n + 1){
        cout << "impossible" << endl;
    }else{
        cout << a << endl;
    }
}
