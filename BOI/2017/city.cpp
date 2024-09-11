#include <bits/stdc++.h>
using namespace std;
#define MAXN 300005
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define f first
#define s second

ll n, k, a[MAXN];
vector<ll> e[MAXN];
pair<ll, ll> nx[MAXN];
pair<ll, ll> nx2[MAXN];

void dfs1(ll v = 1, ll p = -1){
    nx[v] = {LLONG_MIN  + 1, LLONG_MIN  + 1};
    nx2[v] = {LLONG_MIN  + 1, LLONG_MIN  + 1};
    for(ll v2 : e[v]) if(v2 != p){
        dfs1(v2, v);
        if(nx[v2].f != LLONG_MIN + 1){
            if(nx[v].f == LLONG_MIN + 1 || nx[v2].s - 1 > nx[v].s || (nx[v2].s - 1 == nx[v].s && nx[v2].f < nx[v].f)){
                nx2[v] = nx[v];
                nx[v] = {nx[v2].f, nx[v2].s - 1};
            }else if(nx2[v].f == LLONG_MIN + 1 || nx[v2].s - 1 > nx2[v].s || (nx[v2].s - 1 == nx2[v].s && nx[v2].f < nx2[v].f)){
                nx2[v] = {nx[v2].f, nx[v2].s - 1};
            }
        }

        if(nx2[v2].f != LLONG_MIN + 1){
            if(nx[v].f == LLONG_MIN + 1 || nx2[v2].s - 1 > nx[v].s || (nx2[v2].s - 1 == nx[v].s && nx2[v2].f < nx[v].f)){
                nx2[v] = nx[v];
                nx[v] = {nx2[v2].f, nx2[v2].s - 1};
            }else if(nx2[v].f == LLONG_MIN + 1 || nx2[v2].s - 1 > nx2[v].s || (nx2[v2].s - 1 == nx2[v].s && nx2[v2].f < nx2[v].f)){
                nx2[v] = {nx2[v2].f, nx2[v2].s - 1};
            }
        }

        if(nx[v].f == LLONG_MIN + 1 || a[v2] - 1 > nx[v].s || (a[v2] - 1 == nx[v].s && v2 < nx[v].f)){
            nx2[v] = nx[v];
            nx[v] = {v2, a[v2] - 1};
        }else if(nx2[v].f == LLONG_MIN + 1 || a[v2] - 1 > nx2[v].s || (a[v2] - 1 == nx2[v].s && v2 < nx2[v].f)){
            nx2[v] = {v2, a[v2] - 1};
        }
    }
}

void dfs2(ll v = 1, ll p = -1){
    if(p != -1){
        if(nx[p].f != v && nx[p].f != nx[v].f && nx[p].f != nx2[v].f){
            if(nx[v].f == LLONG_MIN + 1 || nx[p].s - 1 > nx[v].s || (nx[p].s - 1 == nx[v].s && nx[p].f < nx[v].f)){
                nx2[v] = nx[v];
                nx[v] = {nx[p].f, nx[p].s - 1};
            }else if(nx2[v].f == LLONG_MIN + 1 || nx[p].s - 1 > nx2[v].s || (nx[p].s - 1 == nx2[v].s && nx[p].f < nx2[v].f)){
                nx2[v] = {nx[p].f, nx[p].s - 1};
            }
        }
        if(nx2[p].f != v && nx2[p].f != nx[v].f && nx2[p].f != nx2[v].f){
            if(nx[v].f == LLONG_MIN + 1 || nx2[p].s - 1 > nx[v].s || (nx2[p].s - 1 == nx[v].s && nx2[p].f < nx[v].f)){
                nx2[v] = nx[v];
                nx[v] = {nx2[p].f, nx2[p].s - 1};
            }else if(nx2[v].f == LLONG_MIN + 1 || nx2[p].s - 1 > nx2[v].s || (nx2[p].s - 1 == nx2[v].s && nx2[p].f < nx2[v].f)){
                nx2[v] = {nx2[p].f, nx2[p].s - 1};
            }
        }

        if(nx[v].f == LLONG_MIN + 1 || a[p] - 1 > nx[v].s || (a[p] - 1 == nx[v].s && p < nx[v].f)){
            nx2[v] = nx[v];
            nx[v] = {p, a[p] - 1};
        }else if(nx2[v].f == LLONG_MIN + 1 || a[p] - 1 > nx2[v].s || (a[p] - 1 == nx2[v].s && p < nx2[v].f)){
            nx2[v] = {p, a[p] - 1};
        }
    }

    for(ll v2 : e[v]) if(v2 != p) dfs2(v2, v);
}

int main(){
    cin >> n >> k;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n - 1){
        ll x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs1();
    dfs2();

    bool v[MAXN];
    FOR(i, 1, n) v[i] = false;
    vector<int> seq;
    int c = 1;
    while(!v[c]){
        seq.push_back(c);
        v[c] = true;
        c = nx[c].f;
    }

    ll lst = 0, lsz = 0;
    FOR(i, 1, seq.size()){
        if(seq[i - 1] == c){
            lst = i;
            break;
        }
    }
    lsz = seq.size() - lst + 1;

    k++;
    if(k <= seq.size()){
        cout << seq[k - 1];
    }else{
        k -= lst - 1;
        k = k % lsz;
        if(k == 0) k = lsz;
        cout << seq[lst - 1 + (k - 1)];
    }
}
