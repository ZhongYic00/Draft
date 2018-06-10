// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <cstdio>
struct Treap
{
    struct node
    {
        int key,prio,tsize;
        node* child[2];
    };
    node nil;
    typedef node* tree;
    tree null=&nil,root=null;
    const int P_INF=2147483647,N_INF=1<<31;
    int seed=10007;
    inline void init()
    {
        null->child[0]=null->child[1]=null;
        null->tsize=0;
        null->key=N_INF,null->prio=P_INF;
    }
    inline int random()
    {
        return (int)((seed*=48271LL)%=P_INF);
    }
    inline void _update(tree &t)
    {
        t->tsize=t->child[0]->tsize+t->child[1]->tsize+1;
    }
    tree _newnode(int key)
    {
        tree t=new node;
        t->key=key;
        t->prio=random();
        t->child[1]=t->child[0]=null;
        t->tsize=1;
        return t;
    }
    void Split(tree t,int jud,tree &few,tree &more)//>=jud split to right subtree
    {
        if(t==null)
        {
            few=more=null;
            return;
        }
        //pushdown(t);
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
        _update(t);
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
            more->child[0]=Merge(few,more->child[0]);
        }
        _update(now);
        return now;
    }
    void Insert(int x)
    {
        tree few,more,now=_newnode(x);
        Split(root,x,few,more);
        root=Merge(Merge(few,now),more);
    }
    void Erase(int x)
    {
        tree few,more,now;
        Split(root,x,few,now);
        Split(now,x+1,now,more);
        tree tmp=now;
        now=Merge(now->child[0],now->child[1]);
        delete tmp;
        root=Merge(Merge(few,now),more);
    }
    void Find(int &k)
    {
        tree t=root;
        while((k<=t->child[0]->tsize||k>t->child[0]->tsize+1)&&t!=null)
        {
            if(k<=t->child[0]->tsize)
                t=t->child[0];
            else
            {
                k-=t->child[0]->tsize+1;
                t=t->child[1];
            }
        }
        printf("%d\n",t->key);
    }
    void Rank(int &k)
    {
        tree few,more;
        Split(root,k,few,more);
        int rt=few->tsize+1;
        root=Merge(few,more);
        printf("%d\n",rt);
    }
    void Pre(int &x)
    {
        tree t=root;int rt=0;
        while(t!=null)
        {
            if(t->key<x)
            {
                rt=t->key;
                t=t->child[1];
            }
            else
                t=t->child[0];
        }
        printf("%d\n",rt);
    }
    void Suc(int &x)
    {
        tree t=root;int rt=0;
        while(t!=null)
        {
            if(t->key>x)
            {
                rt=t->key;
                t=t->child[0];
            }
            else
                t=t->child[1];
        }
        printf("%d\n",rt);
    }
};
Treap T;
int read()
{
    int f=1,v=0;char ch;
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        v=v*10+ch-'0';
        ch=getchar();
    }
    return f*v;
}
int option,num;
int main()
{
    int n;
    n=read();
    T.init();
    for(int i=1;i<=n;i++)
    {
        option=read();num=read();
        switch(option)
        {
            case 1:T.Insert(num);break;
            case 2:T.Erase(num);break;
            case 3:T.Rank(num);break;
            case 4:T.Find(num);break;
            case 5:T.Pre(num);break;
            case 6:T.Suc(num);break;
        }
    }
    return 0;
}
/*964673
964673
1
964673
3
1
1
964673
964673
*/
