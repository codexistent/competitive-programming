#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; i++)

int main(){
    int N;
    cin >> N;
    int A[N + 1];
    A[0] = 0;
    FOR(i, 1, N) cin >> A[i];

    int R[N + 1], L[N + 2];
    R[0] = 0;
    FOR(i, 1, N) {
        R[i] = 1;
        if(R[i - 1] + 1 <= A[i]) R[i] = max(R[i], R[i - 1] + 1);
        else if(A[i] <= R[i - 1]) R[i] = max(R[i], A[i]);
    }

    L[N + 1] = 0;
    for(int i = N; i >= 1; i--){
        L[i] = 1;
        if(L[i + 1] + 1 <= A[i]) L[i] = max(L[i], L[i + 1] + 1);
        else if(A[i] <= L[i + 1]) L[i] = max(L[i], A[i]);
    }

    int RET = 0;
    FOR(i, 1, N){
        if(R[i] != L[i + 1]) RET = max(RET, min(R[i], L[i + 1]) + 1);
        else RET = max(RET, R[i] - 1);
    }

    cout << RET << endl;
}
