#define MAXN 100005
#define STMAX (2*MAXN)

vector<PII> G[MAXN]; //<to,w>
struct ST
{
    int dp[STMAX][20];
    int mm[STMAX];
    // 预处理出log2(x),即 mm[x]=floor（log2(x))
    void init()
    {
        mm[0]=-1;
        for(int i=1 ; i<STMAX; i++)
            mm[i]=mm[i-1]+((i&(i-1))==0);
    }
    void build(int n,int b[])
    {
        init();
        for(int i=1; i<=n; i++)
            dp[i][0]=b[i];
        for(int j=1; j<=mm[n]; j++)
            for(int i=1; i+(1<<j)-1<=n; i++)
                dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
    }
    int query(int x,int y)
    {
        int k=mm[y-x+1];
        return min(dp[x][k],dp[y-(1<<k)+1][k]);
    }
}st;

struct _LCA
{
    int n ; // n是树上的节点个数
    int depth,b[MAXN*2],cnt; //dfs序
    int p[MAXN],f[MAXN];
    void dfs(int u,int pre)
    {
        int t=++depth;
        b[++cnt]=t;
        f[t]=u;
        p[u]=cnt;
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i].AA;
            if(v==pre) continue;
            dfs(v,u);
            b[++cnt]=t;
        }
    }
    void init(int nn)
    {
        n=nn;
        depth=0; cnt=0;
        dfs(1,-1);
        //注意rmq中元素为n*2-1个,数组长度要开够
        st.build(n*2-1,b);
    }
    int lca(int a,int b)
    {
        if(p[a]>p[b]) swap(a,b);
        return f[st.query(p[a],p[b])];
    }
}LCA;
