#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define MAXM 500005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, m, t[MAXN], en[MAXN], r[MAXM];
pair<ll, ll> e[MAXM];
vector<pair<ll, ll>> adj[MAXN];
bool v[MAXN];

int main(){
    cin >> n >> m;
    FOR(i, 1, n) {
        cin >> t[i];
        en[i] = 0, v[i] = false;
    }
    FOR(i, 1, m){
        cin >> e[i].f >> e[i].s;
        adj[e[i].f].push_back({e[i].s, i}), en[e[i].f]++;
        adj[e[i].s].push_back({e[i].f, i}), en[e[i].s]++;
        r[i] = 1000000001;
    }
    if(!(m == n - 1 || m == n)) return cout << 0 << endl, 0;

    queue<ll> q;
    FOR(i, 1, n) if(en[i] == 1) q.push(i);

    ll d = n;
    while(q.size()){
        ll qi = q.front(); q.pop();
        if(v[qi]) continue;
        v[qi] = true, d--;
        if(en[qi] == 0) continue;

        for(pair<ll, ll> p : adj[qi]) if(r[p.s] == 1000000001) {
            r[p.s] = 2 * t[qi];
            t[p.f] -= t[qi], en[p.f]--;

            if(!v[p.f] && en[p.f] == 1) q.push(p.f);
        }
    }

    if(d != 0 && d % 2 == 0) return cout << 0 << endl, 0;

    ll prvi = -1, stt, ci = -1, fe = 0;
    FOR(i, 1, n) if(!v[i]) ci = i;
    if(ci == -1) {
        FOR(i, 1, m) cout << r[i] << endl;
        return 0;
    }
    stt = ci;

    stack<ll> st;
    ll alts = 0;
    do{
        for(pair<ll, ll> p : adj[ci]) if(r[p.s] == 1000000001 && !(e[p.s].f == prvi || e[p.s].s == prvi)) {
            prvi = ci, ci = p.f;
            if(stt != ci) alts = t[p.f] - alts;
            if(fe == 0) fe = p.s;
            break;
        }
        st.push(ci);
    }while(stt != ci);

    prvi = r[fe] = t[stt] - alts;
    if(prvi % 2) return cout << 0 << endl, 0;

    ll pi = st.top(); st.pop();
    while(!st.empty()){
        ll sti = st.top(); st.pop();

        for(pair<ll, ll> p : adj[sti]) if(e[p.s].f == pi || e[p.s].s == pi) {
            prvi = r[p.s] = 2 * (t[pi] - prvi / 2);
            if(prvi % 2) return cout << 0 << endl, 0;
        }
        pi = sti;
    }

    FOR(i, 1, m) cout << r[i] << endl;
}
