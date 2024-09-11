#include <bits/stdc++.h>
using namespace std;
#define MAXN 300005
#define MAXMSK 32
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, m, k, t[MAXN], r;
ll dp[MAXN][6][MAXMSK];
vector<ll> e[MAXN];

int main(){
    cin >> n >> m >> k;
    FOR(i, 1, n) cin >> t[i];

    int mxmsk = pow(2, k);
    FOR(i, 1, n) FOR(ki, 2, k) FOR(msk, 0, mxmsk - 1) dp[i][ki][msk] = 0;
    FOR(i, 1, m){
        ll a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);

        if(t[a] != t[b]){
            dp[a][2][(1 << (t[b] - 1)) | (1 << (t[a] - 1))]++;
            dp[b][2][(1 << (t[b] - 1)) | (1 << (t[a] - 1))]++;
        }
    }

    FOR(ki, 3, k){
        FOR(i, 1, n){
            FOR(msk, 0, mxmsk - 1){
                int ct = 0;
                FOR(j, 1, k) {
                    if(msk & (1 << (j - 1))) ct++;
                }

                if(ct != ki || !(msk & (1 << (t[i] - 1)))) continue;

                for(int i2 : e[i]){
                    dp[i][ki][msk] += dp[i2][ki - 1][msk & ~(1 << (t[i] - 1))];
                }
            }
        }
    }

    r = 0;
    FOR(i, 1, n) FOR(ki, 2, k) FOR(msk, 0, mxmsk) {
        r += dp[i][ki][msk];
    }

    cout << r << endl;
}
