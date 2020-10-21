														/**Bismillahir Rahmanir Rahimm**/
#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define ffr(i,a,b) for(int i=a;i<b;i++)
#define mm(a,b) memset(a,b,sizeof(a))

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int,int> mii;

const int maxn=1010;
const int INF = 1e5+10;

class Graph
{

public:
    int V,E;
    vi setA ,setB;
    vector< pii > adj[maxn];
    int** capacity = new int*[maxn];
    vector<int>clr;
    Graph(int v,int e)
    {
        this->V = v;
        this->E = e;
        ffr(i,0,v)
        {
           capacity[i] = new int[v];
           memset(capacity[i] , 0 , v*sizeof(int));
        }
        clr.assign(V,-1);

    }
    bool isBipartite(int src)
    {
        int u,v,sz;
        clr[src] = 1;

        queue<int> q;
        q.push(src);

        while(!q.empty()){
            u = q.front();
            q.pop();

            ///self loop
            sz = adj[u].size();
            ffr(i,0,sz)
            {
                if(adj[u][i].first==u)return false;
                v = adj[u][i].first;
                if(clr[v]==-1){
                    clr[v] = 1-clr[u];
                    q.push(v);
                }
                if(clr[u]==clr[v]){
                    return false;
                }
            }
        }
        ffr(i,0,V)
        {
            ///extra condition just to make sure both sets contain unique elements
            if( (find(setA.begin(), setA.end(), i) == setA.end()) and clr[i]==1)setA.pb(i);
            else if( (find(setB.begin(), setB.end(), i) == setB.end()) and clr[i]==0)setB.pb(i);
        }
        return true;
    }

    void addEdge(int u,int v,int wt)
    {
        adj[u].pb(mp(v,wt));
        adj[v].pb(mp(u,wt));
        capacity[u][v] = wt;
        capacity[v][u] = wt;
    }

    void addEdge_dir(int u,int v,int wt)///for the 2nd graph on which maxflow is run
    {
        adj[u].pb(mp(v,wt));
        adj[v].pb(mp(u,wt));
        capacity[u][v] = wt;
        capacity[v][u] = 0;
    }

    void printflows()
    {
        int v;
        int sb=setB.size(),sa = setA.size();int k=0;
        ffr(i , 0 , sb)
        {
            ffr(j , 0 , sa)
            {
                if(capacity[setB[i]][setA[j]]==1){cout<<setB[i]<<" "<<setA[j]<<endl;k++;}
            }
        }
        //cout<<k;///k is a count
    }

    bool isEdge(int u , int v)
    {
        int sz = adj[u].size();
        ffr(i , 0 , sz)
        {
            if(adj[u][i].first == v)return true;
        }
        return false;
    }

    int bfs(int s, int t, vector<int>& parent) {
        //mm(parent , -1);
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        int next,cap;
        queue<pair<int, int>> q;
        q.push({s, INF});
        while (!q.empty()){
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            int sz = adj[cur].size();
            ffr(i , 0 , sz)
            {
                next = adj[cur][i].first;

                if (parent[next] == -1 && capacity[cur][next]) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

    int getCapacity(int u , int v)
    {
        ffr(i , 0 , adj[u].size())
        {
            if(v==adj[u][i].first)return adj[u][i].second;
        }
    }

    int maxflow(int s, int t) {
        int flow = 0;
        vector<int> parent(V+2);
        int new_flow;

        while (new_flow = bfs(s, t, parent)) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }

        return flow;
    }
    Graph createNewGraph(int s , int t)
    {
        int sa = setA.size() , sb = setB.size();
        Graph g(V+2 , E+V);
        ///setting previous sets as the new graph's sets

        g.setA = setA;
        g.setB=setB;

        ffr(i,0,sa)g.addEdge_dir( s , setA[i], 1);
        ffr(i, 0 , sb)g.addEdge_dir(setB[i] ,t , 1);
        ffr(i,0,sa)
        {
            ffr(j , 0  ,sb)
            {
                if(isEdge(setA[i] , setB[j]))g.addEdge_dir(setA[i] , setB[j] , 1);
            }

        }

        return g;
    }
    ~Graph()
    {
        ffr(i,0,V)
        {
            delete[] capacity[i];
        }
        delete[] capacity;
    }
};
main()
{
    ifstream fin;
    fin.open("input2.txt");
    int n,m,u,v,w,s,t,src_bp;

    FILE *fp;
    ///uncomment to output in a file
    //fp = freopen("output_matching.txt", "w+", stdout);

    fin>>n>>m;
    Graph g(n,m);
    ffr(i,0,m){
        fin>>u>>v;
        if(i==0)src_bp = u;
        g.addEdge(u,v,1);
    }
    s = n, t = n+1;

    bool ok=true;
    ///following loop handles disconnected graph
    ffr(i,0,n)
    {
        if(g.clr[i]==-1 ){
            ok = ok&&g.isBipartite(i);
        }
    }
    if(!ok){
        cout<<"The graph is not bipartite"<<endl;
    }
    else {
        Graph g2 = g.createNewGraph(s,t);
        cout<<g2.maxflow(s,t)<<endl;
        g2.printflows();
    }
}
