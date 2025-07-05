#include <bits/stdc++.h>
#include "toydesign.h"
using namespace std;
#define FOR(ict, ist, ied) for(int ict = ist; ict <= ied; ict++)
#define MAXN 205
 
int g[MAXN], gp[MAXN], ga[MAXN], gn;
 
void ToyDesign(int n, int max_ops){
	gn = 1, g[1] = 1, ga[1] = 0, gp[1] = 1;
	FOR(i, 2, n){
		int lo = 1, hi = gn + 1;
		int ai = 0;
		while(lo < hi){
			int md = (lo + hi) / 2;
			
			if(md == gn + 1 || (ai = Connected(ga[md], gp[md], i)) == ga[md]){
				hi = md;
			}else{
				lo = md + 1;
			}
		}
 
		if(hi == gn + 1){
			g[i] = ++gn;
			gp[gn] = i;
			ga[gn] = ai;
		}else{
			g[i] = lo;
		}
	}
 
	vector<pair<int, int>> vc;
	FOR(i, 1, n){
		if(gp[g[i]] != i){
			vc.emplace_back(gp[g[i]], i);
		}
	}
 
	DescribeDesign(vc);
	return;
}
