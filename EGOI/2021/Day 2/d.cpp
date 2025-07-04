#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(ict, ist, ied) for(ll ict = ist; ict <= ied; ict++)
#define MAXN 40
 
struct frc{
    ll fn, fd;
    inline bool operator < (const frc g) const{
        return fn * g.fd < fd * g.fn;
    }
 
    inline frc operator * (frc g){
        frc f2 = {fn * g.fn, fd * g.fd};
        ll dv = __gcd(f2.fn, f2.fd);
        assert(dv);
        return {f2.fn / dv, f2.fd / dv};
    }
};
inline frc operator - (ll x, frc g){
    frc f2 = {x * g.fd - g.fn, g.fd};
    ll dv = __gcd(f2.fn, f2.fd);
    return {f2.fn / dv, f2.fd / dv};
}

// LESSON: UNDERSTAND SOL MORE!!! + MT
ll n, k, g[MAXN], sz[MAXN], e[MAXN], RES = 0ll, MUL = 1ll;
map<vector<int>, frc> mp;
frc fr;
 
ll find(ll x) { return (g[x] == x) ? x : (g[x] = find(g[x])); }
ll fpow(ll b, ll x){
    if(x == 0) return 1ll;
    ll r = fpow(b, x / 2);
    return r * r * (1 + (b - 1) * (x % 2));
}
 
frc dfs(ll mv, vector<int> v){
    if(mv == n + 1) return {0, 1};
    if(mp.count(v)) return mp[v];
 
    mp.insert({v, {-1, 1}});
    vector<int> v2 = v;
    FOR(i, 1, n){
        if(!v[i]) continue;
        
        v2[i]--;
        mp[v] = max(mp[v], (frc){2, i} * (fpow(2, n + 1 - mv) - dfs(mv + 1, v2)));
        FOR(j, 1, n){
            if(!v2[j]) continue;
            
            v2[j]--; v2[i + j]++;
            mp[v] = max(mp[v], (frc){i + j, i * j} * (fpow(2, n + 1 - mv) - dfs(mv + 1, v2)));
            v2[j]++; v2[i + j]--;
        }
        v2[i]++;
    }
    return mp[v];
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n >> k;
    FOR(i, 1, n) g[i] = i, sz[i] = 1ll, e[i] = 0ll;
 
    vector<int> v(n + 1, 0);
    FOR(i, 1, k){
        ll a, b; cin >> a >> b;
        a = find(a), b = find(b);
 
        if(a == b){
            e[a]++;
            if(e[a] > sz[a]){
                if(i % 2 == 0) RES += fpow(2, n + 1 - (i - 1)) * MUL;
                cout << RES << ' ' << (fpow(2, n + 1) - RES) << '\n';
                return 0;
            }
            if(i % 2 == 0) RES += fpow(2, n + 1 - (i - 1)) * MUL / sz[a] * (sz[a] - 1);
            MUL = MUL / sz[a] * 2;
        }else{
            if(e[a] == sz[a] && e[b] == sz[b]){
                if(i % 2 == 0) RES += fpow(2, n + 1 - (i - 1)) * MUL;
                cout << RES << ' ' << (fpow(2, n + 1) - RES) << '\n';
                return 0;
            }
            
            if(i % 2 == 0){
                if(sz[a] > e[a]) RES += fpow(2, n + 1 - i) * (MUL / sz[a] * (sz[a] - 1));
                else RES += fpow(2, n + 1 - i) * MUL;
                
                if(sz[b] > e[b]) RES += fpow(2, n + 1 - i) * (MUL / sz[b] * (sz[b] - 1));
                else RES += fpow(2, n + 1 - i) * MUL;
            }
 
            if(sz[a] > e[a]) MUL /= sz[a];
            else MUL /= 2;
 
            if(sz[b] > e[b]) MUL /= sz[b];
            else MUL /= 2;
 
            if(sz[a] < sz[b]) swap(a, b);
 
            g[a] = g[b] = a;
            sz[a] += sz[b];
            e[a] += e[b] + 1;
 
            if(sz[a] > e[a]) MUL *= sz[a]; 
            else MUL *= 2;
        }
    }
 
    FOR(i, 1, n) if(find(i) == i) if(sz[i] > e[i]) v[sz[i]]++;
    fr = dfs(k + 1, v);
    if((k + 1) % 2) RES += MUL * fr.fn / fr.fd;
    else RES += MUL * fpow(2, n + 1 - k) - MUL * fr.fn / fr.fd;
 
    cout << RES << ' ' << (fpow(2, n + 1) - RES) << '\n';
}
close
