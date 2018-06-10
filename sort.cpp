#include <iostream>
#include <cstdio>
#include <algorithm>

#define N 102000

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

struct Treap
{
    struct node
    {
        int key,prio,tsize;
        bool turn,srt,inc,red;
        node* child[2];
    };
    typedef node* tree;
    const int P_INF=2147483647,N_INF=-2147483648;

    node base,tail;
    tree root=&base,null=&tail;
    void init(int x,int* arr)
    {
        null->prio=P_INF,null->tsize=0,null->child[0]=null->child[1]=null;
        root->child[0]=root->child[1]=null;
        root=build(arr,1,x,0);
    }
    int seed=7007;
    inline int random()
    {
        return (int)((seed*=1LL)%=P_INF);
    }
    inline void update(tree t)
    {
        if(t==null)return;
        t->tsize=t->child[0]->tsize+t->child[1]->tsize;
        t->inc=t->child[0]->inc&t->child[1]->inc;
        t->red=t->child[0]->red&t->child[1]->red;
    }
    inline void pushdown(tree t)
    {
        if(!t->turn)return;
        register tree tmp=t->child[0];
        t->child[0]=t->child[1];
        t->child[1]=tmp;
        t->child[0]->turn=!t->child[0]->turn,t->child[1]->turn=!t->child[1]->turn;
        t->child[0]->inc=!t->child[0]->inc,t->child[1]->inc=!t->child[1]->inc;
        t->child[0]->red=!t->child[0]->red,t->child[1]->red=!t->child[1]->red;
        t->turn=false;
    }
    void Split(tree t,int jud,tree &few,tree &more)//>=jud split to right subtree
    {
        if(t==null)
        {
            few=more=null;
            return;
        }
        pushdown(t);
        if(t->key<jud)
        {
            Split(t->child[1],jud,t->child[1],more);
            few=t;
        }
        else
        {
            Split(t->child[0],jud,few,t->child[0]);
            more=t;
        }
        update(few);
        update(more);
    }
    tree Merge(tree few,tree more)
    {
        if(few==null)return more;
        else if(more==null)return few;
        tree now;
        if(few->prio<more->prio)
        {
            now=few;
            few->child[1]=Merge(few->child[1],more);
        }
        else
        {
            now=more;
            more->child[0]=Merge(more->child[0],few);
        }
        return now;
    }
    void Split1(tree t,int jud,tree &few,tree &more)//>=jud split to right subtree
    {
        if(t==null)
        {
            few=more=null;
            return;
        }
        pushdown(t);
        if(t->child[0]->tsize+1<jud)
        {
            Split(t->child[1],jud-t->child[0]->tsize-1,t->child[1],more);
            few=t;
        }
        else
        {
            Split(t->child[0],jud,few,t->child[0]);
            more=t;
        }
        update(few);
        update(more);
    }
    int pos;
    void through(tree t,int* arr)
    {
        if(t==null)return;
        *(arr+pos)=t->key;
        pos++;
        through(t->child[0],arr);
        through(t->child[1],arr);
    }
    void check(tree &t,int type)
    {
        if(t==null)return;
        if(!t->srt)
        {
            int* a=new int[t->tsize];
            pos=1;
            through(t,a);
            sort(a+1,a+1+t->tsize);
            tree newtree=new node;
            *newtree=*null;
            for(int i=1;i<=t->tsize;i++)
            {
                tree tmp=new node;
                tmp->key=*(a+i);
                tmp->prio=random();
                tmp->srt=true;
                Merge(newtree,tmp);
            }
            t=newtree;
            delete a;
            return;
        }
        if(!t->inc&&!t->red)
        {
            check(t->child[0],type);
            check(t->child[1],type);
        }
        if(t->inc==type)t->turn=true;
    }
    void Turn(int type,int l,int r)
    {
        tree few,mid,more;
        Split1(root,l,few,mid);
        Split1(mid,r+1,mid,more);
        check(mid,type);
        Merge(Merge(few,mid),more);
    }
    int Query(int pos)
    {
        tree few,more,mid;
        Split1(root,pos,few,mid);
        Split1(root,pos+1,mid,more);
    }
}T;

int main()
{
    int n=read(),m=read(),ori[N];
    for(int i=1;i<=n;i++)
        ori[i]=read();
    T.init(n,ori);
    for(int i=1;i<=m;i++)
    {
        int op=read(),l=read(),r=read();
        T.Turn(op,l,r);
    }
    int q=read();
    printf("%d",T.Query(q));
    return 0;
}
