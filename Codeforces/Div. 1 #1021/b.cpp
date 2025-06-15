#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXNM 1000005
#define fs first 
#define sc second
#define MOD 1000000007

ll n, m, k, p[MAXNM], tk[MAXNM], sz[MAXNM], r[MAXNM], s[MAXNM];
bool v[MAXNM], fx[MAXNM];
pair<ll, ll> c[MAXNM];

// LESSON: DONT GIVE UP
ll find(ll x){ return (p[x] == x) ? x : (p[x] = find(p[x])); }
ll upd(ll x, ll ri, ll si, bool fxi){
    x = find(x);
    r[x] += ri, s[x] += si, fx[x] |= fxi;
}
void onion(ll a, ll b){
    a = find(a), b = find(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[a] = p[b] = a;
    r[a] += r[b];
    s[a] += s[b]; 
    fx[a] |= fx[b];
}

void solve(){
    cin >> n >> m >> k;
    FOR(i, 1, n * m) p[i] = i, r[i] = s[i] = 0, sz[i] = 1, v[i] = true, fx[i] = false, tk[i] = 0;
    for(ll i = 1; i <= 2 * k + 1; i += 2) {
        cin >> c[i].fs >> c[i].sc;
        tk[(c[i].fs - 1) * m + c[i].sc] = 1;
    }

    for(ll i = 2; i <= 2 * k; i += 2){
        if((abs(c[i - 1].fs - c[i + 1].fs) == 2 && c[i - 1].sc == c[i + 1].sc) || (c[i - 1].fs == c[i + 1].fs && abs(c[i - 1].sc - c[i + 1].sc) == 2)){
            pair<ll, ll> c2 = {(c[i - 1].fs + c[i + 1].fs) / 2, (c[i - 1].sc + c[i + 1].sc) / 2};
            ll c2i = (c2.fs - 1) * m + c2.sc;

            if(tk[c2i] == 1){
                cout << 0 << '\n';
                return;
            }
            upd(c2i, 1, tk[c2i] == 0, true);
            tk[c2i] = 2;

            v[c2i] = false;
        }else if(abs(c[i - 1].fs - c[i + 1].fs) == 1 && abs(c[i - 1].sc - c[i + 1].sc) == 1){
            ll c2i = (c[i - 1].fs - 1) * m + c[i + 1].sc;
            ll c2j = (c[i + 1].fs - 1) * m + c[i - 1].sc;

            if(tk[c2i] == 1 && tk[c2j] == 1){
                cout << 0 << '\n';
                return;
            }else if(tk[c2i] == 1){
                upd(c2j, 1, tk[c2j] == 0, true);
            }else if(tk[c2j] == 1){
                upd(c2i, 1, tk[c2i] == 0, true);
            }else{
                upd(c2i, 1, (tk[c2i] == 0) + (tk[c2j] == 0), false);
                onion(c2i, c2j);
            }

            v[c2i] = v[c2j] = false;
            tk[c2i] = tk[c2j] = 2;
        }else{
            cout << 0 << '\n';
            return;
        }
    }

    ll res = 1ll;
    FOR(i, 1, n * m) {
        ll pi = find(i);
        if(!v[pi]){
            if(r[pi] > s[pi]) {
                res *= 0ll;
            }else if(r[pi] < s[pi]){
                res = (res * sz[pi]) % MOD;
            }else if(r[pi] == s[pi]){
                res = (res * (fx[pi] ? 1ll : 2ll)) % MOD;
            }
            v[pi] = true;
        }
    }

    cout << res << endl;
}

int main(){
    ll t; cin >> t;
    while(t--) solve();
}
