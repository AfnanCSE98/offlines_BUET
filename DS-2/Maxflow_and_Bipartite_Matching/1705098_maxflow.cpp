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
    vector< pii > adj[maxn];
    int** capacity = new int*[maxn];
    int** flowmat = new int*[maxn];
    int** initialcapacity = new int*[maxn];

    Graph(int v,int e)
    {
        this->V = v;
        this->E = e;
        ffr(i,0,v)
        {
           capacity[i] = new int[v];
           memset(capacity[i] , 0 , v*sizeof(int));
           flowmat[i] = new int[v];
           memset(flowmat[i] , 0 , v*sizeof(int));
           initialcapacity[i] = new int[v];
           memset(initialcapacity[i] , 0 , v*sizeof(int));
        }

    }

    void addEdge(int u,int v,int wt)
    {
        adj[u].pb(mp(v,wt));
        capacity[u][v] = wt;
        initialcapacity[u][v] = wt;
    }

    void printflows()
    {
        int v;
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<adj[i].size();j++)
            {
                v = adj[i][j].first;
                 cout<<i<<" "<<v<<" "<< flowmat[i][v]<<"/"<<adj[i][j].second<<endl;
            }
        }
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

     bool isEdge(int u , int v)
    {
        int sz = adj[u].size();
        ffr(i , 0 , sz)
        {
            if(adj[u][i].first == v)return true;
        }
        return false;
    }

    int maxflow(int s, int t) {
        int flow = 0;
        vector<int> parent(V);
        int new_flow;

        while (new_flow = bfs(s, t, parent)) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;

                flowmat[prev][cur] += new_flow;

                if(flowmat[prev][cur]>initialcapacity[prev][cur]){
                    flowmat[cur][prev] -= (flowmat[prev][cur] - initialcapacity[prev][cur]);
                    flowmat[prev][cur] = initialcapacity[prev][cur];
                }

                cur = prev;
            }
        }

        return flow;
    }
    ~Graph()
    {
        ffr(i,0,V)
        {
            delete[] capacity[i];
            delete[] initialcapacity[i];
            delete[] flowmat[i];
        }
        delete[] capacity;
        delete[] initialcapacity;
        delete[] flowmat;
    }
};
main()
{
    ifstream fin;
    fin.open("input1.txt");

    FILE *fp;
     ///uncomment to output in a file
   // fp = freopen("output_flow.txt", "w+", stdout);
    int n,m,u,v,w,s,t;
    fin>>n>>m;
    Graph g(n,m);
    ffr(i,0,m){
        fin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    fin>>s>>t;
    cout<<g.maxflow(s,t)<<endl;
    g.printflows();

}
