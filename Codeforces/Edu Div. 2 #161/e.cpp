#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define mp make_pair

void solve(){
    ll n;
    cin >> n;
    vector<int> r;
    int a = -1000, b = 1000;
    while(n > 1){
        if(n & 1) {
            r.push_back(++a);
            n--;
        } else{
            r.push_back(--b);
            n /= 2;
        }
    }

    reverse(begin(r), end(r));
    cout << r.size() << endl;
    for(int i : r) cout << i << " ";
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    FOR(i, 1, t) solve();
}
