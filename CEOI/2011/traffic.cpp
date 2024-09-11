#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 300005
#define MAXM 900005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second
 
ll n, m, c, MAXX, MAXY, p[MAXN], sz[MAXN], en[MAXN], pfx[MAXN];
pair<ll, ll> vp[MAXN], rng[MAXN];
vector<ll> adj[MAXN], radj[MAXN], ts;
bool vis[MAXN], rw[MAXN];
stack<ll> s;
 
ll find(ll x){
    return (p[x] == x) ? x : (p[x] = find(p[x])); 
}
 
void onion(ll a, ll b){
    a = find(a), b = find(b);
    if(a == b) return;
 
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[a] = p[b] = a;
}
 
void dfs1(ll v){
    if(vis[v]) return;
    vis[v] = true;
 
    for(ll v2 : adj[v]) dfs1(v2);
    s.push(v);
}
 
void dfs2(ll v){
    if(vis[v]) return;
    vis[v] = true;
 
    for(ll v2 : radj[v]) {
        v2 = find(v2);
        if(!vis[v2]) onion(v, v2);
        dfs2(v2);
    }
}
 
void dfs3(ll v){
    if(vis[v]) return;
    vis[v] = true;
 
    for(ll v2 : adj[v]){
        v2 = find(v2);
        dfs3(v2);
    }
    ts.push_back(v);
}
 
int main(){
    cin >> n >> m >> MAXX >> MAXY;
    FOR(i, 1, n) cin >> vp[i].f >> vp[i].s;
    FOR(i, 1, m) {
        ll a, b, ct; cin >> a >> b >> ct;
        adj[a].push_back(b), radj[b].push_back(a);
        if(ct == 2) adj[b].push_back(a), radj[a].push_back(b);
    }
 
 
    // Kosarju's
    FOR(i, 1, n) vis[i] = false;
    FOR(i, 1, n) dfs1(i);
 
    FOR(i, 1, n) vis[i] = false, p[i] = i, sz[i] = 1;
    while(!s.empty()){
        ll si = s.top(); s.pop();
        dfs2(si);
    }
 
    // Topological sort
    FOR(i, 1, n) {
        if(find(i) != i){
            ll fi = find(i);
            for(ll i2 : adj[i]){
                adj[fi].push_back(i2);
            }
            for(ll i2 : radj[i]){
                radj[fi].push_back(i2);
            }
        }
    }
    FOR(i, 1, n) vis[i] = false;
    FOR(i, 1, n) dfs3(find(i));
 
    // sort east nodes by top to bottom y values
    vector<pair<ll, ll>> ev;
    FOR(i, 1, n) {
        if(vp[i].f == MAXX){
            ev.push_back({vp[i].s, i});
        }else{
            en[i] = -1;
        }
    }
    sort(begin(ev), end(ev));
 
    // first topological order run
    FOR(i, 1, n) rw[i] = false;
    FOR(i, 1, n) rw[find(i)] |= (vp[i].f == 0);
    for(ll i = ts.size() - 1; i >= 0; i--){
        ts[i] = find(ts[i]);
        for(ll i2 : radj[ts[i]]) {
            rw[ts[i]] |= rw[find(i2)];
        }
    }
 
    // final topological order run
    pfx[0] = 0;
    FOR(i, 0, ev.size() - 1) en[ev[i].s] = i + 1;
    FOR(i, 1, n) rng[find(i)] = {LONG_LONG_MAX, LONG_LONG_MIN};
    FOR(i, 1, n) {
        if(vp[i].f == MAXX && rw[find(i)]) {
            rng[find(i)].f = min(rng[find(i)].f, en[i]);
            rng[find(i)].s = max(rng[find(i)].s, en[i]);
        }
        vis[i] = false;
    }
    FOR(i, 1, ev.size()) pfx[i] = pfx[i - 1] + (rng[ev[i - 1].s].f != LONG_LONG_MAX);
 
    for(ll i : ts){
        i = find(i);
        if(!vis[i]){
            vis[i] = true;
            for(ll i2 : adj[i]) if(find(i2) != i) {
                i2 = find(i2);
 
                rng[i].f = min(rng[i].f, rng[i2].f);
                rng[i].s = max(rng[i].s, rng[i2].s);
            }
        }
    }
 
    set<pair<ll, ll>> st;
    FOR(i, 1, n){
        if(vp[i].f == 0) st.insert({-vp[i].s, find(i)});
    }
    for(pair<ll, ll> i : st){
        if(rng[i.s].f == LONG_LONG_MAX){
            cout << 0 << endl;
        }else{
            cout << (pfx[rng[i.s].s] - pfx[rng[i.s].f - 1]) << endl;
        }
    }
}
