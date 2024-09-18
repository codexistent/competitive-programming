#include <bits/stdc++.h>
using namespace std;
#define ll int
#define MAXN 30005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, m, d[MAXN], b0 = 0, b1 = 0;
vector<pair<ll, ll>> adj[MAXN];
set<ll> p[MAXN];

int main(){
    cin >> n >> m;
    FOR(i, 0, m - 1){
        ll bi, pi; cin >> bi >> pi;
        
        if(i == 0) b0 = bi;
        if(i == 1) b1 = bi;

        p[bi].insert(pi);
    }

    FOR(i, 0, n - 1){
        for(ll pi : p[i]){
            ll j = i;
            while(0 <= j - pi){
                j -= pi;
                adj[i].push_back({j, (i - j) / pi});
                if(p[j].find(pi) != p[j].end()) break;
            }

            j = i;
            while(j + pi <= n - 1){
                j += pi;
                adj[i].push_back({j, (j - i) / pi});
                if(p[j].find(pi) != p[j].end()) break;
            }
        }
        d[i] = -1;
    }

    priority_queue<pair<ll, ll>> pq;
    d[b0] = 0, pq.push({0, b0});
    while(!pq.empty()){
        auto pqi = pq.top(); pqi.first *= -1;
        pq.pop();

        if(d[pqi.second] < pqi.first) continue;
        if(pqi.second == b1) break;

        for(auto i : adj[pqi.second]){
            if(d[i.first] == -1 || pqi.first + i.second < d[i.first]){
                d[i.first] = pqi.first + i.second;
                pq.push({-d[i.first], i.first});
            }
        }
    }

    cout << d[b1] << endl;
}
