#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define f first 
#define s second

int n, pfx[MAXN], pr[MAXN], pl[MAXN], stmn[MAXN * 4], q;
string s;

void update(int i, int l, int r, pair<int, int> upd){
    if(upd.f < l || r < upd.f) return;

    if(l == r){
        stmn[i] = upd.s;
    } else{
        update(i * 2, l, (l + r) / 2, upd);
        update(i * 2 + 1, (l + r) / 2 + 1, r, upd);
        stmn[i] = min(stmn[i * 2], stmn[i * 2 + 1]);
    }
}

int query(int i, int l, int r, pair<int, int> qry){
    if(qry.s < l || r < qry.f) return INT_MAX;

    if(qry.f <= l && r <= qry.s) return stmn[i];
    return min(query(i * 2, l, (l + r) / 2, qry), query(i * 2 + 1, (l + r) / 2 + 1, r, qry));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    n = s.length();
    pfx[0] = 0, pr[0] = 0, pl[0] = 0;

    FOR(i, 0, MAXN * 4 - 1) stmn[i] = INT_MAX;
    FOR(i, 1, n) {
        pfx[i] = pfx[i - 1] + (s[i - 1] == '(' ? 1 : -1);
        pr[i] = pr[i - 1] + (s[i - 1] == ')');

        update(1, 1, n, {i, pfx[i]});
    }

    cin >> q;
    FOR(i, 1, q){
        int l, r;
        cin >> l >> r;

        int sl = query(1, 1, n, {l, r}) - pfx[l - 1];
        int queez = query(1, 1, n, {l, r});
        int rb = (pr[r] - pr[l - 1]) + min(0, sl);
        cout << max(0, rb * 2) << endl;
    }
}
