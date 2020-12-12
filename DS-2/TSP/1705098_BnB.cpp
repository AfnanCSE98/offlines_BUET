/**Bismillahir Rahmanir Rahimm**/

//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
using namespace std;

#define mp make_pair
#define pb push_back
#define ffr(i,a,b) for(int i=a;i<b;i++)
#define mm(a,b) memset(a,b,sizeof(a))
#define black 0
#define red 1
#define _(x) {cout << #x << " = " << x << " ";}
#define eq(x,y) (fabs((x)-(y)) < eps)
#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl


typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int,int> mii;

using namespace std::chrono;
using namespace std;

//int N;
#define INF INT_MAX

struct Node
{
    int cost, vertex, level;
    vpii path;
    vvi reducedMatrix;
};
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

typedef Node *Node_Ptr;
typedef vector<Node_Ptr> v_Nodeptr;

class tsp
{
public:
    int N;
    tsp(int x)
    {
        N=x;
    }

    void put_inf(Node_Ptr node, int level, int i, int j)
    {
        for (int k = 0; level != 0 and k < N; k++)
        {
            node->reducedMatrix[i][k] = INF;
            node->reducedMatrix[k][j] = INF;
        }
        node->reducedMatrix[j][0] = INF;

    }
    Node_Ptr CreateNewNode(vvi& parentMatrix, vpii &path,int level, int i, int j)
    {
        Node_Ptr node = new Node;
        node->path = path;
        // skip for root node
        if (level != 0)
        {
            node->path.push_back(make_pair(i, j));
        }

        node->reducedMatrix = parentMatrix;
        put_inf(node, level, i, j);
        node->level = level;
        node->vertex = j;
        return node;
    }

    void Reduction_row_col(vvi& reducedMatrix, vi& row, vi& col)
    {
        for (int i=0; i<N; i++)
        {
            row.pb(INF);
        }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (reducedMatrix[i][j] < row[i])
                    row[i] = reducedMatrix[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (reducedMatrix[i][j] != INF && row[i] != INF)
                    reducedMatrix[i][j] -= row[i];

        for (int i=0; i<N; i++)
            col.pb(INF);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (reducedMatrix[i][j] < col[j])
                    col[j] = reducedMatrix[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (reducedMatrix[i][j] != INF && col[j] != INF)
                    reducedMatrix[i][j] -= col[j];
    }


    int Find_Cost(vvi& reducedMatrix)
    {
        int cost = 0;
        vi row;
        vi col;
        Reduction_row_col(reducedMatrix, row, col);

        for (int i = 0; i < N; i++)
        {
            cost += (row[i] != INT_MAX) ? row[i] : 0;
            cost += (col[i] != INT_MAX) ? col[i] : 0;
        }
        return cost;
    }

    void Print(vpii const &lst)
    {
        cout<<"Path :\n";
        for (int i = 0; i < lst.size(); i++)
        {
            cout << lst[i].first << " => " << lst[i].second << endl;
        }

    }

    int solve(vvi&  costMatrix)
    {
        priority_queue<Node_Ptr, v_Nodeptr, comp> pq;

        vpii v;
        Node_Ptr root = CreateNewNode(costMatrix, v, 0, -1, 0);
        root->cost = Find_Cost(root->reducedMatrix);
        pq.push(root);

        while (!pq.empty())
        {
            Node_Ptr mn = pq.top();
            pq.pop();
            int i = mn->vertex;

            if (mn->level == N - 1)
            {
                mn->path.pb(make_pair(i, 0));
                Print(mn->path);
                return mn->cost;
            }
            for (int j = 0; j < N; j++)
            {
                if (mn->reducedMatrix[i][j] != INF)
                {
                    Node* child = CreateNewNode(mn->reducedMatrix, mn->path,mn->level + 1, i, j);
                    child->cost = mn->cost + mn->reducedMatrix[i][j] + Find_Cost(child->reducedMatrix);
                    pq.push(child);
                }
            }
            delete mn;
        }
        return 0;
    }
};
int main()
{
    freopen("data15.txt", "r", stdin);
    string s;
    cin>>s;
    int N;
    cin >> N;

    vector<vector<int>> costMatrix(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (costMatrix[i][j] == -1)
            {
                costMatrix[i][j] = INF;
            }
            cin >> costMatrix[i][j];
        }
    }
    tsp t(N);
    auto start = high_resolution_clock::now();
    cout << "\nTotal Cost is " << t.solve(costMatrix);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    float time = (duration.count())/(1e+9);
    cout<<"\nTime taken "<<time<<" s"<<endl;
}
