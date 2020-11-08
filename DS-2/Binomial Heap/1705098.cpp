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
typedef vector<ll> vl;
typedef set<int> si;
typedef multiset<int> msi;
typedef map<int,int> mii;

const int maxn=1010;
const int INF = 1e5+10;

struct Node {
	int val;
	int degree;
	Node *parent;
	Node *child; ///ptr that points to the leftmost child
	Node *sibling; /// ptr that points to the right sibling
};

typedef Node *Node_Pointer;

class BinomialHeap {
public:
	Node_Pointer head;

	BinomialHeap() {
		head = nullptr;
	}
	void initialize_New_Node(Node_Pointer node, int val, int degree) {
		node->val = val;
		node->degree = degree;
		node->parent = nullptr;
		node->child = nullptr;
		node->sibling = nullptr;
	}

    int C(int n, int r) {
        if(r > n - r) r = n - r; // because C(n, r) == C(n, n - r)
        int ans = 1;
        int i;

        for(i = 1; i <= r; i++) {
            ans *= n - r + i;
            ans /= i;
        }

        return ans;
    }

	///x will be parent of y
    void link_Two_BinomialTrees(Node_Pointer x, Node_Pointer y) {
		y->parent = x;
		y->sibling = x->child;
		x->child = y;
		x->degree += 1;
	}

	Node_Pointer find_Min() {
		int mn = INT_MAX;
		Node_Pointer current_Ptr = head;
		Node_Pointer minimum_Ptr = nullptr;

		while (current_Ptr != nullptr){
			if (current_Ptr->val < mn){
				mn = current_Ptr->val;
				minimum_Ptr =current_Ptr;
			}
			current_Ptr = current_Ptr->sibling;
		}
		return minimum_Ptr;
	}

	void print() {
	    cout<<"Printing Binomial Heap..."<<endl;
	    Node_Pointer currPtr = new Node;
		currPtr = head;
		while (currPtr != nullptr) {

			cout<<"Binomial Tree, "<<"B"<<currPtr->degree<<endl;
			queue<Node_Pointer> q;

			q.push(currPtr);

			int r=0;
			int sz = currPtr->degree;
			int seq[sz+1];seq[0] = 1;
			for(int i=1 ; i<=sz ; i++)
            {
                seq[i] = C(sz , i) + seq[i-1];
            }

            int koyta = 0;
            int i = 0;
            cout<<"Level "<<"0"<<" : ";
			while (!q.empty()) {
				Node_Pointer p = q.front();
				q.pop();

				cout<<p->val<<" ";
                koyta++;
                if(koyta==seq[i]){
                    cout<<endl;
                    i++;
                    if(i<=sz)cout<<"Level "<<i<<" : ";
                }

				if (p->child != nullptr) {
					Node_Pointer tempPtr = p->child;
					while (tempPtr != nullptr) {
						q.push(tempPtr);
						tempPtr = tempPtr->sibling;
					}
				}
			}
			currPtr = currPtr->sibling;
			//cout<<endl<<endl;

		}
	}

	Node_Pointer get_HeadPointer() {
		return head;
	}

	void set_HeadPointer(Node_Pointer head) {
		this->head = head;
	}

	void insert(int val) {
		BinomialHeap h;
		Node_Pointer node = new Node;
		initialize_New_Node(node, val, 0);
		h.set_HeadPointer(node);
		Union(h);
	}

