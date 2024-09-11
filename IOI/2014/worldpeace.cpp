#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define MAXN 100005

int n, m, p[MAXN], sz[MAXN];

int find(int x){
    return (p[x] == x) ? x : (p[x] = find(p[x]));
}

void onion(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return;

    if(sz[a] > sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
}

int main(){
    priority_queue<pair<int, pair<int, int>>> eq;

    cin >> n >> m;
    FOR(i, 1, m){
        int a, b, w; cin >> a >> b >> w;
        eq.push({-w, {a, b}});
    }

    FOR(i, 1, n){
        p[i] = i, sz[i] = 1; 
    }

    int mxw = 0, rq; cin >> rq;
    FOR(i, 1, rq){
        int a, b; cin >> a >> b;
        while(find(a) != find(b) && !eq.empty()){
            auto e = eq.top();
            mxw = -e.first;
            onion(e.second.first, e.second.second);
            eq.pop();
        }

        if(find(a) != find(b)){
            cout << "MISSION IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << mxw << endl;
}
