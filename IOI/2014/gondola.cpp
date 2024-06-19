#include <bits/stdc++.h>
#include <gondola.h>
using namespace std;
#define MOD 1000000009
#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)
 
int diff(int n, int a, int b){
    if(b >= a) return b - a;
    else return (n - a) + b;
}
 
ll pwr(ll b, ll exp){
    if(exp == 0) return 1;
    if(exp == 1) return b;
    ll x = pwr(b, exp / 2) % MOD;
    return (((x * x) % MOD) * ((exp % 2 == 0) ? 1 : b)) % MOD;
}
 
int valid(int n, int inputSeq[]){
    pair<int, int> prev = make_pair(-1, 0);
    set<int> s;
    FOR(i, 0, n - 1){
        if(inputSeq[i] <= n){
            if(prev.first == -1){
                prev = make_pair(i, inputSeq[i]);
            }else{
                if((((prev.second + diff(n, prev.first, i)) % n) == 0 ? n : ((prev.second + diff(n, prev.first, i)) % n)) != inputSeq[i]) return 0;
                prev = make_pair(i, inputSeq[i]);
            }
        }else{
            if(s.find(inputSeq[i]) != s.end()) return 0;
            s.insert(inputSeq[i]);
        }
    }
 
    return 1;
}
 
int replacement(int n, int gondolaSeq[], int replacementSeq[]){
    int idx = -1, mx = -1;
    vector<pair<int, int> > v;
    FOR(i, 0, n - 1){
        if(gondolaSeq[i] <= n){
            idx = gondolaSeq[i] - i;
            if(idx <= 0) idx += n;
        }else{
            v.push_back(make_pair(gondolaSeq[i], i));
        }
        mx = max(mx, gondolaSeq[i]);
    }
    sort(v.begin(), v.end());
 
    if(idx == -1) idx = 1;
 
    set<int> s;
    FOR(i, 0, (int)(v.size() - 2)) {
        s.insert(v[i].first);
        replacementSeq[v[i].first - n - 1] = ((idx + v[i].second) % n == 0) ? n : ((idx + v[i].second) % n);
    }
 
    if(v.size()){
        int prev = ((idx + v[v.size() - 1].second) % n == 0) ? n : ((idx + v[v.size() - 1].second) % n);
        FOR(i, n + 1, mx) {
            if(s.find(i) == s.end()) {
                replacementSeq[i - (n + 1)] = prev;
                prev = i;
            }
        }
    }
    return mx - n;
}
 
int countReplacement(int n, int inputSeq[]){
    if(!valid(n, inputSeq)) return 0;
    ll r = 1;
    int c = 0, mx = -1;
    set<int> s;
    bool fct = true;
    FOR(i, 0, n - 1){
        if(inputSeq[i] <= n) fct = false;
        else{
            c++, s.insert(inputSeq[i]);
        }
        mx = max(mx, inputSeq[i]);
    }
 
    int c2 = 0;
    ll k = n;
    for(int k2 : s){
        r = (r * pwr(c - c2, k2 - k - 1)) % MOD;
        k = k2, c2++;
    }
    if(fct){
        r = (r * (ll)(n)) % MOD;
    }
    return r;
}