	Node_Pointer copy_ptr(Node_Pointer y)
	{
	    Node_Pointer x = new Node;
	    x->val = y->val;
	    x->parent = y->parent;
	    x->child = y->child;
	    x->degree = y->degree;
	    x->sibling = y->sibling;
	    return x;
	}
	void Union(BinomialHeap h1) {
        Node_Pointer tmp1 = get_HeadPointer();
		Node_Pointer tmp2 = h1.get_HeadPointer();
		Node_Pointer tmp3 = new Node;
		Node_Pointer temp = new Node;

            if (tmp1!=nullptr and tmp1->degree <= tmp2->degree) {
			tmp3 = tmp1;
			tmp1 = tmp1->sibling;
		} else {
			tmp3 = tmp2;
			tmp2 = tmp2->sibling;
		}

		temp = tmp3;

		while(tmp1 != nullptr and tmp2 != nullptr){///Union of 2 heaps without considering the same degree and the roots of the trees are in ascending order of degree
			if (tmp1->degree <= tmp2->degree) {
				tmp3->sibling = tmp1;
				tmp1 = tmp1->sibling;
			} else {
				tmp3->sibling = tmp2;
				tmp2 = tmp2->sibling;
			}

			tmp3 = tmp3->sibling;
		}

		if (tmp1 != nullptr) {
			while(tmp1 != nullptr) {///copying all the remaining trees of heap1
				tmp3->sibling = tmp1;
				tmp1 = tmp1->sibling;
				tmp3 = tmp3->sibling;
			}
		}

		if (tmp2 != nullptr) {
			while(tmp2 != nullptr) {/// copying all the remaining trees of heap2
				tmp3->sibling = tmp2;
				tmp2 = tmp2->sibling;
				tmp3 = tmp3->sibling;
			}
		}


		///Now merging trees with same degree
		tmp3 = temp;
		Node_Pointer prev = nullptr;
		Node_Pointer next = tmp3->sibling;

		while (next != nullptr) {
			///If 2 adjacent tree has same degree or 3 consecutive trees have same degree , then move to next tree
			if ((tmp3->degree != next->degree )|| (next->sibling != nullptr and tmp3->degree == next->sibling->degree)) {
				prev = tmp3;
				tmp3 = next;
			} else {
				///Else union
				if (tmp3->val <= next->val) {
					tmp3->sibling = next->sibling;
					BinomialHeap::link_Two_BinomialTrees(tmp3, next);
				} else {
					if (prev == nullptr) {
						temp = next;
					} else {
						prev->sibling = next;
					}

				    link_Two_BinomialTrees(next, tmp3);
					tmp3 = next;
				}
			}

			next = tmp3->sibling;
		}
		//if(temp->val==613)cout<<temp->val;
		set_HeadPointer(temp);
		//if(head->val==613)cout<<"thik";
		//}

	}

	Node_Pointer Extract_Min() {
		Node_Pointer curr = head;
		Node_Pointer prevMin = nullptr;
		Node_Pointer minPtr = nullptr;
		Node_Pointer prevPtr = nullptr;
		int mn = 999999;

		if(head->sibling == nullptr and head->child==nullptr){
            Node_Pointer xyz = head;
            head = nullptr;return xyz;
		}
		while (curr != nullptr) {///First find the root with minimum key
			if(curr->val <= mn) {
				mn = curr->val;
				prevMin = prevPtr;
				minPtr = curr;
			}
			prevPtr = curr;
			curr = curr->sibling;
		}

		if(prevMin != nullptr and minPtr->sibling != nullptr){///deleting node minPtr
			prevMin->sibling = minPtr->sibling;
		}else if(prevMin != nullptr and minPtr->sibling == nullptr){
			prevMin->sibling = nullptr;
		}else if(prevMin == nullptr and minPtr->sibling != nullptr){
            head = minPtr->sibling;
		}else if(prevMin == nullptr and minPtr->sibling == nullptr){
            head = nullptr;
		}

		Node_Pointer childPtr = minPtr->child;///removing parent reference from all its child
		while (childPtr != nullptr) {
			childPtr->parent = nullptr;
			childPtr = childPtr->sibling;
		}

		stack<Node_Pointer> s;
		childPtr = minPtr->child;
		while (childPtr != nullptr) {///reversing the order
			s.push(childPtr);
			childPtr = childPtr->sibling;
		}

		Node_Pointer temp = nullptr;
		if(!s.empty()){
            curr = s.top();
            temp = curr;
            s.pop();
		}

		while (!s.empty()) {
			curr->sibling = s.top();
			s.pop();
			curr = curr->sibling;
		}

		curr->sibling = nullptr;
		BinomialHeap h;
		h.set_HeadPointer(temp);

		// Union
		Union(h);

		// return the min root
		return minPtr;
	}

};

int main() {

    ifstream fin;
    fin.open("input.txt");

    FILE *fp;
    ///uncomment to output in a file
    //fp = freopen("output.txt", "w+", stdout);

    char op;int key;
    BinomialHeap h;

    while(true)
    {

        fin>>op;
        //cout<<op<<endl;
        if(fin.eof())break;
        if(op=='I'){
            fin>>key;
            h.insert(key);
        }
        else if(op=='E'){
            cout<<"Extract-Min returned "<<h.Extract_Min()->val<<endl;
        }
        else if(op=='P')
        {
            h.print();
        }
        else if(op=='F'){
            cout<<"Find-Min returned "<<h.find_Min()->val<<endl;
        }
        else if(op=='U'){
            BinomialHeap h2;
            while( (fin.peek()!='\n') and (fin>>key) )
            {
                h2.insert(key);
            }
            //h2.print();
            h.Union(h2);
        }
    }

	return 0;
}
