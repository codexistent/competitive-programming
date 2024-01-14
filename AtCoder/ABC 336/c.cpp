#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main(){
    long long N;
    cin >> N;
    N--;
    vector<int> d;
    while(N){
        d.push_back(N % 5);
        N /= 5;
    }

    if(d.empty()) d.push_back(0);

    reverse(begin(d), end(d));

    for(int i : d) cout << i*2;
}
