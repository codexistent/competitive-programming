#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)
#define MAXN 1005

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

int H, W, G[MAXN][MAXN];
bool V[MAXN][MAXN];
bool red[MAXN][MAXN];
static vector<pair<int, int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void dfs(int i, int j, int g){
    if(!(1 <= i && i <= H && 1 <= j && j <= W) || V[i][j] || red[i][j]) return;
    V[i][j] = true;

    G[i][j] = g;

    FOR(d, 0, 3) dfs(i + dir[d].first, j + dir[d].second, g);
}

int main(){
    cin >> H >> W;
    int cc = 0;

    FOR(i, 0, MAXN - 1) FOR(j, 0, MAXN - 1) red[i][j] = true;

    FOR(i, 1, H){
        string s;
        cin >> s;
        FOR(j, 1, W){
            red[i][j] = s[j - 1] == '.';
            V[i][j] = false; 
        }
    }

    FOR(i, 1, H) FOR(j, 1, W) if(!red[i][j] && !V[i][j]) {
        dfs(i, j, cc);
        cc++;
    }

    ll p = 0, q = 0;
    FOR(i, 1, H){
        FOR(j, 1, W){
            if(red[i][j]){
                set<int> see;
                FOR(d, 0, 3){
                    if(!red[i + dir[d].first][j + dir[d].second]){
                        see.insert(G[i + dir[d].first][j + dir[d].second]);
                    }
                }

                p += (cc - (int)(see.size() - 1));
                q++;
            }
        }
    }

    cout << mod998244353(p, q) << endl;

}
