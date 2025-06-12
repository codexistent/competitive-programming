#include <bits/stdc++.h>
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define fs first 
#define sc second

// LESSONZ: TRY/FIND MORE PATTERNS OR ASSOCIATIONS
//          DONT GET TOO CAUGHT UP IN THE ALGO
//          XORS NEED PARENTHESES AROUND THEM WHEN IN EQUATIONS, ESP. BOOL EXPRESSIONS
//          RPH PR
//          TRY MOD STUFF, CONVERT STUFF TO NUMBERS, DRAW EDGES BETWEEN STUFF
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    next: while(t--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<vector<pair<int, bool>>> adj(n + m); // second value is for xor
        FOR(ki, 1, k){
            pair<int, int> a, b;
            cin >> a.fs >> a.sc >> b.fs >> b.sc;
            if(b.sc == a.sc + 1){
                adj[a.fs].emplace_back((n - 1) + a.sc, 1); // same
                adj[(n - 1) + a.sc].emplace_back(a.fs, 1);
            }else{
                adj[a.fs].emplace_back((n - 1) + b.sc, 0); // diff
                adj[(n - 1) + b.sc].emplace_back(a.fs, 0);
            }
        }

        vector<short> col(n + m, -1);
        FOR(i, 1, (n - 1) + (m - 1)){
            if(col[i] == -1){
                queue<int> q;
                col[i] = 0;
                q.push(i);
                while(q.size()){
                    int qi = q.front(); q.pop();
                    
                    for(auto i2 : adj[qi]){
                        if(col[i2.fs] == (col[qi] ^ i2.sc)) {
                            cout << "NO\n";
                            goto next;
                        }
                        if(col[i2.fs] == -1){
                            q.push(i2.fs);
                            col[i2.fs] = col[qi] ^ i2.sc ^ 1;
                        }
                    }
                }
            }
        }

        cout << "YES\n";
    }
}
