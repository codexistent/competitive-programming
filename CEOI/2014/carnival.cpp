#include <iostream>
#include <vector>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define MAXN 155

int main(){
    int n, c; cin >> n;
    cout << n << " "; FOR(i, 1, n) cout << i << " "; cout << endl;
    cin >> c;

    vector<int> r(n + 1), tp;
    FOR(i, 1, n) r[i] = -1;
    r[1] = 1, tp.push_back(1);

    int prev = 1;
    FOR(i, 2, n){
        cout << i << " "; FOR(j, 1, i) cout << j << " "; cout << endl;

        int cur; cin >> cur;
        if(cur != prev){
            r[i] = r[tp[tp.size() - 1]] + 1;
            tp.push_back(i);
        }
        prev = cur;
    }

    FOR(i, 1, n) if(r[i] == -1) {
        int a = 1, b = c;
        while(a < b){
            int m = (a + b) / 2;
            cout << (m + 1) << " " << i << " ";
            FOR(j, 1, m){
                cout << tp[j - 1] << " ";
            }
            cout << endl;

            int x; cin >> x;
            if(x == m) {
                b = m;
            }else{
                a = m + 1;
            }
        }

        r[i] = a;
    }

    cout << 0 << " ";
    FOR(i, 1, n) cout << r[i] << " ";
    cout << endl;
}
