#include <cstdio>
#include <cmath>
#define N 2003
using namespace std;
int n;
/*inline void add(int x,int y)
{
    e[++tot]=y,nt[tot]=p[x],p[x]=tot;
}*/
bool flag[N][N];
struct node{int x,w;}in[N];
bool cmp(node a,node b){return a.x<b.x;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&in[i].x,&in[i].w);
    //sort(in+1,in+1+n,cmp);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            if(abs(in[j].x-in[i].x)>in[j].w+in[i].w)flag[i][j]=true,p[i][++p[i][0]]=j,p[j][++p[j][0]]=i;
    for(int i=1;i<=n;i++)
    {
        int now=0;
        for(int j=1;j<=p[i][0];j++)
            for(int k=j+1;k<=p[i][0];k++)
            if(flag[p[i][j]][p[i][k]])now++;
        ans=max(ans,now);
    }
    cout<<ans;
}
