#include <cstdio>
#include <cstring>
#include <iostream>
#define N 81
using namespace std;
struct STOP
{
    int k,x;
    STOP operator+(const STOP &x)
    {
        STOP y=*(this);
        y.x+=x.x,y.k+=x.k;
        return y;
    }
}on[N],stop[N],last;
int main()
{
    int a,n,m,q,X;
    scanf("%d%d%d%d",&a,&n,&m,&q);
    stop[1].k=a,on[1].k=a,on[2].x=1;
    for(int i=2;i<n;i++)
    {
        on[i+1]=on[i]+on[i-1];
        stop[i]=stop[i-1]+on[i-2];
    }
    last=stop[n-1];
    X=(m-last.k)/last.x;
    printf("%d",stop[q].k+stop[q].x*X);
}
