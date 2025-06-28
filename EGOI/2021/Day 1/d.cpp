#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define ROF(ict, ist, ied) for(ll ict = ist; ict >= ied; ict--)
#define MAXNK 2005
#define MOD 1000000007
#define fs first 
#define sc second
#define pll pair<ll, ll>

ll n, k, h[MAXNK], p[MAXNK], c[MAXNK], dp[MAXNK][MAXNK], inv_byfs[MAXNK], inv_bysc[MAXNK];
pll rngh[MAXNK], rngx[2][MAXNK];
pair<pll, ll> byfs[MAXNK], bysc[MAXNK];
priority_queue<pll, vector<pll>, greater<pll>> pq[2][MAXNK];

bool trtr = false;

void update(ll z, ll i, ll j, ll ci){
    pq[z][i].push({ci, j});
}
ll query(ll z, ll i, pll rngxi, pll rnghi){
    while(pq[z][i].size()){
        ll pqi = pq[z][i].top().sc;
        if(p[pqi] < rngxi.fs || rngxi.sc < p[pqi]) {
            pq[z][i].pop();
            continue;
        }

        if(rngh[pqi].sc < rnghi.fs || rnghi.sc < rngh[pqi].fs){
            pq[z][i].pop();
            continue;
        }
        return pq[z][i].top().fs;
    }

    return MOD;
}

// LESSON: UNDERSTAND THE SOL MORE!!! OR DEBUGGING WILL HAUNT U!!!
// INSPO: BenQ PQ SOL.
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    FOR(i, 1, n) cin >> h[i];
    FOR(i, 1, k) {
        cin >> p[i] >> c[i] >> rngh[i].fs >> rngh[i].sc;
        byfs[i] = {{rngh[i].fs, -rngh[i].sc}, i}, bysc[i] = {{rngh[i].sc, -rngh[i].fs}, i};
    }
    sort(byfs + 1, byfs + 1 + k);
    sort(bysc + 1, bysc + 1 + k);

    FOR(byfsi, 1, k){
        inv_byfs[byfs[byfsi].sc] = byfsi;
        inv_bysc[bysc[byfsi].sc] = byfsi;
        ll i = byfs[byfsi].sc;

        rngx[0][i] = {p[i] + 1, p[i] - 1};
        while(1 <= rngx[0][i].fs - 1 && rngh[i].fs <= h[rngx[0][i].fs - 1]) rngx[0][i].fs--;
        while(rngx[0][i].sc + 1 <= n && rngh[i].fs <= h[rngx[0][i].sc + 1]) rngx[0][i].sc++;

        rngx[1][i] = {p[i] + 1, p[i] - 1};
        while(1 <= rngx[1][i].fs - 1 && h[rngx[1][i].fs - 1] <= rngh[i].sc) rngx[1][i].fs--;
        while(rngx[1][i].sc + 1 <= n && h[rngx[1][i].sc + 1] <= rngh[i].sc) rngx[1][i].sc++;
    }

    FOR(i, 1, k) FOR(j, 1, k) dp[i][j] = MOD;
    FOR(byfsi, 1, k) ROF(byscj, k, 1){
        ll i = byfs[byfsi].sc, j = bysc[byscj].sc;
        pll rnghi = {rngh[i].fs, rngh[j].sc};
        pll rngxi = {max(rngx[0][i].fs, rngx[1][j].fs), min(rngx[0][i].sc, rngx[1][j].sc)};

        if(p[i] < rngxi.fs || rngxi.sc < p[i]) continue;
        if(p[j] < rngxi.fs || rngxi.sc < p[j]) continue;

        if(1 == rngxi.fs && rngxi.sc == n){
            dp[byfsi][byscj] = 0ll;
        }else{
            if(byscj < inv_bysc[i]) {
                dp[byfsi][byscj] = min(dp[byfsi][byscj], dp[byfsi][inv_bysc[i]]);
            }
            if(inv_byfs[j] < byfsi){
                dp[byfsi][byscj] = min(dp[byfsi][byscj], dp[inv_byfs[j]][byscj]);
            }
            dp[byfsi][byscj] = min(dp[byfsi][byscj], query(0, i, rngxi, rnghi));
            dp[byfsi][byscj] = min(dp[byfsi][byscj], query(1, j, rngxi, rnghi));
        }
    
        if(dp[byfsi][byscj] != MOD){
            update(0, i, j, dp[byfsi][byscj] + c[j]);
            update(1, j, i, dp[byfsi][byscj] + c[i]);
        }
    }

    FOR(byfsi, 1, k) ROF(byscj, k, 1){
        ll i = byfs[byfsi].sc, j = bysc[byscj].sc;
        pll rnghi = {rngh[i].fs, rngh[j].sc};
        pll rngxi = {max(rngx[0][i].fs, rngx[1][j].fs), min(rngx[0][i].sc, rngx[1][j].sc)};
    }

    FOR(i, 1, k) cout << ((dp[inv_byfs[i]][inv_bysc[i]] == MOD) ? -1 : (dp[inv_byfs[i]][inv_bysc[i]] + c[i])) << endl;
}
// CF Submission W/ Comments: https://codeforces.com/gym/103148/submission/326450104
