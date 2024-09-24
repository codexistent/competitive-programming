#include <bits/stdc++.h>
using namespace std;
#define MAXN 500001
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define f first
#define s second

int n, r = 0;
int c[MAXN];
pair<int, int> e1[MAXN], e2[MAXN], r1[MAXN], r2[MAXN];

int main(){
    cin >> n;
    FOR(i, 1, n) c[i] = 0;
    FOR(i, 1, n){
        int j; cin >> j;
        e1[i] = {i, j};
        e2[i] = {j, i};
        ++c[i]; ++c[j];

        r1[i] = r2[i] = {-1, -1};
    }
    sort(e1 + 1, e1 + 1 + n);
    sort(e2 + 1, e2 + 1 + n);

    FOR(i, 1, n){
        if(r1[e1[i].first].first == -1){
            r1[e1[i].first] = {i, i};
        }
        r1[e1[i].first].second = i;
    }
    FOR(i, 1, n){
        if(r2[e2[i].first].first == -1){
            r2[e2[i].first] = {i, i};
        }
        r2[e2[i].first].second = i;
    }

    priority_queue<pair<int, int>> pq;
    FOR(i, 1, n) pq.push({-c[i], i});

    while(pq.size()){
        auto pqi = pq.top(); pq.pop();
        if(c[pqi.s] == -1) continue;
        c[pqi.s] = -1;

        r++;
        FOR(i, r1[pqi.second].first, r1[pqi.second].second){ int j = e1[i].second;
            FOR(i2, r1[j].first, r1[j].second){ int k = e1[i2].second;
                if(c[k] == -1) continue;
                --c[k];
                pq.push({-c[k], k});
            }
            FOR(i2, r2[j].first, r2[j].second){ int k = e2[i2].second;
                if(c[k] == -1) continue;
                --c[k];
                pq.push({-c[k], k});
            }
            c[j] = -1;
            r1[j] = r2[j] = {-1, -1};
        }
        FOR(i, r2[pqi.second].first, r2[pqi.second].second){ int j = e2[i].second;
            FOR(i2, r1[j].first, r1[j].second){ int k = e1[i2].second;
                if(c[k] == -1) continue;
                --c[k];
                pq.push({-c[k], k});
            }
            FOR(i2, r2[j].first, r2[j].second){ int k = e2[i2].second;
                if(c[k] == -1) continue;
                --c[k];
                pq.push({-c[k], k});
            }
            c[j] = -1;
            r1[j] = r2[j] = {-1, -1};
        }
    }

    cout << r << endl;
}
