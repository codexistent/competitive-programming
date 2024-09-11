// Key to solution lies in the fact that you cannot have more than 1 full-circle trip.
// PROOF: Assume you have 2 full-circle trips. Then you travel 2L time and deliver >= 2K souvenirs.
//        But we can easily just deliver the first k souvenirs(from clockwise direction) in 2 * x time going 
//        clockwise and deliver the first k souvenirs(from counter-clockwise direction) in at most 2 * (l - x)
//        time going counter-clockwise, which is just as good if not better. □
 
#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 10000005
#define FOR(i, a, b) for(ll i = a; i <= b; i++)
#define RFOR(i, a, b) for(ll i = a; i >= b; i--)
 
ll dp_cw[MAXN], dp_ccw[MAXN], r = __LONG_LONG_MAX__;
 
long long delivery(int N, int K, int L, int p[]) {
    dp_cw[0] = dp_ccw[N + 1] = 0;
    FOR(i, 1, N) dp_cw[i] = dp_cw[max(0ll, i - K)] + 2 * p[i - 1];
    RFOR(i, N, 1) dp_ccw[i] = dp_ccw[min((ll)N + 1, i + K)] + 2 * (L - p[i - 1]);
 
    FOR(i, 0, N) r = min(r, dp_cw[i] + dp_ccw[i + 1]);
    if(N >= K) FOR(i, 0, N) r = min(r, dp_cw[i] + dp_ccw[i + K + 1] + L);
 
    return r;
}
