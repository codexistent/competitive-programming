#include <bits/stdc++.h>
using namespace std;
#define int long long 

main(){
    int n, k, r = 0;
    cin >> n >> k;

    vector<array<int, 2>> m;
    for(int i = 1, a, b; i <= n; i++){
        cin >> a >> b;
        m.push_back({b, a});
    }
    sort(begin(m), end(m));

    multiset<int> ed;
    for(int i = 1; i <= k; i++) ed.insert(0);
    for(auto mi : m){
        if(-*ed.rbegin() <= mi[1]){
            r++;
            ed.erase(ed.lower_bound(-mi[1]));
            ed.insert(-mi[0]);
        }
    }

    cout << r << endl;
}
