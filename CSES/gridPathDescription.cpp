#include <bits/stdc++.h>
using namespace std;

string s;
int r=0,m=0;
bool b[8][8];

void bfs(int i,int j){
    b[i][j]=true,m++;

    if(m==49){
        r+=(i==1&&j==1);
    }else{
        char L=(1<=i-1&&!b[i-1][j]&&(s[m-1]=='?'||s[m-1]=='L'));
        char R=(i+1<=7&&!b[i+1][j]&&(s[m-1]=='?'||s[m-1]=='R'));
        char U=(j+1<=7&&!b[i][j+1]&&(s[m-1]=='?'||s[m-1]=='U'));
        char D=(1<=j-1&&!b[i][j-1]&&(s[m-1]=='?'||s[m-1]=='D'));
        if(i==1&&j==1)goto pt1;
        if(!L&&!R&&U&&D)goto pt1;
        if(!U&&!D&&R&&L)goto pt1;

        if(L)bfs(i-1,j);
        if(R)bfs(i+1,j);
        if(D)bfs(i,j-1);
        if(U)bfs(i,j+1);
    }
    
    pt1: b[i][j]=false,m--;
    return;
}

main(){
    cin>>s;
    bfs(1,7);
    cout<<r<<endl;
}
