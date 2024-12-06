// https://cses.fi/alon/result/11340103/

#include <bits/stdc++.h>
using namespace std;
#define ll int
#define MAXN 200005 
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, m, arr[MAXN], st[MAXN * 4], r[MAXN], add[MAXN];
vector<pair<pair<ll, ll>, ll>> q;
map<ll, ll> prv;

void update(ll i, ll l, ll r, ll updi, ll updv){
    if(r < updi || updi < l) return;

    if(l == r) {
        st[i] += updv;
        return;
    }
    update(i * 2, l, (l + r) / 2, updi, updv), update(i * 2 + 1, (l + r) / 2 + 1, r, updi, updv);
    st[i] = st[i * 2] + st[i * 2 + 1];
}

ll query(ll i, ll l, ll r, pair<ll, ll> qry){
    if(qry.s < l || r < qry.f) return 0;

    if(qry.f <= l && r <= qry.s) return st[i];
    return query(i * 2, l, (l + r) / 2, qry) + query(i * 2 + 1, (l + r) / 2 + 1, r, qry);
}

int main(){
    cin >> n >> m;
    FOR(i, 0, MAXN * 4 - 1) st[i] = 0;

    set<ll> sn;
    FOR(i, 1, n) add[i] = -1;
    FOR(i, 1, n) {
        cin >> arr[i];
        if(sn.find(arr[i]) == sn.end()){
            update(1, 1, n, i, 1);
            sn.insert(arr[i]);
            prv.insert({arr[i], i});
        }else{
            add[prv[arr[i]]] = i;
            prv[arr[i]] = i;
        }
    }
    FOR(i, 1, m){
        pair<pair<ll, ll>, ll> pr;
        pr.s = i;
        cin >> pr.f.f >> pr.f.s;
        q.push_back(pr);
    }
    sort(begin(q), end(q));

    ll sti = 1;
    for(auto qi : q){
        while(sti < qi.f.f){
            if(add[sti] != -1){
                update(1, 1, n, add[sti], 1);
            }
            sti++;
        }

        r[qi.s] = query(1, 1, n, qi.f);
    }

    FOR(i, 1, m) cout << r[i] << endl;
}
