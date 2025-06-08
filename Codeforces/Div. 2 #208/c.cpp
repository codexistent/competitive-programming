#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 100005
#define fs first 
#define sc second

ll n, a[MAXN], t[MAXN];
priority_queue<pair<ll, ll>> pq;
string ts[4] = {"popQueue", "popStack", "popFront", "popBack"};
string qs[4] = {"pushBack", "pushQueue", "pushStack", "pushFront"};

// LESSON: READ PROBLEM MORE CAREFULLY
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    FOR(i, 1, n){
        cin >> a[i];
        if(a[i]){
            pq.push({a[i], i});
            t[i] = 0;
        }else{
            FOR(j, 1, 3) if(pq.size()){
                auto pqi = pq.top(); pq.pop();
                t[pqi.sc] = j;
                a[i]--;
            }
            while(pq.size()) pq.pop();
        }
    }

    FOR(i, 1, n){
        if(a[i] <= 0){
            a[i] *= -1;
            cout << a[i];
            FOR(j, 1, a[i]){
                cout << ' ' << ts[j - 1];
            }
        }else{
            cout << qs[t[i]];
        }
        cout << endl;
    }
}
