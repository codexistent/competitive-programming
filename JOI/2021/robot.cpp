#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 100005
#define MAXM 200005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, m, d[MAXN], mn[MAXM], sm[MAXM];
vector<array<ll, 3>> e[MAXN];
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
bool v[MAXN];

int main(){
    cin >> n >> m;
    FOR(i, 1, m){
        ll u, v, w, c;
        cin >> u >> v >> c >> w;
        e[u].push_back({v, w, c});
        e[v].push_back({u, w, c});
    }
    FOR(i, 1, n) d[i] = LLONG_MAX, v[i] = false;

    d[1] = 0;
    pq.push({0, 1});
    while(pq.size()){
        ll pqi = pq.top().s; pq.pop();
        if(v[pqi]) continue;
        v[pqi] = true;

        for(auto i : e[pqi]) mn[i[2]] = LLONG_MAX, sm[i[2]] = 0;
        for(auto i : e[pqi]) sm[i[2]] += i[1];
        for(auto i : e[pqi]) if(d[i[0]] != LLONG_MAX) mn[i[2]] = min(mn[i[2]], d[i[0]] + sm[i[2]]);
        for(auto i : e[pqi]){
            ll i2 = i[0], w = i[1], c = i[2]; 
            if(d[i2] > min({d[pqi] + w, d[pqi] + sm[c] - w, mn[c] - w})){
                d[i2] = min({d[pqi] + w, d[pqi] + sm[c] - w, mn[c] - w});
                pq.push({d[i2], i2});
            }
        }
    }

    cout << (d[n] == LLONG_MAX ? -1 : d[n]) << endl;
}
