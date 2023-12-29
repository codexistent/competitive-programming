#include <iostream>
using namespace std;

int main(){
    string A, B;
    cin >> A >> B;
    int a, b, x, y;
    a = A[0], b = A[1];
    x = B[0], y = B[1];

    if(a < b) swap(a, b);
    if(x < y) swap(x, y);

    a -= b, x -= y;

    cout << ((a == x || (a + x == 5)) ? "Yes" : "No");
 
}
