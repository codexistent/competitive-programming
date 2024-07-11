#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define MAXN 705
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, osc = 0;
db h[MAXN][MAXN], g[MAXN][MAXN];
db osz[MAXN * MAXN], op[MAXN * MAXN], sz[MAXN * MAXN], p[MAXN * MAXN];
db t[MAXN * MAXN], pt = -1, r = 1;

ll find(ll x){
    if(t[x] != pt) {
        sz[x] = osz[x], p[x] = op[x], t[x] = pt;
    }
    if(x == p[x]){
        return x;
    }

    if(t[(ll)p[x]] != pt) {
        sz[(ll)p[x]] = osz[(ll)p[x]], p[(ll)p[x]] = op[(ll)p[x]], t[(ll)p[x]] = pt;
    }
    return p[x] = find(p[x]);
}

void onion(ll a, ll b){
    a = find(a), b = find(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[a] = p[b] = a;

    r = max(r, sz[a]);
}

int main(){
    cin >> n;
    FOR(i, 1, n) FOR(j, 1, n) cin >> h[i][j];
    FOR(i, 1, n) FOR(j, 1, n) cin >> g[i][j];

    priority_queue<pair<db, pair<ll, ll> > > pq;
    vector<pair<ll, ll > > pg;
    FOR(i, 1, n){
        FOR(j, 1, n){
            if(i != n){ // then add edge between (i, j) and (i + 1, j)
                if((h[i][j] < h[i + 1][j] && g[i][j] > g[i + 1][j]) || (h[i][j] > h[i + 1][j] && g[i][j] < g[i + 1][j]) || h[i][j] == h[i + 1][j]){
                    if(g[i][j] == g[i + 1][j]){
                        pg.push_back({(i - 1) * n + j, ((i + 1) - 1) * n + j});
                    }else{
                        pq.push({(db)(h[i][j] - h[i + 1][j]) / (g[i + 1][j] - g[i][j]), {(i - 1) * n + j, ((i + 1) - 1) * n + j}});
                    }
                }
            }
            if(j != n){
                if((h[i][j] < h[i][j + 1] && g[i][j] > g[i][j + 1]) || (h[i][j] > h[i][j + 1] && g[i][j] < g[i][j + 1]) || h[i][j] == h[i][j + 1]){
                    if(g[i][j] == g[i][j + 1]){
                        pg.push_back({(i - 1) * n + j, (i - 1) * n + (j + 1)});
                    }else{
                        pq.push({(db)(h[i][j] - h[i][j + 1]) / (g[i][j + 1] - g[i][j]), {(i - 1) * n + j, (i - 1) * n + (j + 1)}});
                    }
                }
            }
        }
    }

    FOR(i, 1, n * n) t[i] = -1, sz[i] = 1, p[i] = i;

    for(auto i : pg) onion(i.f, i.s);
    FOR(i, 1, n * n) osz[i] = sz[i], op[i] = p[i];

    while(!pq.empty()){
        auto pqi = pq.top(); pq.pop();
        if(pqi.f != pt){
            pt = pqi.f;
        }
        
        if(t[pqi.s.f] != pt) {
            sz[pqi.s.f] = osz[pqi.s.f], p[pqi.s.f] = op[pqi.s.f], t[pqi.s.f] = pt;
        }
        if(t[pqi.s.s] != pt) {
            sz[pqi.s.s] = osz[pqi.s.s], p[pqi.s.s] = op[pqi.s.s], t[pqi.s.s] = pt;
        }
        onion(pqi.s.f, pqi.s.s);
    }

    cout << (ll)r << endl;
}
