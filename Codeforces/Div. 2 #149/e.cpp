#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define MXLOG 21
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define fs first 
#define sc second

int n, q, st[MXLOG][MAXN * 4];
bool lz[MXLOG][MAXN * 4];

void push(int pv, int i, int l, int r){
    if(!lz[pv][i]) return;
    st[pv][i] = (r - l + 1) - st[pv][i];
    if(l != r) lz[pv][i * 2] ^= 1, lz[pv][i * 2 + 1] ^= 1;
    lz[pv][i] = 0;
}

void update(int pv, int i, int l, int r, pair<int, int> updr){
    push(pv, i, l, r);
    if(updr.sc < l || r < updr.fs) return;

    if(updr.fs <= l && r <= updr.sc) {
        lz[pv][i] ^= 1;
        push(pv, i, l, r);
        return;
    }
    update(pv, i * 2, l, (l + r) / 2, updr);
    update(pv, i * 2 + 1, (l + r) / 2 + 1, r, updr);
    st[pv][i] = st[pv][i * 2] + st[pv][i * 2 + 1];
}

int query(int pv, int i, int l, int r, pair<int, int> qry){
    push(pv, i, l, r);
    if(qry.sc < l || r < qry.fs) return 0;
    
    if(qry.fs <= l && r <= qry.sc) return st[pv][i];
    return query(pv, i * 2, l, (l + r) / 2, qry)
        + query(pv, i * 2 + 1, (l + r) / 2 + 1, r, qry);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    FOR(pv, 0, MXLOG - 1) FOR(i, 0, MAXN * 4 - 1) st[pv][i] = 0ll, lz[pv][i] = false; 

    cin >> n;
    FOR(i, 1, n){
        int x; cin >> x;
        FOR(pv, 0, 20) {
            if(x & 1) update(pv, 1, 1, n, {i, i});
            x /= 2;
        }
    }

    cin >> q;
    FOR(qi, 1, q){
        int t; cin >> t;
        if(t == 1){ // sum
            long long r = 0ll, pow2 = 1;
            pair<int, int> rng; cin >> rng.fs >> rng.sc;
            FOR(pv, 0, 20) r += pow2 * query(pv, 1, 1, n, rng), pow2 *= 2;

            cout << r << '\n';
        }else{ // upd
            pair<int, int> qry;
            int x;
            cin >> qry.fs >> qry.sc >> x;
            FOR(pv, 0, 20) {
                if(x & 1) update(pv, 1, 1, n, qry);
                x /= 2;
            }
        }
    }
}
