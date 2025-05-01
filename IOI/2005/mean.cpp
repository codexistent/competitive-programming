#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(icounter, istart, iend) for(int icounter = istart; icounter <= iend; icounter++)
#define RFOR(icounter, istart, iend) for(int icounter = istart; icounter >= iend; icounter--)
#define fs first 
#define sc second

ll n;
int arr[5000005];

int main(){
  cin >> n;
  FOR(i, 1, n) {
    cin >> arr[i];
    if(i != 1 && arr[i - 1] > arr[i]){
      cout << 0 << endl;
      return 0;
    }
  }

  pair<int, int> rng = {2*arr[1] - arr[2], arr[1]};

  FOR(i, 2, n - 1){
    rng = {2*arr[i - 1] - rng.sc, 2*arr[i - 1] - rng.fs};
    rng.fs = max(rng.fs, 2*arr[i] - arr[i + 1]);
  }

  cout << max(0, rng.sc - rng.fs + 1) << endl;
}
