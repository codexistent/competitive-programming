#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll mod998244353(ll p, ll q){
    ll mod = 998244353, pow;
    pow = mod - 2;
    while(pow){
        if(pow & 1) p = (p * q) % mod;
        q = (q * q) % mod;

        pow >>= 1;
    }
    return p;
}

int main(){
}
