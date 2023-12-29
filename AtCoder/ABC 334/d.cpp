#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)

int main(){
    int N, Q;
    cin >> N >> Q;
    ll R[N];
    FOR(i, 0, N - 1) cin >> R[i];
    sort(R, R + N);

    ll S[N + 1]; S[0] = 0;
    FOR(i, 1, N) S[i] = S[i - 1] + R[i - 1];

    FOR(i, 1, Q){
        ll q;
        cin >> q;
        int a = 0, b = N;
        while(a < b){
            int m = (a + b + 1) / 2;
            if(S[m] <= q){
                a = m;
            }else{
                b = m - 1;
            }
        }
        cout << a << endl;
    }
}
