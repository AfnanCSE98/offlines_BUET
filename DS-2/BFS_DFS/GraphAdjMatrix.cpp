#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <chrono>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;
using namespace std::chrono;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ;
	int* clr;
	int* distance;
	int* d_clr;
	int* d_parent;
	int* parent; ///adjacency matrix to store the graph
	///define other variables required for bfs such as color, parent, and dist
	///you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void setEdges(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
    void dfs(int s);
    void dfs_visit(int s);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
//	clr = new int[nVertices];
//	distance = new int[nVertices];
//	parent = new int[nVertices];
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    clr = new int[nVertices];
	d_clr = new int[nVertices];
	distance = new int[nVertices];
	parent = new int[nVertices];
	d_parent = new int[nVertices];
}

bool Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    this->nEdges++;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

    return true;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    nEdges--;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(!directed)
    {
            if(matrix[u][v]==1 or matrix[v][u]==1)return true;
            else return false;
    }
    if(matrix[u][v]==1)return true;
    else return false;
}

int Graph::getOutDegree(int u)
{
    //returns the degree of vertex u
    int cnt = 0;
    if(directed)
    {
        for(int i = 0; i < nVertices; i++)
            if(matrix[u][i] == 1) cnt++;
    }
    else
    {
        for(int i = 0; i < nVertices; i++)
            if(matrix[u][i] == 1)
            {
                if(i == u) cnt += 2;
                else cnt++;
            }
    }
    return cnt;
}
int Graph::getInDegree(int u)
{
    int cnt = 0;
    if(directed)
    {
        for(int i = 0; i < nVertices; i++)
            if(matrix[i][u] == 1) cnt++;
    }
    else
    {
        for(int i = 0; i < nVertices; i++)
            if(matrix[i][u] == 1)
            {
                if(i == u) cnt += 2;
                else cnt++;
            }
    }
    return cnt;
}
void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    cout<<"The adjacent vertices are : ";
    for(int i = 0; i < nVertices; i++)
    {
        if(u == i) continue;
        if(matrix[u][i]) cout<<i<<" ";
    }
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    ///returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i] && matrix[v][i]) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //write this function
    if(source<0 or source>=nVertices)return ;
    int u,v;
    for(int i=0;i<nVertices;i++)
    {
        if(i==source)continue;
        clr[i] = WHITE;
        distance[i] = INFINITY;
        parent[i] = NULL_VALUE;
    }
    ///cout<<source<<" ";
    clr[source] = GREY;
    distance[source] = 0;
    parent[source] = NULL_VALUE;

    Queue Q ;
    Q.enqueue(source);

    while(!Q.empty())
    {
        u = Q.dequeue();
        clr[u] = GREY;
        for(int i=0;i<nVertices;i++)
        {
            if(matrix[u][i] and clr[i] == WHITE)
            {
                ///cout<<i<<" ";
                clr[i] = GREY;
                distance[i]= distance[u]+1;
                parent[i]=u;
                Q.enqueue(i);
            }
        }
        clr[u]=BLACK;
    }
    return;

}
void Graph::dfs(int source)
{
    if(source<0 || source>=nVertices) return;

    int u;

    for(int i = 0; i < nVertices; i++){
        d_clr[i] = WHITE;
        d_parent[i] = NULL_VALUE;
    }
    dfs_visit(source);
    cout << endl;
}

