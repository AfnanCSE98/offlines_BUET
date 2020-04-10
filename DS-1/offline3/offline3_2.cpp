#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;

#define bound 10

class Queue{
    int fr,rr,capacity;
    int* ara;
public:
    Queue()
    {
        fr=rr=0;
        capacity=10;
        ara = new int[capacity];
    }
    int* create_new()
    {
        int* new_ara;
        new_ara = new int[capacity+bound];
        for(int i=0;i<rr;i++)
        {
            new_ara[i] = ara[i];
        }
        capacity+=bound;
        return new_ara;
    }
    void enqueue(int val)
    {
        if(rr==capacity)
        {
            ara = create_new();
        }
        ara[rr] = val;
        rr++;
    }
    void dequeue()
    {
        if(rr==fr)
        {
            cout<<"queue is empty!\n";
            return;
        }
        else
        {
            cout<<"dequeue function called\n";
            for (int i=0;i<rr-1;i++)
            {
                ara[i] = ara[i+1];
            }
            rr--;
        }
    }
    bool empty()
    {
        return (fr==rr);
    }
    int size()
    {
        return rr;
    }
    int& front()
    {
        if(fr==rr){cout<<"queue is empty!\n";exit(0);}
         return ara[fr];
    }
    int& rear()
    {
        if(fr==rr){cout<<"queue is empty!\n";exit(0);}
         return ara[rr];
    }
    void display()
    {
        if (fr == rr) {
            cout<<"\nQueue is Empty\n";
            return;
        }
        cout<<"Stack : \n";
        for (int i = fr; i < rr; i++) {
            cout<<ara[i]<<" ";
        }
        cout<<endl;
        return;
    }
};
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
	int* discovery;
	int* finish;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void dfs(int s);
    void DFS();
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	clr = new int[nVertices];
	distance = new int[nVertices];
	parent = new int[nVertices];
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
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
    //complete this function
    //initialize BFS variables for all n vertices first
    if(source<0 or source>=nVertices)return ;
    int u,v;
    for(int i=0;i<nVertices;i++)
    {
        if(i==source)continue;
        clr[i] = WHITE;
        distance[i] = INFINITY;
        parent[i] = NULL_VALUE;
    }
    clr[source] = GREY;
    distance[source] = 0;
    parent[source] = NULL_VALUE;

    Queue Q ;
    Q.enqueue(source);

    while(!Q.empty())
    {
        u = Q.dequeue();
        cout<<u<<" ";
        for(int i=0;i<adjList[u].getLength();i++)
        {
            v = adjList[u].getItem(i);
            if(clr[v]==WHITE)
            {
                clr[v]==GREY;
                distance[v]= distance[u]+1;
                parent[v]=u;
                Q.enqueue(v);
            }
        }
        clr[u]=BLACK;
    }
    cout<<endl;
    return;

}
void Graph::dfs(int s)
{
    time+=1;
    discovery[s] = time;
    d_clr[s] = GREY;
    cout<<s<<" ";
    for(int i=0;i<adjList[s].getLength();i++)
    {
        int tmp = adjList[s].getItem(i);
        if(d_clr[tmp]==WHITE)
        {
            d_parent[tmp] = s;
            dfs(tmp);
        }
    }
    d_clr[s] = BLACK;
    time+=1;
    finish[s] = time;
}
void Graph::DFS()
{
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0; j<adjList[i].getLength();j++)
        {
           d_clr[ adjList[i].getItem(j) ] = WHITE;
           d_parent[adjList[i].getItem(j)] = NULL_VALUE;
        }
    }
    time=0;
    for(int i=0;i<nVertices;i++)
    {
        if(d_clr[i]==WHITE)
        {
            dfs(i);
        }
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

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove edge.\n");
        printf("3. Check if there is edge between 2 vertices \n");
        printf("4. Get degree of a vertex\n");
        printf("5. Print adjacent vertices\n");
        printf("6. Check if two vertices has any common adjoint vertex\n");
        printf("7. Find the shortest distance between two connected graphs\n");
        printf("8. Run Breadth First Search with source s\n");
        printf("9. Print Graph\n10. Exit.\n");

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
            g.bfs(s);
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }

}
