//单源最短路：

//Dijkstra算法：

//邻接矩阵
const int MAXN=1005;
const int  inf=0x3f3f3f3f;
int cost[MAXN][MAXN];   //cost[u][v]表示边e=(u,v)的权值
int d[MAXN];            //顶点s出发的最短距离
bool used[MAXN];        //已使用过的图
int n;                  //顶点数

void dijkstra (int s)
{
    fill(d,d+n,inf);
    fill(used,used+n,false);
    d[s] = 0;
    while(true)
    {
        int v = -1;
        for(int u = 0 ; u < n  ; u++)
            if(!used[u] && (v==-1 || d[u]<d[v]))
                v = u;
        if(v == -1)
            break;
        used[v] = true;
        for(int u = 0 ; u < n ; u++)
            d[u] = min(d[u],d[v]+cost[v][u]);
    }
}



//邻接表 nlgn
const int MAXN=100005;
const int  inf=0x3f3f3f3f;
int n;                  //顶点数
struct edge{ int to,cost; };
vector<edge> G[MAXN];
typedef pair<int,int> P;  //first是最短距离，second是顶点的编号
int d[MAXN];   //顶点s出发的最短距离

void dijkstra(int s)
{
    priority_queue< P,vector<P>,greater<P> > que;
    fill(d,d+n,inf);
    d[s] = 0;
    que.push(P(0,s));
    while(!que.empty()){
        P p = que.top();que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i = 0 ; i <G[v].size() ; i++){
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}




//SPFA：(单源最短路，可处理负边)

//只要最短路径存在，上述SPFA算法必定能求出最小值。时间复杂度是O(ke)，
//其中k为所有顶点进队的平均次数，可以证明k一般小于等于2。

class Spfa
{
    struct Edge
    {
        int to;
        int w;
        int next;
    };
public:
    enum { TAIL = -1, UNREACHABLE = 2147483647 };
    Spfa(int n) : n(n), sp(-1), head(vector<int>(n + 1, TAIL)) {}
    int dist(int a, int b)
    {
        if (sp != a) bellmanFord(a);
        return dst[b];
    }
    void addEdge(int a, int b, int w)
    {
        Edge edge {b, w, head[a]};
        head[a] = e.size();
        e.push_back(edge);
    }
private:
    bool bellmanFord(int st)
    {
        used.assign(n + 1, false);
        oq.assign(n + 1, 0);
        dst.assign(n + 1, UNREACHABLE);
        sp = st;
        used[st] = true;
        dst[st] = 0;
        queue<int> q;
        q.push(st);
        while (!q.empty())
        {
            int top = q.front();
            q.pop();
            oq[top]++;
            used[top] = false;
            if (oq[top] > n) return false; //有环
            for (int k = head[top]; k != TAIL; k = e[k].next)
                if (dst[e[k].to] > dst[top] + e[k].w)
                {
                    dst[e[k].to] = dst[top] + e[k].w;
                    if (!used[e[k].to])
                    {
                        used[e[k].to] = true;
                        q.push(e[k].to);
                    }
                }

        }
        return true;
    }
protected:
    const int n;
    int sp; // last queried source
    vector<bool> used;
    vector<int> oq;
    vector<int> head;
    vector<int> dst;
    vector<Edge> e;
};



