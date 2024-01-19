#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

void solve(){
    int n;
    string a, b, c;
    cin >> n >> a >> b >> c;

    bool valid = false;
    FOR(i, 0, n  - 1){
        if(a[i] == b[i] && a[i] != c[i]){
            valid = true;
        }else if(a[i] != c[i] && b[i] != c[i]){
            valid = true;
        }
    }
    cout << ((valid) ? "YES" : "NO") << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    FOR(i, 1, t) solve();
}
