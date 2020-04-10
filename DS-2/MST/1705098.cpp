/**Bismillahir Rahmanir Rahimm**/
#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int,int> mii;

const db epsilon=1e-9;
const int maxsz=10050;
const db INF = 1e6+10;

class edge
{
public:
    int u,v,w;
    edge(int x,int y,int z)
    {
        u=x;
        v=y;
        w=z;
    }
};
bool comp(const edge e1, const edge e2)
{
    return e1.w < e2.w;
}
struct subset
{
    int parent;
    int rank;
};
class disjointSet
{
public:
    subset *ara;
    disjointSet()
    {
        ara = new subset[maxsz];
        for(int i=0; i<maxsz; i++)
        {
            ara[i].parent = -1;
        }
    }
    void MakeSet(int x)
    {
        ara[x].parent = x;
        ara[x].rank = 0;
    }
    int Findset(int x)
    {
        if(ara[x].parent != x)
        {
            ara[x].parent = Findset(ara[x].parent);
        }
        return ara[x].parent;
    }
    void Union(int x, int y)
    {
        int xroot = Findset(x);
        int yroot = Findset(y);

        if(xroot==yroot)
            return;

        if(ara[xroot].rank < ara[yroot].rank)
        {
            ara[xroot].parent = yroot;
        }
        else
        {
            ara[yroot].parent = xroot;
        }
        if(ara[xroot].rank == ara[yroot].rank)
        {
            ara[xroot].rank++;
        }
    }
};
class Graph
{
public:
    ofstream fout;
    int V,E;
    vii adj[maxsz];
    int* key;
    int* parent;
    vector<edge>EdgeVector;

    Graph(int v,int e)
    {
        this->V = v;
        this->E = e;
        key = new int [V+1];
        parent = new int[V+1];
        fout.open("output.txt");
    }
    void addEdge(int u,int v,int wt)
    {
        adj[u].pb(mp(v,wt));
        adj[v].pb(mp(u,wt));
        edge e(u,v,wt);
        EdgeVector.pb(e);
    }

    void kruskal()
    {
        disjointSet ds;
        vector<edge> mst_path;

        int u,v,mstWeight=0;
        for(int i=0; i<V; i++)
        {
            ds.MakeSet(i);
        }
        sort(EdgeVector.begin(), EdgeVector.end(), comp);

        for(int i=0; i<EdgeVector.size(); i++)
        {
            int u = EdgeVector[i].u;
            int v = EdgeVector[i].v;
            int uroot = ds.Findset(u);
            int vroot = ds.Findset(v);
            if(uroot!=vroot)
            {
                mst_path.pb(edge(u,v,EdgeVector[i].w));
                ds.Union(u,v);
            }
        }
        for(int i=0; i<mst_path.size(); i++)
        {
            mstWeight+=mst_path[i].w;
        }
        fout<<mstWeight<<endl<<"kruskal's algorithm\n";
        for(int i=0; i<mst_path.size(); i++)
        {
            fout<<mst_path[i].u<<" "<<mst_path[i].v<<endl;
        }
    }
    void prims(int src)
    {
        int u,v,wt;
        for(int i=0; i<V; i++)
        {
            key[i] = INF;
            parent[i] = -1;
        }
        key[src] = 0;
        priority_queue<pii, vector<pii>, greater<pii> >pq;
        bool contains[V];
        memset(contains, false, sizeof(contains));
        pq.push(mp(0,src));
        while(!pq.empty())
        {
            pii top = pq.top();
            pq.pop();

            u = top.second;
            contains[u] = true;

            for(int i=0; i<adj[u].size(); i++)
            {
                v = adj[u][i].first;
                wt = adj[u][i].second;

                if(wt<key[v] and !contains[v])
                {
                    parent[v] = u;
                    key[v] = wt;
                    pq.push(mp(wt, v));
                }
            }
        }
        fout<<"Prims Algorithm\nRoot node = "<<src<<endl;
        for(int i=0; i<V; i++)
        {
            if(parent[i]!=-1)
                fout<<i<<" "<<parent[i]<<endl;

        }
    }
};
main()
{
    ifstream fin;
    fin.open("input.txt");
    int n,m,u,v,wt;
    fin>>n>>m;
    Graph g(n,m);
    for(int i=0; i<m; i++)
    {
        fin>>u>>v>>wt;
        g.addEdge(u,v,wt);
    }
    g.kruskal();
    g.prims(0);
}
