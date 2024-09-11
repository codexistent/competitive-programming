#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXNM 1005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define RFOR(i, a, b) for(ll i = a; i >= b; i--)

ll n, m, gn = 0, g[MAXNM][MAXNM], rr[MAXNM][MAXNM], s[MAXNM][MAXNM], r = 0;
stack<pair<ll, ll>> st[MAXNM];

int main(){
    cin >> n >> m;
    FOR(i, 1, n) FOR(j, 1, m) cin >> g[i][j];
    FOR(i, 1, n) RFOR(j, m, 1){
        rr[i][j] = 1 + (j != m && g[i][j] == g[i][j + 1]) * rr[i][j + 1];
    }

    FOR(i, 1, n){
        FOR(j, 1, m){
            if(i == 1 || g[i][j] != g[i - 1][j]){
                s[i][j] = rr[i][j];
                while(!st[j].empty()) st[j].pop();

                st[j].push({0, i - 1}), st[j].push({rr[i][j], i});
            }else{
                s[i][j] = s[i - 1][j] + rr[i][j];
                while(st[j].size() >= 2 && st[j].top().first >= rr[i][j]){
                    pair<ll, ll> sti = st[j].top(); st[j].pop();
                    s[i][j] -= (sti.first - rr[i][j]) * (sti.second - st[j].top().second);
                }
                st[j].push({rr[i][j], i});
            }
            r += s[i][j];
        }
    }

    cout << r << endl;
}
