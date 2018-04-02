静态区间第K小：


//将 a[i] 投影到数轴上 a[i]的位置
int a[MAX];
vector<int> c;

int getid(int x) 
{
    return lower_bound(c.begin(),c.end(),x)-c.begin()+1;
}

struct node
{
    int l,r,sum;
}T[MAX*40];

int root[MAX];
int cnt=0;  //cnt要记得初始化

//建立最原始的线段树。如果最开始为空树，则不需要调用
//调用：root[0]=build(1,n);
int bulid(int l,int r){
    int root=cnt++;
    T[root].sum=0;
    if(l!=r){
        int mid=(l+r)>>1;
        T[root].l=bulid(l,mid);
        T[root].r=bulid(mid+1,r);
    }
    return root;
}
void update(int l,int r,int &x,int y,int pos) // y是上一个版本的root编号，x是这个版本的root编号
{
    T[++cnt]=T[y];
    T[cnt].sum++;
    x=cnt;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(pos<=mid)
        update(l,mid,T[x].l,T[y].l,pos);
    else
        update(mid+1,r,T[x].r,T[y].r,pos);
}

int query(int l,int r,int x,int y,int k)
{
    if(l==r) return l;
    int sum=T[T[y].l].sum-T[T[x].l].sum;
    int mid=(l+r)>>1;
    if(sum>=k)
        return query(l,mid,T[x].l,T[y].l,k);
    else
        return query(mid+1,r,T[x].r,T[y].r,k-sum);
}

int main()
{
    int n,m ;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        c.PB(a[i]);
    }
    sort(c.begin(),c.end());
    c.erase(unique(c.begin(),c.end()),c.end());
    for(int i=1;i<=n;i++)
        update(1,n,root[i],root[i-1],getid(a[i]));
    for(int i=1;i<=m;i++)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n",c[query(1,n,root[x-1],root[y],k)-1]);
    }
    return 0;
}


区间内不同数的个数：
/*
 * 给出一个序列，查询区间内有多少个不相同的数
 */
 
//将 a[i]投影到数轴上 i 位置
const int MAXN = 30010;
const int M = MAXN * 100;
int n,q,tot;
int a[MAXN];
int T[M],lson[M],rson[M],c[M];
int build(int l,int r){
    int root = tot++;
    c[root] = 0;
    if(l != r){
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}
int update(int root,int pos,int val){
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = n;
    while(l < r){
        int mid = (l+r)>>1;
        if(pos <= mid){
            lson[newroot] = tot++;  rson[newroot] = rson[root];
            newroot = lson[newroot]; root = lson[root];
            r = mid;
        }
        else{
            rson[newroot] = tot++; lson[newroot] = lson[root];
            newroot = rson[newroot]; root = rson[root];
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int query(int root,int pos){
    int ret = 0;
    int l = 1, r = n;
    while(pos < r){
        int mid = (l+r)>>1;
        if(pos <= mid){
            r = mid;
            root = lson[root];
        }
        else{
            ret += c[lson[root]];
            root = rson[root];
            l = mid+1;
        }
    }
    return ret + c[root];
}
int main()
{
    while(scanf("%d",&n) == 1){
        tot = 0;
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        T[n+1] = build(1,n);
        map<int,int>mp;
		//在每个元素最后一次出现的位置加1，上一次出现的位置减1
		//倒着插入确保当前加1的位置是所有a[i]出现的位置中最小的。
        for(int i = n;i>= 1;i--){
            if(mp.find(a[i]) == mp.end()){
                T[i] = update(T[i+1],i,1);
            }
            else{
                int tmp = update(T[i+1],mp[a[i]],-1);
                T[i] = update(tmp,i,1);
            }
            mp[a[i]] = i;
        }
        scanf("%d",&q);
        while(q--){
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",query(T[l],r));
        }
    }
    return 0;
}



树上第K小：

//题意：从树上一点u到根节点的路径中，小于等于w的数有多少个
//更改query函数，也可求从树上一点u到根节点的路径中，第w小的数是多少

//HDU5877 本题用到的变量
int n;
ll K;
vector<int> c,G[MAX];
int a[MAX],fa[MAX];
bool used[MAX];

//通用函数及变量
int getid(ll x)
{
    return lower_bound(c.begin(),c.end(),x)-c.begin()+1;
}

struct node
{
    int l,r,sum;
}T[MAX*40];

int root[MAX];
int cnt=0;

void update(int l,int r,int &x,int y,int pos) // y是上一个版本的root编号，x是这个版本的root编号
{
    T[++cnt]=T[y];
    T[cnt].sum++;
    x=cnt;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(pos<=mid)
        update(l,mid,T[cnt].l,T[y].l,pos);
    else
        update(mid+1,r,T[cnt].r,T[y].r,pos);
}

int query(int L,int R,int l,int r,int x)
{
    if(L>R) return 0;
    if(L<=l&&r<=R)  return T[x].sum;

    int ans=0;
    int m=(l+r)>>1;
    if(L<=m)
        ans+=query(L,R,l,m,T[x].l);
    if(R>m)
        ans+=query(L,R,m+1,r,T[x].r);
    return ans;
}



void dfs(int u,int p)
{
    fa[u]=p;
    update(1,n,root[u],root[p],getid(a[u]));
    for(int i=0;i<G[u].size();i++)
        dfs(G[u][i],u);
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>K;
        c.clear();
        cnt=0;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            c.PB(a[i]);
        }
        memset(used,0,sizeof(used));
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].PB(v);
            used[v]=1;
        }
        int rt;
        for(int i=1;i<=n;i++)  if(!used[i]) rt=i;
        sort(c.begin(),c.end());
        c.erase(unique(c.begin(),c.end()),c.end());
        dfs(rt,0);
        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]==0)
                ans+=query(1,n,1,n,root[fa[i]]);
            else
            {
                ll t=K/a[i];
                int b=getid(t);
                if(c[b-1]!=t) b--;
                ans+=query(1,b,1,n,root[fa[i]]);
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

