#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define MAXN 300005
#define fs first 
#define sc second

int n, m, t[MAXN], p[MAXN], sz[MAXN], e[MAXN][3];
vector<pair<int, int>> adj[MAXN];
bool c[MAXN], k[MAXN];
set<int> r;
ll d[MAXN];

// LESSON: BE MORE CAREFUL W UR CODE!!! OTHERWISE DEBUGGING WILL HAUNT YOU
// *UNLESS YOU LIKE DEBUGGING
int find(int x) { return (p[x] == x) ? x : (p[x] = find(p[x])); }
void onion(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a, b);
    c[a] |= c[b];
    sz[a] += sz[b];
    p[a] = p[b] = a;
}

bool valid(ll mxd, bool rbl){ // returns true if walls can have max 
    FOR(i, 1, n) p[i] = i, sz[i] = 1ll, c[i] = (t[i] == -1), k[i] = true;

    FOR(ei, 1, m) {
        int i = e[ei][0], j = e[ei][1];
        if(t[i] == 1 || t[i] == -1 || (t[i] == 0 && mxd < d[i])){
            if(t[j] == 1 || t[j] == -1 || (t[j] == 0 && mxd < d[j])){
                onion(i, j);
            }
        }
    }

    FOR(i, 1, n) {
        int fi = find(i);
        if(t[i] == 1 && c[fi]) return false;
        
        k[fi] &= c[fi] == false;
        for(auto adji : adj[i]) if(c[find(adji.fs)]) {
            k[fi] = false;
        }
    }

    // DSU all nodes with k[i] = true;
    FOR(ei, 1, m) {
        int i = find(e[ei][0]), j = find(e[ei][1]);
        if(k[i] && k[j]) onion(i, j);
    }

    int hg = -1;
    FOR(i, 1, n) {
        int fi = find(i);
        if(t[i] == 1){
            if(hg == -1) hg = fi;
            else if(hg != fi){
                return false;
            }
        }
    }

    if(rbl) FOR(i, 1, n) if(!k[find(i)] && t[i] == 0 && d[i] <= mxd) r.insert(i);
    return true;
}

int main(){     
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    FOR(i, 1, n) cin >> t[i];
    FOR(i, 1, m){
        cin >> e[i][0] >> e[i][1] >> e[i][2];
        adj[e[i][0]].push_back({e[i][1], e[i][2]});
        adj[e[i][1]].push_back({e[i][0], e[i][2]});
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    FOR(i, 1, n) {
        if(t[i] == 1) d[i] = 0, pq.push({0ll, i});
        else d[i] = LLONG_MAX;
    }
    while(pq.size()){
        auto pqi = pq.top(); pq.pop();
        int i = pqi.sc;
        ll di = pqi.fs;
        if(d[i] != di) continue;
         
        for(auto adji : adj[i]) {
            int i2 = adji.fs;
            ll wi = adji.sc;
            if(d[i] + wi < d[i2]) {
                d[i2] = d[i] + wi, pq.push({d[i2], i2});
            }
        }
    }

    ll lo = 0, hi = 3000000000000000;
    while(lo < hi){
        ll md = (lo + hi) / 2;
        if(valid(md, 0)){
            hi = md;
        }else{
            lo = md + 1;
        }
    }

    if(valid(lo, 1)){
        cout << r.size() << '\n';
        for(ll ri : r) cout << ri << ' ';
        cout << '\n';
    }else{
        cout << -1 << '\n';
    }
}
