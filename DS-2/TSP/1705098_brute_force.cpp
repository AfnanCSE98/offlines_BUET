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

const int maxn=1010;
const int INF = 1e5+10;

using namespace std::chrono;
using namespace std;

vi soln_list;
int tsp_bruteforce(vvi& data , int n, int s)
{
    vi all_possible_soln;
    vi vertex;
	ffr(i,0,n)
    {
        if (i != s)vertex.push_back(i);
    }
    int mn_dist = INT_MAX;
    while (next_permutation(vertex.begin(), vertex.end()))
    {
        int curr_dist =  0;
        all_possible_soln.erase(all_possible_soln.begin() , all_possible_soln.end());

        int k = s;
		for (int i = 0; i < vertex.size(); i++) {
			curr_dist += data[k][vertex[i]];
			k = vertex[i];
            all_possible_soln.pb(k);
		}
        curr_dist += data[k][s];

        if (curr_dist < mn_dist){
            soln_list.erase(soln_list.begin(), soln_list.end());
            for (int i = 0; i < all_possible_soln.size(); i++){
                    soln_list.push_back(all_possible_soln[i]);
            	}
	    }
	    mn_dist = min(mn_dist, curr_dist);
    }

    return mn_dist;

}
int main()
{
	freopen("data10.txt", "r", stdin);
    string str;cin>>str;
    int N;
	cin >> N;

	vector<vector<int>> graph(N, vector<int>(N));

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> graph[i][j];
		}
	}


    int s=0;
    auto start = high_resolution_clock::now();
    cout << "\n\nTotal Cost is " << tsp_bruteforce(graph , N , s);
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);
	float time = (duration.count())/(1e+9);
	cout<<"\nTime taken "<<time<<" s"<<endl;
}
