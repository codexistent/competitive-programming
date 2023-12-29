#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main(){
    int N, M = 0;
    cin >> N;
    vector<pair<int, int> > P[N + 1];
    int D[N + 2], PG[N + 1];
    fill(D, D + N + 2, 0);
    fill(PG, PG + N + 1, 0);

    FOR(i, 1, N){
        int a, b;
        cin >> a >> b;
        if(a == 1) {
            P[b].push_back(make_pair(i, M));
            M++;
        }else{
            if(P[b].empty()) {
                cout << "-1" << endl;
                return 0;
            }else{
                PG[P[b][P[b].size() - 1].second] = 1;
                D[P[b][P[b].size() - 1].first] += 1;

                D[i + 1] += -1;
                P[b].erase(P[b].end() - 1);
            }
        }
    }

    int K = 0, PFX = 0;
    FOR(i, 1, N){
        PFX += D[i];
        K = max(K, PFX);
    }

    cout << K << endl;

    FOR(i, 1, M - 1) cout << PG[i - 1] << " ";
    if(M != 0) cout << PG[M - 1] << endl;
}
