#include "coins.h"
 
std::vector<int> coin_flips(std::vector<int> b, int c) {
    std::vector<int> flips(1);
    int xr = 0;
    for(int i = 0; i < 64; i++) if(b[i]) xr ^= i;
 
    xr %= 64;
    flips[0] = xr ^ c;
 
    return flips;
}
 
int find_coin(std::vector<int> b) {
    int xr = 0;
    for(int i = 0; i < 64; i++) if(b[i]) xr ^= i;
 
    xr %= 64;
    return xr;
}
