#include <iostream>
#include <cstdio>
#define N 300020
using namespace std;

int read()
{
    int f=1,v=0;
    char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))v=v*10+ch-'0',ch=getchar();
    return f*v;
}
char getop()
{
    char ch=getchar();
    while(ch<'A'||ch>'Z')
        ch=getchar();
    return ch;
}

int tot,e[N],nt[N],p[N];
void add(int x,int y)
{
    e[++tot]=y,nt[tot]=p[x],p[x]=tot;
}

int depth[N],fth[N],tsize[N],son[N],id[N],nod[N],cnt,top[N];
void dfs1(int now,int fa,int deep)
{
    if(!now)return;
    depth[now]=deep,fth[now]=fa;
    tsize[now]=1;
    for(int i=p[now];i;i=nt[i])
    {
        dfs1(e[i],now,deep+1);
        tsize[now]+=tsize[e[i]];
        son[now]=tsize[e[i]]>tsize[son[now]]?e[i]:son[now];
    }
    return;
}
void dfs2(int now,int anc)
{
    if(!now)return;
    top[now]=anc;
    id[now]=++cnt;
    nod[cnt]=now;
    dfs2(son[now],anc);
    for(int i=p[now];i;i=nt[i])
    {
        if(e[i]==son[now])continue;
        dfs2(e[i],e[i]);
    }
}
struct Seg
{
    struct node
    {
        int l,r,key;
    }t[N<<2];
    inline void update(int p)
    {
        t[p].key=t[p<<1].key|t[p<<1|1].key;
    }
    void build(int p,int l,int r)
    {
        t[p].l=l,t[p].r=r;
        if(l==r)
        {
            t[p].key=0;
            return;
        }
        int m=l+r>>1;
        build(p<<1,l,m),build(p<<1|1,m+1,r);
        update(p);
    }
    void change(int p,int l,int val)
    {
        if(t[p].l==t[p].r)
        {
            t[p].key=val;
            return;
        }
        int m=t[p].l+t[p].r>>1;
        if(l<=m)change(p<<1,l,val);
        else change(p<<1|1,l,val);
        update(p);
    }
    int query(int p,int l,int r)
    {
        if(!t[p].key)return 0;
        if(t[p].l==t[p].r)
            return t[p].key!=0?t[p].l:0;
        int m=t[p].l+t[p].r>>1,ls=0,rs=0;
        if(r<=m)ls=query(p<<1,l,r);
        else if(l>m)rs=query(p<<1|1,l,r);
        else ls=query(p<<1,l,m),rs=query(p<<1|1,m+1,r);
        return max(ls,rs);
    }
}T;
int solve(int x)
{
    int anc,rt=0;
    while(1)
    {
        anc=top[x];
        rt=T.query(1,id[anc],id[x]);
        if(rt)return rt;
        x=fth[anc];
    }
}

int main()
{
    //freopen("tree.in","r",stdin);
    //freopen("tree.out","w",stdout);
    int n,q;
    scanf("%d%d",&n,&q);
    int x,y;
    for(int i=1;i<n;i++)
        x=read(),y=read(),add(x,y);
    dfs1(1,1,1);
    dfs2(1,1);
    T.build(1,1,n);
    T.change(1,id[1],1);
    for(int i=1;i<=q;i++)
    {
        switch(getop())
        {
            case 'C':T.change(1,id[read()],1);break;
            case 'Q':printf("%d\n",nod[solve(read())]);break;
        }
    }
    return 0;
}
