#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define MAXN 200005
#define MAXV 1000005
#define MXSQRT 505
#define fs first 
#define sc second

// LESSON: DONT USE MAPS WHEN UNNEEDED
// LESSON: USE '\n' INSTEAD OF ENDL
int n, p, q, a[MAXN], mp[MAXV];
long long ans[MAXN];
pair<int, int> ql[MAXN];
vector<pair<int, int>> qg[MXSQRT]; // {right ptr, idx}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    FOR(i, 1, n) cin >> a[i];
    p = sqrt(n);
    FOR(i, 0, MAXV - 1) mp[i] = 0;

    FOR(i, 1, q){
        cin >> ql[i].fs >> ql[i].sc;
        qg[ql[i].fs / p].push_back({ql[i].sc, i});
    }

    for(auto g : qg) if(g.size()){
        int ni = g.size();

        sort(begin(g), end(g));

        long long r = 0ll;

        // qi = 0
        FOR(i, ql[g[0].sc].fs, ql[g[0].sc].sc){
            r -= (long long)a[i] * mp[a[i]] * mp[a[i]];
            mp[a[i]]++;
            r += (long long)a[i] * mp[a[i]] * mp[a[i]];
        }

        int lo, hi; tie(lo, hi) = ql[g[0].sc];
        ans[g[0].sc] = r;
        FOR(qi, 1, ni - 1){
            int lo2, hi2; tie(lo2, hi2) = ql[g[qi].sc];

            // update lo
            if(lo < lo2){
                FOR(i, lo, lo2 - 1){
                    r -= (long long)a[i] * mp[a[i]] * mp[a[i]];
                    mp[a[i]]--;
                    r += (long long)a[i] * mp[a[i]] * mp[a[i]];
                }
            }else{
                FOR(i, lo2, lo - 1){
                    r -= (long long)a[i] * mp[a[i]] * mp[a[i]];
                    mp[a[i]]++;
                    r += (long long)a[i] * mp[a[i]] * mp[a[i]];
                }
            }

            // move up hi
            FOR(i, hi + 1, hi2){
                r -= (long long)a[i] * mp[a[i]] * mp[a[i]];
                mp[a[i]]++;
                r += (long long)a[i] * mp[a[i]] * mp[a[i]];
            }

            tie(lo, hi) = {lo2, hi2};

            ans[g[qi].sc] = r;
        }

        FOR(i, lo, hi) mp[a[i]]--;
    }

    FOR(i, 1, q) cout << ans[i] << '\n';
}
