#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <string.h>
#define N 1600000
using namespace std;
int e[N],p[N],w[N],nt[N],tp[N],n,s,num,points;
bool vis[N];
struct node{int x,dis;}pnt[N];
void add(int &fi,int &ti,int &wi)
{
    e[++num]=ti,nt[num]=p[fi],w[num]=wi,p[fi]=num,tp[ti]++;
}
void dfs(int x,int cst)
{
    if(x>num)return;
    vis[x]=true,pnt[++points].x=x,pnt[points].dis=cst;
    int next=p[x];
    while(next)
    {
        if(!vis[e[next]])dfs(e[next],cst+w[next]);
        next=nt[next];
    }
}
bool cmp(node x,node y){return x.dis>y.dis;}
int main()
{
    int fi,ti,wi,root;
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&fi,&ti,&wi);
        add(fi,ti,wi);
    }
    for(register int i=1;i<=num;i++)
        if(tp[i]==1)root=i;
    dfs(root,0);
    sort(pnt+1,pnt+1+points,cmp);
    points=1;
    while(pnt[points].dis==pnt[points+1].dis)
    return 0;
}
