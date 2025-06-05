#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define RFOR(ict, ist, ied) for(int ict = ist; ict >= ied; ict--)
#define MAXN 100005
#define MXLOG 25

int n, a[MAXN], r = 0ll, pfx[MAXN][MXLOG], sfx[MAXN][MXLOG];
vector<int> pg[61];
set<int> st;

int rpfx(int a, int b){
    int lg = log2(b - a + 1);
    return max(pfx[a][lg], pfx[b - (int)pow(2, lg) + 1][lg]);
}
int rsfx(int a, int b){
    int lg = log2(b - a + 1);
    return max(sfx[a][lg], sfx[b - (int)pow(2, lg) + 1][lg]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    FOR(i, 1, n) {
        cin >> a[i]; 
        pg[a[i] + 30].push_back(i);
    }

    pfx[0][0] = 0ll; FOR(i, 1, n) pfx[i][0] = pfx[i - 1][0] + a[i];
    sfx[n + 1][0] = 0ll; RFOR(i, n, 1) sfx[i][0] = sfx[i + 1][0] + a[i];
    for(int j = 1, jsz = 2; jsz <= n; j++, jsz *= 2){
        FOR(i, 1, n) if(i + jsz - 1 <= n){
            pfx[i][j] = max(pfx[i][j - 1], pfx[i + jsz / 2][j - 1]);
            sfx[i][j] = max(sfx[i][j - 1], sfx[i + jsz / 2][j - 1]);
        }
    }

    st.insert(0), st.insert(n + 1);
    RFOR(pgi, 60, 0){
        for(int i : pg[pgi]){
            int lo = *prev(st.lower_bound(i)) + 1, hi = *st.lower_bound(i) - 1;
            lo = rsfx(lo, i), hi = rpfx(i, hi);
            
            r = max(r, (lo - sfx[i][0]) + (hi - pfx[i][0]));
        }
        for(int i : pg[pgi]) st.insert(i);
    }

    cout << r << '\n';
}