void Graph::dfs_visit(int u)
{
    cout << u << " ";
    d_clr[u] = GREY;

    for(int i = 0; i < nVertices; i++){
        if(d_clr[i] == WHITE and matrix[u][i]){
            d_parent[i] = u;
            dfs_visit(i);
        }
    }
    d_clr[u] = BLACK;
}
int Graph::getDist(int u, int v)
{
    ///returns the shortest path distance from u to v
    ///must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return distance[v];
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}
void Graph::setEdges(int edges)
{
    for(int i=0;i<edges;i++)
    {
        int u = rand()%nVertices;
        int v = rand()%nVertices;
        while(u==v){
            v = rand()%nVertices;
        }
        addEdge(u,v);
    }
    ///chk if any disconnected component exists
    for(int i=0;i<nVertices;i++)
    {
        int cnt=0;
        for(int j=0;j<nVertices;j++)
        {
            if(matrix[i][j]==0)cnt++;
        }
        if(cnt==nVertices)
        {
            int tmp = rand()%nVertices;
            while(tmp==i){
                tmp = rand()%nVertices;
            }
            addEdge(i,tmp);
        }
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(matrix)delete [] matrix;
    if(parent) delete [] parent;
    if(clr)delete[] clr;
    if(distance)delete[] distance;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{

    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    printf("Enter number of edges: ");
    int edges;scanf("%d" , &edges);
    g.setEdges(edges);

    while(1)
    {
        printf("\n1. Add edge. \n");
        printf("2. Remove edge.\n");
        printf("3. Check if there is edge between 2 vertices \n");
        printf("4. Get degree of a vertex\n");
        printf("5. Print adjacent vertices\n");
        printf("6. Check if two vertices has any common adjoint vertex\n");
        printf("7. Find the shortest distance between two connected graphs\n");
        printf("8. Run Breadth First Search with source s\n");
        printf("9. Run dfs\n");
        printf("10. Print Graph\n11. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            cout<<"Enter U and V (U--v):"<<endl;
            cin>>u>>v;
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u,v;
            cout<<"Enter U and V (U--v):"<<endl;
            cin>>u>>v;
            if(g.isEdge(u,v))cout<<"There is edge between vertices "<<u<<" and "<<v<<endl;
            else cout<<"There is no edge between vertices "<<u<<" and "<<v<<endl;
        }
        else if(ch==4)// get number of indegree and outdegree
        {
            int u,ch2=0;
            cout<<"Enter vertex U: "<<endl;
            cin>>u;
            if(dir)
            {
                cout<<"1.Indegree 2.Outdegree"<<endl;
                cin>>ch2;
            }
            if(ch2==1)cout<<"Indegree of vertex "<<u<<" :"<<g.getInDegree(u);
            else if (ch2==2)cout<<" Outdegree of vertex "<<u<<" :"<<g.getOutDegree(u);
        }
        else if(ch==5) // print adjacent vertices
        {
            int u;
            cout<<"Enter vertex U:" <<endl;
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==6)// has common vertices
        {
            int u,v;
            cout<<"Enter vertex U and V (U--v): "<<endl;
            cin>>u>>v;
            if(g.hasCommonAdjacent(u,v))cout<<"The vertices "<<u<<" and "<<v<<" have common vertices."<<endl;
            else cout<<"The vertices "<<u<<" and "<<v<<" does not have common vertices."<<endl;
        }
        else if(ch==7)// shortest distance between two connected graphs
        {
            int u,v;
            cout<<"Enter vertex U and V: "<<endl;
            cin>>u>>v;
            int distance = g.getDist(u,v);
            if(distance==INFINITY)cout<<"The two vertices are not connected"<<endl;
            else cout<<"The shortest distance between "<<u<<" and "<<v<<" is :"<<distance<<endl;
        }
        else if(ch==8)// bfs with source s
        {
            int s;
            cout<<"Enter source"<<endl;
            cin>>s;
            auto start = high_resolution_clock::now();
            g.bfs(s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<endl<<"Time taken for bfs is "<<duration.count()/1000<<" nanoseconds"<<endl;

        }
        else if(ch==9)
        {
            int s;
            cout<<"Enter source"<<endl;
            cin>>s;
            auto start = high_resolution_clock::now();
            g.dfs(s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<endl<<"Time taken for dfs is "<<duration.count()/1000<<" nanoseconds"<<endl;

        }
        else if(ch==10)
        {
            g.printGraph();
        }
        else break;
    }

}
