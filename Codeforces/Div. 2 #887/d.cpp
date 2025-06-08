#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 200005
#define fs first 
#define sc second 

ll n, q;
set<ll> st;

// LESSON: CHECK IF SOME CONSTRAINTS ALREADY LEAD TO VALIDITY / YOUR CONSTRAINTS TOO COMPLICATED
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    string s; cin >> s;
    FOR(i, 0, n - 1){
        if((s[i] == '(' && i % 2 == 1) || (s[i] == ')' && i % 2 == 0)){
            st.insert(i);
        }
    }

    FOR(qi, 1, q){
        ll i; cin >> i; i--;
        if((s[i] == '(' && i % 2 == 1) || (s[i] == ')' && i % 2 == 0)){
            st.erase(i);
        }else{
            st.insert(i);
        }

        s[i] = (s[i] == '(') ? ')' : '(';

        if(n % 2 == 0 && ((ll)st.size() == 0 || (*(st.begin()) % 2 == 1 && *(st.rbegin()) % 2 == 0))){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
}
