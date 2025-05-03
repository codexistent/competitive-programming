#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(int icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(int icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second

ll n, dp[2][4][4][4][4];
string s;
map<char, ll> fid = {{'M', 1}, {'F', 2}, {'B', 3}};

int main(){
    cin >> n >> s;
    FOR(i, 0, 1) FOR(a1, 0, 3) FOR(a2, 0, 3) FOR(b1, 0, 3) FOR(b2, 0, 3) dp[i][a1][a2][b1][b2] = -1;
    
    dp[0][0][0][0][0] = 0;
    FOR(i, 0, n - 1) {
        FOR(a1, 0, 3) FOR(a2, 0, 3) FOR(b1, 0, 3) FOR(b2, 0, 3) if(dp[i % 2][a1][a2][b1][b2] != -1){
            ll ft = fid[s[i]];

            // send to mine 1
            ll m1 = (a1 == 1 || a2 == 1 || ft == 1) + (a1 == 2 || a2 == 2 || ft == 2) + (a1 == 3 || a2 == 3 || ft == 3);
            dp[(i + 1) % 2][a2][ft][b1][b2] = max(dp[(i + 1) % 2][a2][ft][b1][b2], dp[i % 2][a1][a2][b1][b2] + m1);

            // send to mine 2
            ll m2 = (b1 == 1 || b2 == 1 || ft == 1) + (b1 == 2 || b2 == 2 || ft == 2) + (b1 == 3 || b2 == 3 || ft == 3);
            dp[(i + 1) % 2][a1][a2][b2][ft] = max(dp[(i + 1) % 2][a1][a2][b2][ft], dp[i % 2][a1][a2][b1][b2] + m2);

            dp[i % 2][a1][a2][b1][b2] = -1;
        }
    }

    ll r = 0;
    FOR(a1, 0, 3) FOR(a2, 0, 3) FOR(b1, 0, 3) FOR(b2, 0, 3) r = max(r, dp[n % 2][a1][a2][b1][b2]);

    cout << r << endl;
}
