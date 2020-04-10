
#include<bits/stdc++.h>
#include <chrono>
#define NULL_VALUE -999999
#define INF 999999
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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int* clr;
	int* distance;
	int* parent;
	///dfs variables
	int time;
	int* d_clr;
	int* d_parent;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void setEdges(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void dfs(int s);
    void dfs_visit(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void topsortutil(int v,bool*vis , stack<int>&s);
    void topsort();
    int connectedcomp();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
//	clr = new int[nVertices];
//	distance = new int[nVertices];
//	parent = new int[nVertices];
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	clr = new int[nVertices];
	d_clr = new int[nVertices];
	distance = new int[nVertices];
	parent = new int[nVertices];
	d_parent = new int[nVertices];
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    if(!directed)if(adjList[u].searchItem(v)!=NULL_VALUE or adjList[v].searchItem(u)!=NULL_VALUE)return false;
    if(directed)if(adjList[u].searchItem(v)!=NULL_VALUE)return false;
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;

	return true;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges--;
    adjList[u].removeItem(v);
    if(!directed)adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
     if(u<0 || v<0 || u>=nVertices || v>=nVertices) return 0;
     if(adjList[u].searchItem(v) == NULL_VALUE)
        return false;
    else return true;
}

int Graph::getOutDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}
int Graph::getInDegree(int u)
{
    int cnt=0;
    for(int i=0;i<nVertices;i++){
        if(i==u)continue;
        if(adjList[i].searchItem(u)!=NULL_VALUE)cnt++;
    }
    return cnt;
}
void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    for(int i=0;i<adjList[u].getLength();i++){
        printf("%d ", adjList[u].getItem(i));
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
     for(int i = 0; i < adjList[u].getLength(); i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i)) != NULL_VALUE)
            return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    if(source<0 || source>=nVertices) return;

    Queue q;
    int u;

    for(int i = 0; i < nVertices; i++){
        distance[i] = INF;
        clr[i] = WHITE;
        parent[i] = NULL_VALUE;
    }
    cout << source << " ";

    distance[source] = 0;
    clr[source] = GREY;
    parent[source] = NULL_VALUE;
    q.enqueue(source);

    while(!q.empty()){

        u = q.dequeue();

        for(int i = 0; i < adjList[u].getLength(); i++){

            int v = adjList[u].getItem(i);

            if(clr[v] == WHITE){

                cout << v << " ";
                clr[v] = GREY;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                q.enqueue(v);
            }
        }
        clr[u] = BLACK;
    }
    cout << endl;

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

    int v;
    for(int i = 0; i < adjList[u].getLength(); i++){
        v = adjList[u].getItem(i);
        if(d_clr[v] == WHITE){
            d_parent[v] = u;
            dfs_visit(v);
        }
    }
    d_clr[u] = BLACK;
}
int Graph:: connectedcomp()
{
    int n=0;
    for(int i=0;i<nVertices;i++)d_clr[i] = WHITE;
    for(int i=0;i<nVertices;i++)
    {
        if(d_clr[i]==WHITE)
        {
            dfs_visit(i);
            n++;
        }
    }
    return n;
}
void Graph::topsortutil(int v , bool visited[] , stack<int>&s)
{
    visited[v] = true;
    for(int i=0;i<adjList[v].getLength();i++)
    {
        int tmp = adjList[v].getItem(i);
        if(!visited[tmp])
        {
            topsortutil(tmp , visited , s);
        }
    }
    s.push(v);
}
void Graph::topsort()
{
    stack<int> s;
    bool visited[nVertices];
    for(int i=0;i<nVertices;i++)visited[i]=false;

    for(int i=0;i<nVertices;i++)
    {
        if(!visited[i])
        {
            topsortutil(i,visited , s);
        }
    }
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
}


int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return distance[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
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
    for(int i=0;i<nVertices;i++)
    {
        if(adjList[i].empty())
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
    if(adjList)delete [] adjList;
    if(parent) delete [] parent;
    if(clr)delete[] clr;
    if(distance)delete[] distance;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n,edges;
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
    printf("\nEnter number of edges: ");
    scanf("%d" , &edges);
    g.setEdges(edges);

    ///addedge thik korte hbe
//    g.addEdge(1,2);
//    g.addEdge(1,0);
//    g.addEdge(3,0);
//    g.addEdge(3,5);
//    g.addEdge(5,6);
//    g.addEdge(4,0);
//    g.addEdge(4,7);
    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove edge.\n");
        printf("3. Check if there is edge between 2 vertices \n");
        printf("4. Get degree of a vertex\n");
        printf("5. Print adjacent vertices\n");
        printf("6. Check if two vertices has any common adjoint vertex\n");
        printf("7. Find the shortest distance between two connected nodes\n");
        printf("8. Run Breadth First Search with source s\n");
        printf("9. Run depth First Search with source s\n");
        printf("10. Print Graph\n");
        printf("11.Exit\n");

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
        else if(ch==11)break;
        else if(ch==12)cout<<"connected comp : "<<g.connectedcomp()<<endl;
        else if(ch==13)g.topsort();
    }

}
