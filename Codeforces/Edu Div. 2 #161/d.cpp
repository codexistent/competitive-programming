#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define mp make_pair

void solve(){
    ll n;
    cin >> n;
    ll a[n + 2], d[n + 1], k[n + 1];
    fill(d, d + n + 1, 0), fill(k, k + n + 1, 0);

    a[0] = a[n + 1] = 0; FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) cin >> d[i];

    ll l[n + 1], r[n + 1];
    priority_queue<pair<pair<ll, pair<ll, ll>>, ll>> pq;
    FOR(i, 1, n) {
        l[i] = i - 1, r[i] = i + 1;
        pq.push(mp(mp(-1, mp(l[i], r[i])), i));
    }

    bool del[n + 1];
    FOR(i, 1, n) del[i]  = false;
    set<int> dir[n + 1];
    int cr = 1;
    while(!pq.empty()) {
        ll i = pq.top().second, rd = -pq.top().first.first;
        if(d[i] - (a[pq.top().first.second.first] + a[pq.top().first.second.second]) >= 0 || del[i] || ((dir[rd - 1].count(pq.top().first.second.first) || dir[rd - 1].count(pq.top().first.second.second)))) {
            pq.pop();
            continue;
        }
        if(cr < rd) cr = rd;
        pq.pop();
        del[i] = true;
        dir[rd].insert(i);

        k[rd]++;
        r[l[i]] = r[i];
        l[r[i]] = l[i]; 

        if(l[i] != 0) {
            ll i2 = l[i];
            pq.push(mp(mp(- rd - 1, mp(l[i2], r[i2])), i2));
        }
        if(r[i] != n + 1){
            ll i2 = r[i];
            pq.push(mp(mp(- rd - 1, mp(l[i2], r[i2])), i2));
        }
    }

    FOR(i, 1, n) cout << k[i] << " ";
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    FOR(i, 1, t) solve();
}
