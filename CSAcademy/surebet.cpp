#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define db double

main(){
    int n;
    cin >> n;

    db r = 0.0, atot = 0.0, btot = 0.0, x;

    priority_queue<db> a, b;
    for(int i = 0; i < n; i++) {
        cin >> x, a.push(x);
        cin >> x, b.push(x);
    }

    for(int i = 1; i <= 2*n; i++){
        if(b.empty() || (a.size() && atot < btot)) atot += a.top(), a.pop();
        else btot += b.top(), b.pop();

        r = max(r, min(atot - i, btot - i));
    }
    printf("%.4lf",(double)r);
}
