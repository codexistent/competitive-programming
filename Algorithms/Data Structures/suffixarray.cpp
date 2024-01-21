#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)
#define LOGN 25

struct SuffixArray {
    int n;
    string s;
    vector<int> rank, order, clcp;
    vector<vector<int>> st;
    SuffixArray(string const& str): s(str + '$'){
        n = s.length();
        rank.resize(n), order.resize(n);
        rank_suffixes();
        lcp_prep();
    }

    int lcp(int a, int b){
        int l = min(rank[a], rank[b]), r = max(rank[a], rank[b]) - 1, res = INT_MAX;
        RFOR(i, LOGN, 0){
            if((1 << i) <= r - l + 1) {
                res = min(res, st[i][l]);
                l += 1 << i;
            }
        }

        return (res == INT_MAX) ? 0 : res;
    }

private:
    void rank_suffixes() {
        const int ascii_range = 256;

        // counting sort
        vector<int> ct(max(n, ascii_range), 0);
        for(char c : s) ct[c]++;
        FOR(i, 1, ascii_range - 1) ct[i] += ct[i - 1];

        vector<int> p(n), c(n);
        FOR(i, 0, n - 1) p[--ct[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 0;
        FOR(i, 1, n - 1) {
            if(s[p[i]] != s[p[i - 1]]) classes++;
            c[p[i]] = classes - 1;
        }

        // radix sort
        vector<int> p2(n), c2(n);
        for(int l = 0; (1 << l) < n; ++l){
            FOR(i, 0, n - 1) {
                p2[i] = p[i] - (1 << l);
                if(p2[i] < 0) p2[i] += n;
            }
            fill(begin(ct), begin(ct) + classes, 0);
            FOR(i, 0, n - 1) ct[c[p2[i]]]++;
            FOR(i, 1, classes - 1) ct[i] += ct[i - 1];
            RFOR(i, n - 1, 0) p[--ct[c[p2[i]]]] = p2[i];

            c2[p[0]] = 0;
            classes = 1;
            FOR(i, 1, n - 1){
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << l)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << l)) % n]};

                if(cur != prev) ++classes;
                c2[p[i]] = classes - 1;
            }
            swap(c, c2);
        }

        swap(order, p);
        FOR(i, 0, n - 1) rank[order[i]] = i;
    }
    void lcp_prep(){
        clcp.assign(n - 1, 0);
        int k = 0;
        FOR(i, 0, n - 1){
            if(rank[i] == n - 1) {
                k = 0;
                continue;
            }

            int j = order[rank[i] + 1];
            while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            clcp[rank[i]] = k;

            if(k) k--;
        }

        st.push_back(clcp);
        FOR(i, 1, LOGN){
            vector<int> v; 
            for(int j = 0; j + (1 << i) < n; j++){
                v.push_back(min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));
            }
            st.push_back(v);
        }
    }
};

int main(){
}
