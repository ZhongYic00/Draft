#include <cstdio>
#include <iostream>
#define N 1200
#define INF 2147483647
using namespace std;
short A[N],B[N];
void getstring(short* str)
{
    char ch=getchar();
    while(ch<'a'||ch>'z')ch=getchar();
    while(ch>='a'&&ch<='z')*(str++)=ch-'a'+1,ch=getchar();
}
int main()
{
    int n,m,ki;
    scanf("%d%d",&n,&m,&ki);
    getstring(A),getstring(B);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=26;j++)
            num[j][i]=num[j][i-1]+(A[i]==j);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            for(int k=1;k<=ki;k++)
                dp[i][j][k]=
    }
}
