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
typedef vector<ll> vl;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int,int> mii;

const int maxn=1010;
const int INF = 1e5+10;

class Graph
{

public:
    ofstream fout;
    vi path;
    int V,E;
    int* dist;
    int* parent;
    vector< pii > adj[maxn];

    Graph(int v,int e)
    {
        this->V = v;
        this->E = e;
        dist = new int [V+1];
        parent = new int[V+1];
    }
    void removeEdge(int u,int v)
    {
        int i;
        for(int i=0;i<adj[u].size();i++)
        {
            if(adj[u][i].first==v)
            {
                adj[u][i].first=-1;
                adj[u][i].second=-99999;
            }
        }
        //adj[u].erase(i);
    }
    void addEdge(int u,int v,int wt)
    {
        adj[u].pb(mp(v,wt));
    }
    void dijkstra(int src, int destination)
    {
        fout.open("output.txt", std::ios_base::app);
        priority_queue<pii, vector<pii>, greater<pii> >pq;  ///sorted in non-increasing order w.r.t distance
        dist[src] = 0;
        pq.push(mp(0,src));
        while(!pq.empty())
        {
            pii top = pq.top();
            pq.pop();

            int curr=top.second;
            for(int i=0; i<adj[curr].size() and curr>=0; i++)
            {
                int next = adj[curr][i].first;
                int wt_next_curr = adj[curr][i].second;
                if(dist[curr]+wt_next_curr < dist[next] and next>=0)
                {
                    dist[next] = dist[curr]+wt_next_curr ;
                    parent[next] = curr;
                    pq.push(mp(dist[next], next));
                }
            }
        }
        if(dist[destination]==INF){
            cout<<"Not reachable from source\n";
            fout<<"Not reachable from source\n";
        }
        else{
            cout<<"Dijkstra Algorithm :"<<endl<<dist[destination]<<endl;
        fout<<"Dijkstra Algorithm :"<<endl<<dist[destination]<<endl;


        path.pb(destination);
        while(parent[destination]!=src)
        {
            path.pb(parent[destination]);
            destination = parent[destination];
        }
        path.pb(src);
        for(int i=path.size()-1; i>=0; i--)
        {
            if(i!=0)
            {
                cout<<path[i]<<"->";
                fout<<path[i]<<"->";
            }
            else
            {
                cout<<path[i]<<endl;
                fout<<path[i]<<endl;
            }

        }


        }

        for(int i=0; i<sizeof(dist); i++)
        {
            dist[i] = INF;
        }
    }
    void sec_sp()
    {


        ///write more
    }
    bool detect_neg_cycle()
    {
        int n=V;
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<adj[j].size(); k++)
            {
                int next = adj[j][k].first;
                int next_wt = adj[j][k].second;
                if(dist[j] + next_wt < dist[next])
                {
                    return true;
                }
            }
        }
        return false;
    }
    void BFord(int src,int destination)
    {

        fout.open("output.txt");
        int n = V;
        for(int i=0; i<n; i++)
        {
            dist[i] = INF;
        }
        dist[src] = 0;
        for(int i=0; i<n-1; i++)
        {
            for(int j=0; j<n; j++)
            {
                for(int k=0; k<adj[j].size(); k++)
                {
                    int next = adj[j][k].first;
                    int next_wt = adj[j][k].second;
                    if(dist[j] + next_wt < dist[next])
                    {
                        dist[next] = dist[j] + next_wt ;//cout<<dist[next]<<endl;
                        parent[next] = j;
                    }
                }
            }
        }
        if(dist[destination]==INF){
            cout<<"Not reachable from source\n";
            fout<<"Not reachable from source\n";
        }
        else{
                cout<<"Bellman Ford Algorithm :\n";
        fout<<"Bellman Ford Algorithm :\n";
        if(detect_neg_cycle())
        {
            cout<<"Negative cycle found"<<endl;
            fout<<"Negative cycle found"<<endl;
        }
        else
        {
            cout<<dist[destination]<<endl;
            fout<<dist[destination]<<endl;
            vi path;
            path.pb(destination);
            while(parent[destination]!=src)
            {
                path.pb(parent[destination]);
                destination = parent[destination];
            }
            path.pb(src);
            for(int i=path.size()-1; i>=0; i--)
            {
                if(i!=0)
                {
                    cout<<path[i]<<"->";
                    fout<<path[i]<<"->";
                }
                else
                {
                    cout<<path[i]<<endl;
                    fout<<path[i]<<endl;
                }

            }
        }
        }


    }
    void print()
    {
        for(int i=0;i<V;i++)
        {
            cout<<i<<" : ";
            for(int j=0;j<adj[i].size();j++)
            {
                cout<<adj[i][j].first<<" , ";
            }
            cout<<endl;
        }
    }
};
main()
{
    ifstream fin;
    fin.open("input.txt");
    int n,m,u,v,w,s,d;
    fin>>n>>m;
    Graph g1(n,m),g2(n,m);
    for(int i=0; i<n; i++)
    {
        g1.dist[i]=INF;
        g2.dist[i] = INF;
    }
    for(int i=0; i<m; i++)
    {
        fin>>u>>v>>w;
        g1.addEdge(u,v,abs(w));
        g2.addEdge(u,v,w);
    }
    fin>>s>>d;

    g2.BFord(s,d);
    g1.dijkstra(s,d);

    vi sp;
    //g1.removeEdge(3,2);
    //g1.print();
     for(int i=0; i<n-1; i++)
        {
            int x = g1.path[i];
            int y = g1.path[i+1];
            int wt = g1.adj[x][y].second;
            g1.removeEdge(x,y);cout<<x<<" "<<y;
            //g1.print();
            g1.dijkstra(s,d);
            sp.pb(g1.dist[d]);
            g1.addEdge(x,y,wt);
        }
        for(int i=0;i<sp.size();i++)
        {
            cout<<sp[i]<<"-";
        }
        sort(sp.begin() , sp.end());
        cout<<sp[sp.size()-1];

}
