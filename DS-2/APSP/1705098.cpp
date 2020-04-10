/**Bismillahir Rahmanir Rahimm**/
#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<db,int> pdi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int,int> mii;

const db epsilon=1e-9;
const int maxn=10050;
const db INF = 1e6+10;

class Edge
{
    int u,v;
    db w;
public:
    Edge(int x,int y,db z)
    {
        u=x;
        v=y;
        w=z;
    }
    void setu(int x)
    {
        u=x;
    }
    void setv(int x)
    {
        v=x;
    }
    void setw(db x)
    {
        w=x;
    }
    int getu()
    {
        return u;
    }
    int getv()
    {
        return v;
    }
    db getw()
    {
        return w;
    }
};
class Graph
{
public:
    int nVertices;
    vector<class Edge>v[maxn];
    db** distanceMatrix;
    int** parentMatrix;
    vi path;
    db* dist_bf;
    db* dist_dk;
    int* parent_dk;
    Graph()
    {

    }
    void setnVertices(int n)
    {
        nVertices = n;
        dist_dk = new db[n+1];
        dist_bf = new db[n+1];
        parent_dk = new int[n+1];
        distanceMatrix = new db*[n+1];
        for(int i=1; i<=n; i++)
        {
            distanceMatrix[i] = new db[n+1];
        }
        parentMatrix = new int*[n+1];
        for(int i=1; i<=n; i++)
        {
            parentMatrix[i] = new int[n+1];
        }
        cleanSPinfo();
    }
    bool addEdge(int x,int y,db z)
    {
        if(isEdge(x,y))
            return false;
        Edge e = Edge(x,y,z);
        v[x-1].pb(e);              ///since vector is 0 based indexed
        return true;
    }
    bool isEdge(int x,int y)
    {
        for(int i=0; i<v[x-1].size(); i++)
        {
            if(y==v[x-1][i].getv())
                return true;
        }
        return false;
    }
    void removeEdge(int x,int y)
    {
        if(!isEdge(x,y))
            return;
        auto it = v[x-1].begin();
        while(it!=v[x-1].end())
        {
            if(it->getv()==y)
            {
                v[x-1].erase(it);
                break;
            }
            it++;
        }
    }
    db getWeight(int x,int y)
    {
        if(x==y)
            return 0;
        else if(!isEdge(x,y))
            return INF;
        else
        {
            db wt;
            for(int i=0; i<v[x-1].size(); i++)
            {
                if(y==v[x-1][i].getv())
                {
                    wt = v[x-1][i].getw();
                    break;
                }
            }
            return wt;
        }
    }
    void reweightEdge(int x,int y,db z)
    {
        int id;
        if(!isEdge(x,y))
        {
            addEdge(x,y,z);
        }
        else
        {
            for(int i=0; i<v[x-1].size(); i++)
            {
                if(y==v[x-1][i].getv())
                {
                    id=i;
                    break;
                }
            }
            v[x-1][id].setw(z);
        }
    }
    Edge* searchEdge(int x,int y)
    {
        if(!isEdge(x,y))
            return NULL;
        Edge* e;
        for(int i=0; i<v[x-1].size(); i++)
        {
            if(y==v[x-1][i].getv())
                e = &v[x-1][i];
        }
        return e;
    }
    void printGraph()
    {
        for(int i=0; i<nVertices; i++)
        {
            cout<<i+1<<": ";
            for(int j=0; j<v[i].size(); j++)
            {
                if(j!=v[i].size()-1)
                    cout<<v[i][j].getv()<<"("<<v[i][j].getw()<<") -->";
                else
                    cout<<v[i][j].getv()<<"("<<v[i][j].getw()<<")";
            }
            cout<<endl;
        }
    }
    void floydWarshall()
    {
        for(int i=1; i<=nVertices; i++)
        {
            for(int j=1; j<=nVertices; j++)
            {
                distanceMatrix[i][j] = getWeight(i,j);
                if(isEdge(i,j))
                {
                    parentMatrix[i][j] = i;
                }
            }
        }
        for(int k=1; k<=nVertices; k++)
        {
            for(int i=1; i<=nVertices; i++)
            {
                for(int j=1; j<=nVertices; j++)
                {
                    if(distanceMatrix[i][k]+distanceMatrix[k][j] < distanceMatrix[i][j])
                    {
                        distanceMatrix[i][j] = distanceMatrix[i][k]+distanceMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j];
                    }
                }
            }
        }
    }
    void cleanSPinfo()
    {
        for(int i=1; i<=nVertices; i++)
        {
            for(int j=1; j<=nVertices; j++)
            {
                distanceMatrix[i][j] = INF;
                parentMatrix[i][j] = -1;
            }
        }
    }
    void printDistanceMatrix()
    {
        cout<<"Distance Matrix :\n";
        for(int i=1; i<=nVertices; i++)
        {
            for(int j=1; j<=nVertices; j++)
            {
                if(abs(distanceMatrix[i][j]-INF)<=epsilon)
                    cout<<"INF    ";
                else
                    cout<<distanceMatrix[i][j]<<"       ";
            }
            cout<<endl;
        }
    }
    void printPredecessorMatrix()
    {
        cout<<"Predecessor Matrix : \n";
        for(int i=1; i<=nVertices; i++)
        {
            for(int j=1; j<=nVertices; j++)
            {
                if(parentMatrix[i][j]==-1)
                    cout<<"NIL    ";
                else
                    cout<<parentMatrix[i][j]<<"       ";
            }
            cout<<endl;
        }
    }
    db getShortestPathWeight(int i,int j)
    {
        return distanceMatrix[i][j];
    }
    void printShortestPath (int i,int j)
    {
        printSP(i,j);
        int tmp = path[0];
        cout<<tmp<<" --> ";
        for(int i=1; i<path.size(); i++)
        {
            if(i!=path.size()-1)
                cout<<path[i]<<"("<<getWeight(tmp, path[i])<<")"<<" -- > ";
            else
                cout<<path[i]<<"("<<getWeight(tmp, path[i])<<")";
            tmp = path[i];
        }
        cout<<endl;
        path.clear();
    }
    int printSP(int i,int j)
    {
        if(i!=j)
            printSP(i,parentMatrix[i][j]);
        path.pb(j);
    }
    bool bellmanFord()
    {
        int src = nVertices;

        int n = nVertices;
        for(int i=1; i<=n; i++)
        {
            dist_bf[i] = INF;
        }
        dist_bf[src] = 0;
        for(int i=0; i<n-1; i++)
        {
            for(int j=1; j<=n; j++)
            {
                for(int k=1; k<=v[j-1].size(); k++)
                {
                    int next = v[j-1][k-1].getv();
                    db next_wt = v[j-1][k-1].getw();
                    if(dist_bf[j] + next_wt < dist_bf[next])
                    {
                        dist_bf[next] = dist_bf[j] + next_wt ;//cout<<dist[next]<<endl;
                    }
                }
            }
        }
        for(int j=1; j<=n; j++)
        {
            for(int k=1; k<v[j-1].size(); k++)
            {
                int next = v[j-1][k-1].getv();
                db next_wt = v[j-1][k-1].getw();
                if(dist_bf[j] + next_wt < dist_bf[next])
                {
                    return true;
                }
            }
        }
        return false;
    }
    void dijkstra(int src)
    {
        parent_dk = new int[nVertices+1];
        for(int i=1; i<=nVertices; i++)
        {
            parent_dk[i] = -1;
        }
        for(int i=1; i<=nVertices; i++)
        {
            dist_dk[i] = INF;
        }
        priority_queue<pdi, vector<pdi>, greater<pdi> >pq;  ///sorted in non-increasing order w.r.t distance
        dist_dk[src] = 0;
        pq.push(mp(0,src));
        while(!pq.empty())
        {
            pdi top = pq.top();
            pq.pop();

            int curr=top.second;
            for(int i=0; i<v[curr-1].size(); i++)
            {
                int next = v[curr-1][i].getv();
                db wt_next_curr = v[curr-1][i].getw();
                if(dist_dk[curr]+wt_next_curr < dist_dk[next])
                {
                    dist_dk[next] = dist_dk[curr]+wt_next_curr ;
                    parent_dk[next] = curr;
                    pq.push(mp(dist_dk[next], next));
                }
            }
        }
    }
    void johnsonsAlgo()
    {
        cleanSPinfo();
        int s = nVertices+1;
        nVertices++;
        for(int i=1; i<=nVertices-1; i++)
        {
            addEdge(s,i,0);
        }
        if(bellmanFord())
        {
            cout<<"There is a negative weight cycle\n";
            return;
        }
        else
        {
            for(int i=1; i<=nVertices; i++)
            {
                for(int j=1; j<=v[i-1].size(); j++)
                {

                    int vv = v[i-1][j-1].getv();
                    db ww = v[i-1][j-1].getw();
                    reweightEdge(i, vv, ww+dist_bf[i]-dist_bf[vv]);
                }
            }
            nVertices--;
            ///dijkstra run
            for(int i=1; i<=nVertices; i++)
            {
                dijkstra(i);
                for(int j=1; j<=nVertices; j++)
                {
                    distanceMatrix[i][j] = dist_dk[j]+dist_bf[j]-dist_bf[i];
                    parentMatrix[i][j] = parent_dk[j];
                }
            }
            ///graph er weight gula abar ager moto kore dilam
            for(int i=1; i<=nVertices; i++)
            {
                for(int j=1; j<=v[i-1].size(); j++)
                {
                    int vv = v[i-1][j-1].getv();
                    db ww = v[i-1][j-1].getw();
                    reweightEdge(i, vv, ww+dist_bf[vv]-dist_bf[i]);
                }
            }

        }
    }
    ~Graph()
    {
        for(int i=1;i<=nVertices;i++)
        {
            delete[]distanceMatrix[i];
            delete[]parentMatrix[i];
        }
        delete[] dist_bf;
        delete[] dist_dk;
        delete[] parent_dk;
    }
};
main()
{
    ifstream fin;
    fin.open("input.txt");
    Graph g;
    int u,v,c,s,d;
    db w;
    int n,m;
    fin>>n>>m;
    g.setnVertices(n);
    for(int i=1; i<=m; i++)
    {
        fin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    cout<<"Graph created"<<endl;
    while(1)
    {

        cout<<"1 . clean distance and parent matrix\n";
        cout<<"2 . Floyd warshall\n";
        cout<<"3 . Johnsons Algorithm\n";
        cout<<"4 . shortest path between two vertices\n";
        cout<<"5 . print Graph\n";
        cout<<"6 . print distance matrix\n";
        cout<<"7 . print predecessor matrix\n";

        cin>>c;
        if(c==1)
        {
            g.cleanSPinfo();
            cout<<"APSP matrices cleared"<<endl;
        }
        else if(c==2)
        {
            //g.cleanSPinfo();
            g.floydWarshall();
            cout<<"Floyd Warshall implemented"<<endl;
        }
        else if(c==3)
        {
            //g.cleanSPinfo();
            g.johnsonsAlgo();
            cout<<"Johnsons Algorithm implemented"<<endl;
        }
        else if(c==4)
        {
            cin>>s>>d;
            if(g.getShortestPathWeight(s,d)==INF)
            {
                cout<<"Not reachable\n";
            }
            else
            {
                cout<<"Shortest Path Weight : "<<g.getShortestPathWeight(s,d);
                cout<<"\nPath : ";
                g.printShortestPath(s,d);
            }

        }
        else if(c==5)
        {
            g.printGraph();
        }
        else if(c==6)
        {
            g.printDistanceMatrix();
        }
        else if(c==7)
        {
            g.printPredecessorMatrix();
        }
        else
        {
            break;
        }
    }
}
