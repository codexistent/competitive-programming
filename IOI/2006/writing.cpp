#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(int icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(int icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second

int g, n, ct[200];
bool lw[200];
string w, s;
int rm = 0, r = 0;
map<char, int> tg;

int main(){
  FOR(i, 0, 199) lw[i] = false, ct[i] = 0;

  cin >> g >> n >> w >> s;
  for(char c : w){
    if(tg.find(c) == tg.end()){
      tg.insert({c, 0});
    }
    tg[c]++;
    lw[c] = true;
  }

  if(g > n){
    cout << 0 << endl;
    return 0;
  }

  FOR(i, 1, n){
    int old1, new1, old2 = -1, new2 = -1;

  	old1 = ct[s[i - 1]];
    ct[s[i - 1]]++;
  	new1 = ct[s[i - 1]];

    if(1 <= i - g){
      old2 = ct[s[i - g - 1]];
      ct[s[i - g - 1]]--;
      new2 = ct[s[i - g - 1]];
    }

    if(i <= g || s[i - 1] != s[i - g - 1]){
      if(lw[s[i - 1]]){
        if(tg[s[i - 1]] == old1) rm--;
        else if(tg[s[i - 1]] == new1) rm++;
      }

      if(old2 != -1 && lw[s[i - g - 1]]){
        if(tg[s[i - g - 1]] == old2) rm--;
        else if(tg[s[i - g - 1]] == new2) rm++;
      }
    }

    if(rm == tg.size()) r++;
  }

  cout << r << endl;
}
