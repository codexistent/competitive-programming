#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

void solve(){
    int n;
    cin >> n;
    map<int, long long> a;
    FOR(i, 1, n){
        int x;
        cin >> x;
        if(!a.count(x)) a.insert(make_pair(x, 0));
        a[x]++;
    }

    long long ret = 0;
    int prev = 0;
    for(auto p : a){
        if(p.second >= 3) ret += (p.second) * (p.second - 1) * (p.second - 2) / 6;
        if(p.second >= 2) ret += ((p.second) * (p.second - 1) / 2) * (prev);

        prev += p.second;
    }
    cout << ret << endl;
}

int main() {
    int t;
    cin >> t;
    FOR(i, 1, t) solve();
}
