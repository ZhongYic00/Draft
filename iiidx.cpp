#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 500030
using namespace std;
struct node
{
    int l,r,rk,tag;
}t[N<<2];
struct rnk
{
    int pos,k;
}num[N];

int cnt,n,d[N],ans[N];
inline void pushdown(int p)
{
    if(!t[p].tag)return;
    t[p<<1].tag=t[p<<1|1].tag=t[p].tag;
    t[p<<1].rk=t[p<<1|1].rk=t[p].rk;
    t[p].tag=0;
}
void build(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    if(l==r)
    {
        t[p].rk=1;
        return;
    }
    int m=l+r>>1;
    build(p<<1,l,m);
    build(p<<1|1,m+1,r);
}
void change(int p,int l,int r,int val)
{
    if(t[p].l==l&&t[p].r==r)
    {
        t[p].rk=t[p].tag=val;
        return;
    }
    pushdown(p);
    int m=t[p].l+t[p].r>>1;
    if(r<=m)change(p<<1,l,r,val);
    else if(l>m)change(p<<1|1,l,r,val);
    else change(p<<1,l,m,val),change(p<<1|1,m+1,r,val);
}
int query(int p,int pos)
{
    if(t[p].l==t[p].r)return t[p].rk;
    pushdown(p);
    int m=t[p].l+t[p].r>>1;
    if(pos<=m)return query(p<<1,pos);
    else return query(p<<1|1,pos);
}
void through(int p)
{
    if(t[p].l==t[p].r)
    {
        num[++cnt].k=t[p].rk,num[cnt].pos=t[p].l;
        return;
    }
    pushdown(p);
    through(p<<1),through(p<<1|1);
}
bool cmp(rnk a,rnk b)
{
    if(a.k==b.k)return a.pos>b.pos;
    else return a.k<b.k;
}
int main()
{
    freopen("iiidx.in","r",stdin);
    freopen("iiidx.out","w",stdout);
    double k;
    scanf("%d%lf",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&d[i]);
    sort(d+1,d+1+n);
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        int kk=query(1,i);
        int l=(int)(i*k+1)-1,r=(int)(i*k+k)-1;
        if(l<i*k)l++;
        if(r<i*k+k)r++;
        l=max(l,i+1);
        if(l>n)break;
        r=min(r,n);
        change(1,l,r,kk+1);
    }
    through(1);
    sort(num+1,num+1+n,cmp);
    for(int i=1;i<=n;i++)
        ans[num[i].pos]=d[i];
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    return 0;
}
