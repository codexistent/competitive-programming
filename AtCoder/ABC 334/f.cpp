#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define db double
#define ll long long
#define f first
#define s second
#define mp make_pair

struct MinSegmentTree{ // ONE-BASED INDEXED(WILL GIVE ERRORS IF GET RANGE BELOW 1)
public:
    vector<db> tree, lazy;
    ll n;

    MinSegmentTree(ll n) {
        this->n = n;
        tree.assign(4 * this->n + 1, 0);
        lazy.assign(4 * this->n + 1, 0);
    }
    MinSegmentTree(const vector<ll> &a) : MinSegmentTree(a.size()){
        build(a, 1, 1, n);
    }
    
    void update(ll i, db x){ // point update
        update_range(1, 1, n, make_tuple(i, i, x));
    }
    db query(ll i){
        return query_range(1, 1, n, make_pair(i, i));
    }
    db query(ll i, ll j){
        return query_range(1, 1, n, make_pair(i, j));
    }

private:
    void build(const vector<ll> &a, ll i, ll l, ll r){
        if(l > r) return;
        if(l == r) {
            tree[i] = a[l - 1];
            return;
        }
        
        ll m = (l + r) / 2;
        build(a, 2*i, l, m);
        build(a, 2*i + 1, m + 1, r);

        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
    void update_range(ll i, ll l, ll r, tuple<ll, ll, db> upd){
        if(lazy[i] != 0){
            tree[i] += lazy[i];
            if(l != r){
                lazy[i * 2] += lazy[i];
                lazy[i * 2 + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if(l > r || get<1>(upd) < l || r < get<0>(upd)) return;

        if(get<0>(upd) <= l && r <= get<1>(upd)){
            tree[i] += get<2>(upd);
            if(l != r){
                lazy[i * 2] += get<2>(upd);
                lazy[i * 2 + 1] += get<2>(upd);
            }
            return;
        }

        ll m = (l + r) / 2;
        update_range(i * 2, l, m, upd);
        update_range(i * 2 + 1, m + 1, r, upd);

        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
    db query_range(ll i, ll l, ll r, pair<ll, ll> qry){
        if(l > r || qry.second < l || r < qry.first) {
            return INFINITY;
        }

        if(lazy[i] != 0){
            tree[i] += lazy[i];
            if(l != r) {
                lazy[i * 2] += lazy[i];
                lazy[i * 2 + 1] += lazy[i];
            }
            lazy[i] = 0;
        }

        if(qry.first <= l && r <= qry.second) return tree[i];

        ll m = (l + r) / 2;
        return min(query_range(i * 2, l, m, qry), query_range(i * 2 + 1, m + 1, r, qry));
    }
};

db dist(pair<db, db> a, pair<db, db> b){
    return sqrt((a.f - b.f) * (a.f - b.f) + (a.s - b.s) * (a.s - b.s));
}

int main(){
    int N, K;
    cin >> N >> K;
    pair<db, db> c[N + 1];
    db d[N + 2], ddist = 0;
    cin >> c[0].f >> c[0].s;
    c[N + 1].f = c[0].f, c[N + 1].s = c[0].s;
    FOR(i, 1, N){
        cin >> c[i].f >> c[i].s;
        ddist += dist(c[i - 1], c[i]);
    }
    FOR(i, 1, N) {
        d[i] = -dist(c[i], c[i + 1]) + dist(mp(c[i].f, c[i].s), c[0]) + dist(c[0], mp(c[i + 1].f, c[i + 1].s));
    }
    ddist += dist(c[N], c[0]);

    db dp[N + 1];
    MinSegmentTree MT(N + 1);
    FOR(i, 0, N) dp[i] = INFINITY;
    dp[0] = 0;
    FOR(i, 1, N){
        dp[i] = MT.query(max(0, i - K) + 1, i - 1 + 1) + d[i];
        MT.update(i + 1, dp[i]);
    }

    cout << setprecision(6) << fixed << MT.query(max(0, N - K + 1) + 1, N + 1) + ddist << endl;
}
