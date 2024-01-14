#include <bits/stdc++.h>
using namespace std;
#define  FOR(i, a, b) for(int i = a; i  <= b; i++)

int main(){
    int n, ct = 0;
    cin >> n;
    while((n & 1) == 0){
        n = n >> 1;
        ct++;
    }

    cout << ct << endl;
}
