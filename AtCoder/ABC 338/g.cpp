#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ll long long

int main(){
    string s;
    cin >> s;
    int n = s.length();

    ll r = 0;
    ll ms = 0, cs = 0, os = 0;
    ll mv = 1, cv = 0;
    ll ot = 0, mt = 0, ct = 0;
    FOR(i, 1, n){
        if(s[i - 1] == '+' || s[i - 1] == '*'){
            if(s[i - 1] == '+'){
                os = (os + (ot * ((mv * cv) % MOD)) % MOD + (ms * cv % MOD + cs) % MOD) % MOD, ms = 0, cs = 0;
                mv = 1, cv = 0;
                ot = (ot + (mt + ct) % MOD) % MOD, mt = ct = 0;
            }else{
                ms = (ms * cv % MOD + cs) % MOD, cs = 0;
                mv = (mv * cv) % MOD, cv = 0;
                mt = (mt + ct) % MOD, ct = 0;
            }
            continue;
        }

        int d = s[i - 1] - '0';
        ll cs2 = (cs * 10 + (ct + 1) * d) % MOD, cv2 = (cv * 10 + d) % MOD;

        r = (r + os + ((ot * mv) % MOD) * cv2) % MOD;
        r = (r + ms * cv2) % MOD;
        r = (r + cs2) % MOD;

        cs = cs2, cv = cv2, ct++;
    }

    cout << r << endl;
}
