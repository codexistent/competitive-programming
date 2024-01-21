#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
#define mp make_pair
#define f first
#define s second

struct BCC { // gets all bi-connected components of an undirected graph
    int n, count = 0;
    vector<vector<pair<int, int>>> c;
    BCC (int n, const vector<vector<int>>& e) : n(n){
        compute_bccs(e);
    }
private:
    int timer = 0;
    void compute_bccs(const vector<vector<int>>& e){
        int m = 0; for(auto v : e) m += v.size();

        int* tin = new int[n];
        int* low = new int[n];
        int* p = new int[n];
        list<pair<int, int>>* s = new list<pair<int, int>>[m];
        FOR(i, 0, n - 1) tin[i] = low[i] = p[i] = -1;

        FOR(i, 0, n - 1) {
            if(tin[i] == -1) {
                timer = 0;
                dfs1(i, tin, low, s, p, e);
            }

            if(s->size()){
                vector<pair<int, int>> v;
                while(s->size() > 0){
                    v.pb(s->back());
                    s->pop_back();
                }
                c.push_back(v);
            }
        }
    }

    void dfs1(int v, int tin[], int low[], list<pair<int, int>>* s, int p[], const vector<vector<int>>& e){
        tin[v] = low[v] = ++timer;
        int ch = 0;

        for(int to : e[v]){
            if(tin[to] == -1){
                ch++;
                p[to] = v, s->pb(mp(v, to));

                dfs1(to, tin, low, s, p, e);

                low[v] = min(low[v], low[to]);

                if((tin[v] == 1 && ch > 1) || (tin[v] > 1 && low[to] >= tin[v])){
                    vector<pair<int, int>> cc;
                    while(s->back().f != v || s->back().s != to) {
                        cc.pb(s->back());
                        s->pop_back();
                    }
                    cc.pb(s->back());
                    s->pop_back();
                    c.pb(cc);
                }
            }else if(to != p[v]){
                low[v] = min(low[v], tin[to]);
                if(tin[v] > tin[to]) s->pb(mp(v, to));
            }
        }
    }
};

int main() {
  
}
