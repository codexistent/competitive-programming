#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 200005
#define FOR(counteri, starti, endi) for(ll counteri = starti; counteri <= endi; counteri++)
#define f first 
#define s second

ll n, k, st[MAXN * 4], p[MAXN], sz[MAXN], li[MAXN], ri[MAXN], wc;
bool ac[MAXN];

void update(ll i, ll l, ll r, pair<ll, ll> upd){
    if(upd.f < l || r < upd.f) return;

    if(l == r) {
		st[i] = upd.s;
    } else {
        update(i * 2, l, (l + r) / 2, upd);
        update(i * 2 + 1, (l + r) / 2 + 1, r, upd);
        st[i] = st[i * 2] + st[i * 2 + 1];
    }
}

ll query(ll i, ll l, ll r, pair<ll, ll> qry){
    if(qry.s < l || r < qry.f) return 0;

    if(qry.f <= l && r <= qry.s) return st[i];
    return query(i * 2, l, (l + r) / 2, qry) + query(i * 2 + 1, (l + r) / 2 + 1, r, qry);
}

ll find(ll x){
    return (p[x] == x) ? x : (p[x] = find(p[x]));
}

void onion(ll a, ll b){
    a = find(a), b = find(b);
    if(a == b) return;

    update(1, 1, n, {a, 0});
    update(1, 1, n, {b, 0});

    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[a] = p[b] = a;
    li[a] = min(li[a], li[b]), ri[a] = max(ri[a], ri[b]);   

    update(1, 1, n, {a, sz[a] - (bool)(((sz[a] + 1) % 2) && li[a] != 1 && ri[a] != n)}); 
}

int main(){
    cin >> n >> k;

    FOR(i, 0, MAXN * 4 - 1) st[i] = 0;
    update(1, 1, n, {1, 1});

    vector<pair<ll, ll>> ord;
    FOR(i, 1, n){
        ll x; cin >> x;
        ord.push_back({x, i});
        p[i] = i, sz[i] = 1, li[i] = ri[i] = i, ac[i] = false;
    }
    sort(begin(ord), end(ord));
    wc = ord.back().f;
    ord.pop_back();

    for(pair<ll, ll> ordi : ord){
        ll oi = ordi.s, i = ordi.s;
        ac[i] = true;

        update(1, 1, n, {i, 1});
        if(i != n && !ac[i + 1]) update(1, 1, n, {i + 1, 1});

        if(i != 1 && ac[i - 1]) {
            onion(i - 1, i);
        }
        if(i != n && ac[i + 1]){
            onion(i, i + 1);
        }

        ll lm = -1, ln = -1, rm = -1, rn = -1;
        i = find(i);
        if(li[i] == 1) {
            ln = oi - li[i];
        } else {
            ll lr = oi - li[i];
            lm = ln = query(1, 1, n, {1, li[i] - 1}) + (lr - lr % 2);
        }

        if(ri[i] == n){
            rn = ri[i] - oi;
        }else{
            ll rr = ri[i] - oi;
            rm = rn = (rr - rr % 2) + query(1, 1, n, {ri[i] + 1, n});
        }

        ll mx = max({lm, rm, ln + rm, lm + rn, lm + rm});
        if(mx + 1 >= k){
            cout << ordi.f << endl;
            return 0;
        }
    }
    cout << wc << endl;
}
