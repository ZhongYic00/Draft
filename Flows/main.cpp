// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>

#define Q 80800
#define N 500000
#define INF 2147483647

using namespace std;

int n,m,s,t;
bool point[1508];

int read()
{
    int f=1,v=0;
    char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-2;
    while(isdigit(ch))v=v*10+ch-'0',ch=getchar();
    return f*v;
}

struct NetFlow
{
    int e[N],p[N],nt[N],w[N],tot=-1;
    bool edge[3008][3008];

    void _add(int fr,int to,int v)
    {
        e[++tot]=to,nt[tot]=p[fr],w[tot]=v,p[fr]=tot;
    }
    inline void add(int fr,int to,int v)
    {
        if(edge[fr][to])return;
        _add(fr,to,v);
        _add(to,fr,0);
        edge[fr][to]=true;
        //printf("NewEdge:%d->%d\n",fr,to);
    }

    int depth[N],cur[N];

    bool bfs()
    {
        int q[Q],l=0,r=0;
        memset(depth,0,sizeof(depth));
        depth[s]=1;
        q[++r]=s;
        while(l<r)
        {
            for(int side=p[q[++l]];side!=-1;side=nt[side])
            {
                if(w[side]>0&&!depth[e[side]])
                    depth[e[side]]=depth[q[l]]+1,q[++r]=e[side];
            }
        }
        return depth[t]!=0;
    }
    int dfs(int now,int dist)
    {
        if(now==t)return dist;
        for(int &side=cur[now];side!=-1;side=nt[side])
        {
            //printf("%d->%d\n",now,e[side]);
            if(depth[e[side]]==depth[now]+1&&w[side])
            {
                int more=dfs(e[side],min(dist,w[side]));
                if(more)
                {
                    w[side]-=more;
                    w[1^side]+=more;
                    return more;
                }
            }
        }
        return 0;
    }
    int run()
    {
        int ans=0,dnow;
        while(bfs())
        {
            for(register int i=1;i<=3006;i++)cur[i]=p[i];
            while(dnow=dfs(s,INF))
                ans+=dnow;
        }
        return ans;
    }
}F;
int main()
{
    scanf("%d",&n);
    m=1500,s=3002,t=3003;
    memset(F.p,-1,sizeof(F.p));
    int x,y,z;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        y+=500,z+=1000;
        F.add(s,x,INF);
        if(!point[x])
            F.add(x,x+m,1),point[x]=true;
        F.add(x+m,y,INF);
        if(!point[y])
            F.add(y,y+m,1),point[y]=true;
        F.add(y+m,z,INF);
        if(!point[z])
            F.add(z,z+m,1),point[z]=true;
        F.add(z+m,t,INF);
    }
    printf("%d",F.run());
    return 0;
}
