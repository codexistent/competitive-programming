#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 100005 // 100005
#define fs first 
#define sc second

// point update, range query
ll n, m, a[MAXN], st[MAXN * 4], ft[MAXN];

void update_st(ll i, ll l, ll r, ll updi){
    if(updi < l || r < updi) return;

    if(l == r){
        st[i] = updi;
        return;
    }
    update_st(i * 2, l, (l + r) / 2, updi);
    update_st(i * 2 + 1, (l + r) / 2 + 1, r, updi);
    st[i] = (a[st[i * 2]] > a[st[i * 2 + 1]]) ? st[i * 2] : st[i * 2 + 1];
}
void update(ll i, ll x){ 
    ll oi = i;
    while(i <= n) ft[i] += x, i += (i & -i);
    update_st(1, 1, n, oi);
}

ll qpfx(ll i){ return (i > 0) ? (ft[i] + qpfx(i -(i & -i))) : 0ll; }
ll query_mx(ll i, ll l, ll r, pair<ll, ll> qry){
    if(qry.sc < l || r < qry.fs) {
        return qry.fs;
    }
    
    if(qry.fs <= l && r <= qry.sc){
        return st[i];
    }
    ll sti2 = query_mx(i * 2, l, (l + r) / 2, qry);
    ll sti2p1 = query_mx(i * 2 + 1, (l + r) / 2 + 1, r, qry);
    
    return (a[sti2] > a[sti2p1]) ? sti2 : sti2p1;
}
ll query_sm(ll l, ll r){
    return qpfx(r) - qpfx(max(0ll, l - 1));
}

// LESSON: CHECK IF YOU LOG REDUCE
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    a[0] = 0ll;
    FOR(i, 0, MAXN - 1) ft[i] = 0ll;
    FOR(i, 0, MAXN * 4 - 1) st[i] = 0ll;

    cin >> n >> m;
    FOR(i, 1, n) {
        cin >> a[i];
        update(i, a[i]);
    }

    FOR(mi, 1, m){
        ll t; cin >> t;
        if(t == 1){
            ll l, r; cin >> l >> r;
            cout << query_sm(l, r) << endl;
        }else if(t == 2){
            ll l, r, x; cin >> l >> r >> x;
            
            ll mxi = query_mx(1, 1, n, {l, r});
            
            // return 0;
            while(mxi != 0 && a[mxi] >= x){
                ll diff = (a[mxi] % x) - a[mxi];
                a[mxi] %= x;
                update(mxi, diff);

                mxi = query_mx(1, 1, n, {l, r});
            }
        }else{
            ll i, x; cin >> i >> x;
            ll diff = x - a[i]; a[i] = x;
            update(i, diff);
        }
    }
}
