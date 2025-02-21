#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100005
#define FOR(counteri, starti, endi) for(ll counteri = starti; counteri <= endi; counteri++)
#define RFOR(counteri, starti, endi) for(ll counteri = starti; counteri >= endi; counteri--)
#define f first
#define s second
#define pll pair<ll, ll>

ll n, m, k;
vector<pll> e[MAXN];
bool v[MAXN], t[MAXN];
priority_queue<pair<ll, pair<ll, pll>>, vector<pair<ll, pair<ll, pll>>>, greater<pair<ll, pair<ll, pll>>>> pq;

int main(){
    cin >> n >> m >> k;
    FOR(i, 1, n) t[i] = false, v[i] = (i == 1);
    FOR(i, 1, m){
        ll a, b, w;
        cin >> a >> b >> w;
        e[a].push_back({b, w});
        e[b].push_back({a, w});

        if(a == 1) pq.push({w, {b, {-1, -1}}});
        if(b == 1) pq.push({w, {a, {-1, -1}}});
    }
    FOR(i, 1, k){
        ll a, w;
        cin >> a >> w;
        pq.push({w, {a, {w, a}}});
    }

    while(pq.size()){
        pair<ll, pair<ll, pll>> pqi = pq.top(); pq.pop();
        ll w = pqi.f, i = pqi.s.f;
        if(v[i]) continue;
        v[i] = true;

        if(pqi.s.s.f != -1) t[pqi.s.s.s] = true;

        for(pll ei : e[i]) if(!v[ei.f]) {
            pq.push({w + ei.s, {ei.f, pqi.s.s}});
        }
    }

    ll r = k;
    FOR(i, 1, n) if(t[i]) r--;
    cout << r << endl;
}
