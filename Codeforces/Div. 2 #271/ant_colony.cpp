#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define MAXN 100005
#define FOR(icounter, istart, iend) for(ll icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(ll icounter = istart; icounter >= iend; icounter--)
#define fs first
#define sc second
 
ll n, q, s[MAXN], stmn[MAXN * 4], stgcd[MAXN * 4];
vector<pair<ll, ll>> ss;
 
void update(ll i, ll l, ll r, pair<ll, ll> upd){
    if(upd.fs < l || r < upd.fs) return;
 
    if(l == r) stmn[i] = upd.sc, stgcd[i] = upd.sc;
    else{
        update(i * 2, l, (l + r) / 2, upd);
        update(i * 2 + 1, (l + r) / 2 + 1, r, upd);
        stmn[i] = min(stmn[i * 2], stmn[i * 2 + 1]);
        stgcd[i] = __gcd(stgcd[i * 2], stgcd[i * 2 + 1]);
    }
}
ll query_mn(ll i, ll l, ll r, pair<ll, ll> qry){
    if(qry.sc < l || r < qry.fs) return LLONG_MAX;
 
    if(qry.fs <= l && r <= qry.sc) return stmn[i];
    return min(query_mn(i * 2, l, (l + r) / 2, qry), query_mn(i * 2 + 1, (l + r) / 2 + 1, r, qry));
}
ll query_gcd(ll i, ll l, ll r, pair<ll, ll> qry){
    if(qry.sc < l || r < qry.fs) return 0;
 
    if(qry.fs <= l && r <= qry.sc) return stgcd[i];
    return __gcd(query_gcd(i * 2, l, (l + r) / 2, qry), query_gcd(i * 2 + 1, (l + r) / 2 + 1, r, qry));
}
 
ll ct(pair<ll, ll> rng, ll v){
    ll r = 0;
 
    ll lo = 0, hi = n - 1; // maximum working value
    while(lo < hi){
        ll md = (lo + hi + 1) / 2;
        if(ss[md] <= make_pair(v, rng.sc)){
            lo = md;
        }else{
            hi = md - 1;
        }
    }
    r = hi;
 
    lo = 0, hi = n - 1;
    while(lo < hi){ // minimum working value
        ll md = (lo + hi) / 2;
        if(make_pair(v, rng.fs) <= ss[md]){
            hi = md;
        }else{
            lo = md + 1;
        }
    }
 
    r -= lo - 1;
 
    return r;
}
 
int main(){
    FOR(i, 0, MAXN * 4 - 1) stmn[i] = LLONG_MAX, stgcd[i] = 1;
 
    cin >> n;
    FOR(i, 1, n) {
        cin >> s[i];
        ss.push_back({s[i], i});
        update(1, 1, n, {i, s[i]});
    }
    sort(begin(ss), end(ss));
 
    cin >> q;
    FOR(i, 1, q){
        pair<ll, ll> rng;
        cin >> rng.fs >> rng.sc;
 
        ll mn = query_mn(1, 1, n, rng);
        ll mnct = ct(rng, mn);
 
        if(query_gcd(1, 1, n, rng) == mn){
            cout << (rng.sc - rng.fs + 1 - mnct) << endl;
        }else{
            cout << (rng.sc - rng.fs + 1) << endl;
        }
    }
    
}
