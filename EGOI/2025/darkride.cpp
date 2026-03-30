#include <bits/stdc++.h>
using namespace std;

int n, xr = 0;
vector<int> v;

main(){
    cin>>n;
    for(int i = 0, q; i < 15; i++){
        string s(n, '0');
        for(int j = 0; j < n; j++) s[j] += ((j >> i) & 1);
        cout << "? " << s << endl, cin >> q;
        if(q%2){
            xr |= (1 << i);
            if(v.empty()) for(int j = 0; j < n; j++) if(s[j] == '0') v.emplace_back(j);
        }
    }

    int l = 0, r = v.size()-1;
    while(l < r){
        int m = (l + r)/2, q;
        string s(n, '0');
        for(int i = l; i <= m; i++) s[v[i]]++;
        cout << "? " << s << endl, cin >> q;
        if(q%2) r = m; else l = m + 1;
    }
    cout << "! " << v[l] << ' ' << (v[l]^xr) << endl;
}
