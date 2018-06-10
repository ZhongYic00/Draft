#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <string.h>
#define N 1600000
using namespace std;
int n,m,k,p,T;
/*void add(int &fi,int &ti,int &wi)
{
    e[++num]=ti,nt[num]=p[fi],w[num]=wi,p[fi]=num,tp[ti]++;
}*/
void read(int &x)
{
    register char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return;
}
int main()
{
    cin>>T;
    while(T--)
    {
        read(n),read(m),read(k),read(p);
        for(int i=1;i<=m;i++)
        {
            read(ai),read(bi),read(ci);
            add(ai,bi,ci);
        }
        dim[1]=0;
        spfa();
        for(int i=0;i<=k;i++)
        {

        }
    }
    return 0;
}
