#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

#define N 50020
#define Side(x) for(int i=p[x];i;i=nt[i])

using namespace std;
int n,m,Mlog,army[N],f[N][18],dis[N][18];
long long ans,L,R=50000000;
int tot,e[N<<1],nt[N<<1],w[N<<1],p[N];
void add(int x,int y,int v)
{
    e[++tot]=y,nt[tot]=p[x],w[tot]=v,p[x]=tot;
}
void dfs(int x,int fa)
{
    for(int i=1;f[x][i-1];i++)
    {
        f[x][i]=f[f[x][i-1]][i-1];
        dis[x][i]=dis[x][i-1]+dis[f[x][i-1]][i-1];
    }// f[node][n] 2^n
    Side(x)
    {
        if(e[i]==fa)continue;
        f[e[i]][0]=x,dis[e[i]][0]=w[i];
        dfs(e[i],x);
    }
}
struct node{int id;long long d;}a[N],b[N],restm[N];
bool cmp(node a,node b){return a.d>b.d;}
int cnt,cnt1;
bool ctl[N],used[N];
bool chksub(int x,int fa)
{
    if(ctl[x])return true;
    bool sub=false,state=true;
    Side(x)
    {
        if(e[i]==fa)continue;
        sub=true;
        if(!chksub(e[i],x))
        {
            if(x==1)b[++cnt1]={e[i],w[i]},state=false;
            else return false;
        }
    }
    return state&sub;
}
bool check(long long TLE)
{
    memset(used,0,sizeof(used));
    memset(ctl,0,sizeof(ctl));
    memset(a,0,sizeof(a)),cnt=0;
    memset(b,0,sizeof(b)),cnt1=0;
    memset(restm,0,sizeof(restm));
    for(int i=1;i<=m;i++)
    {
        int now=army[i],used=0;
        for(int k=Mlog+1;k>=0;k--)
            if(dis[now][k]+used<=TLE&&f[now][k]>1)used+=dis[now][k],now=f[now][k];
        if(f[now][0]==1&&dis[now][0]+used<=TLE)
        {
            a[++cnt]={i,TLE-used-dis[now][0]};
            if(restm[now].id==0||a[cnt].d<restm[now].d)restm[now]=a[cnt];
        }
        else ctl[now]=true;
    }
    if(chksub(1,0))return true;
    sort(a+1,a+1+cnt,cmp),sort(b+1,b+1+cnt1,cmp);
    int mat=1;
    used[0]=true;
    for(int i=1;i<=cnt1;i++)
    {
        if(!used[restm[b[i].id].id]){used[restm[b[i].id].id]=true;continue;}
        while(mat<=cnt&&(used[a[mat].id]||a[mat].d<b[i].d))++mat;
        if(a[mat].d<b[i].d)
            return false;
        used[a[mat].id]=true;
    }
    return true;
}
int main()
{
    //freopen("P1084#1.in","r",stdin);
    scanf("%d",&n);
    Mlog=log2(n);
    int ui,vi,wi;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&ui,&vi,&wi);
        add(ui,vi,wi),add(vi,ui,wi);
    }
    dfs(1,0);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&army[i]);
    while(L<=R)
    {
        long long M=L+R>>1;
        bool state=check(M);
        if(state)ans=M,R=M-1;
        else L=M+1;
    }
    printf("%lld",ans);
    return 0;
}
