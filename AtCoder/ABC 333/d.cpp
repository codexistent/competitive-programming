#include <iostream>
#include <vector>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

vector<bool> V;
vector<int> E[300005];

int dfs(int n){
    if(V[n]) return 0;
    V[n] = true;

    int r = 0;
    for(int e : E[n]) r += dfs(e);

    if(E[n].size() == 1) r = 0;

    //cout << n + 1 <<  " ~ " << r + 1 << endl;

    return r + 1;
}

int main(){
    int N;
    cin >> N;
    FOR(i, 1, N - 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        E[a].push_back(b), E[b].push_back(a);
    }

    V.assign(N, false);
    int R = 0, S = 0;
    V[0] = true;
    for(int e : E[0]) {
        int D = dfs(e);
        R = max(R, D);
        S += D;
    }

    cout << S - R + 1 << endl;
}
