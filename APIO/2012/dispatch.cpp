// apio 2012 p1
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)

ll n, m, res = 0;
ll p[MAXN], s[MAXN], l[MAXN];
vector<int> c[MAXN];
multiset<int> ms[MAXN];

ll dfs(int i){
    ll si = s[i];
    int sz = -1, ch = -1;
    for(int i2 : c[i]){
        si += dfs(i2);
        if((int)(ms[i2].size()) > sz){
            sz = ms[i2].size();
            ch = i2;
        }
    }

    if(sz != -1) swap(ms[i], ms[ch]);
    for(int i2: c[i]) if(i2 != ch){
        for(int j : ms[i2]){
            ms[i].insert(j);
        }
    }
    ms[i].insert(s[i]);

    while(si > m){
        si -= *(ms[i].rbegin());
        ms[i].erase(ms[i].find(*(ms[i].rbegin())));
    }
    res = max(res, (ll)(ms[i].size()) * l[i]);

    return si;
}

int main(){
    cin >> n >> m;
    FOR(i, 1, n){
        cin >> p[i] >> s[i] >> l[i];
        c[p[i]].push_back(i);
    }

    dfs(1);
    cout << res << endl;
}
