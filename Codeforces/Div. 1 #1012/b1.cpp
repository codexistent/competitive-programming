#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 200005

ll n, k, r, a[2 * MAXN], b[2 * MAXN];

// LESSON: WHEN CYCLIC, EXTEND CHAIN
// LESSON: EVEN WHEN READ SOL, ONLY TAKE IT AS PART BEFORE READING CODE
// LESSON: FULLY UNDERSTAND SOL

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;
    while(t--) {
        cin >> n >> k;
        FOR(i, 1, n) cin >> a[i];
        a[0] = 0ll;
        FOR(i, 1, n) {
            cin >> b[i];
            a[i] = a[i + n] = a[i] - b[i];
        }
        FOR(i, 2, 2 * n) a[i] += a[i - 1];

        stack<ll> st;
        r = 1ll;
        for(ll i = 2 * n; i >= 1; i--){
            while(st.size() && a[st.top()] > a[i]) st.pop();
            if(i <= n) r = max(r, st.top() - i);
            st.push(i);
        }

        cout << r << endl;
    }
}
