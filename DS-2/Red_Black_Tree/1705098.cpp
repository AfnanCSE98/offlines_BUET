                                            /**Bismillahir Rahmanir Rahimm**/

#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define ffr(i,a,b) for(int i=a;i<b;i++)
#define mm(a,b) memset(a,b,sizeof(a))
#define black 0
#define red 1
#define _(x) {cout << #x << " = " << x << " ";}


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


struct node
{
    int val;
    node* left;
    node* right;
    node* par;
    int col;
};

class RBT
{
    node* root;
    node* nil;

public:

    RBT()
    {
        nil = new node;
        nil->col = black;
        root = nil;
    }

    void Left_Rotate(node* x)
    {
        node* y = x->right;

        x->right = y->left;

        if(y->left != nil)
            y->left->par = x;

        y->par = x->par;
        if(x->par == nil)
            root = y;
        else if(x == x->par->left)
            x->par->left = y;
        else
            x->par->right = y;

        y->left = x;

        x->par = y;
    }
    void Right_Rotate(node* x)
    {
        node* y = x->left;

        x->left = y->right;

        if(y->right != nil)
            y->right->par = x;

        y->par = x->par;

        if(x->par == nil)
            root = y;
        else if(x == x->par->right)
            x->par->right = y;
        else
            x->par->left = y;
        y->right = x;

        x->par = y;
    }

    node* Search_RBT(node* x, int k)
    {
        if( (x == nil) || (x->val == k) )
            return x;

        if(k < x->val)
            return Search_RBT(x->left, k);
        else
            return Search_RBT(x->right, k);
    }

    void Insert_Fix(node* z)
    {
        while(z->par->col == red)
        {
            /// The par of z is a left child
            if(z->par == z->par->par->left)
            {
                /// y is the uncle of z
                node* y = z->par->par->right;

                /// Case 1: y is red
                if(y->col == red)
                {
                    z->par->col = black;
                    y->col = black;
                    z->par->par->col = red;
                    z = z->par->par;
                }
                else
                {
                    /// Case 2: y is black and z is a right child
                    if(z == z->par->right)
                    {
                        z = z->par;
                        Left_Rotate(z);
                    }

                    /// Case 3: y is black and z is a left child
                    z->par->col = black;
                    z->par->par->col = red;
                    Right_Rotate(z->par->par);
                }
            }

            /// The parent of z is a right child
            else
            {
                /// y is the uncle of z
                node* y = z->par->par->left;

                /// Case 1: y is red
                if(y->col == red)
                {
                    z->par->col = black;
                    y->col = black;
                    z->par->par->col = red;
                    z = z->par->par;
                }
                else
                {
                    /// Case 2: y is black and z is a left child
                    if(z == z->par->left)
                    {
                        z = z->par;
                        Right_Rotate(z);
                    }

                    /// Case 3: y is black and z is a left child
                    z->par->col = black;
                    z->par->par->col = red;
                    Left_Rotate(z->par->par);
                }
            }
        }

        root->col = black;
    }

    void Insert(node* z)
    {
        node* y = nil;
        node* x = root;

        while(x != nil)
        {
            y = x;

            if(z->val < x->val)
                x = x->left;
            else
                x = x->right;
        }

        z->par = y;

        if(y == nil)
            root = z;
        else if(z->val < y->val)
            y->left = z;
        else
            y->right = z;

        z->left = nil;
        z->right = nil;
        z->col = red;

        Insert_Fix(z);
    }

     void Delete(node* z)
    {
        node* x;
        node* y = z;
        char y_original_col = y->col;

        if(z->left == nil)
        {
            x = z->right;
            Transplant(z, z->right);
        }
        else if(z->right == nil)
        {
            x = z->left;
            Transplant(z, z->left);
        }
        else
        {
            y = get_min(z->right);
            y_original_col = y->col;
            x = y->right;

            if(y->par == z)
                x->par = y;
            else
            {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->par = y;
            }

            Transplant(z, y);

            y->left = z->left;
            y->left->par = y;
            y->col = z->col;
        }

        delete z;

        if(y_original_col == black)
            Delete_Fix(x);
    }

    void Delete_Fix(node* x)
    {
        node* w;

        while( (x != root) && (x->col == black) )
        {
            /// x is a left child
            if(x == x->par->left)
            {
                /// w is the sibling of x
                w = x->par->right;

                /// Case 1: w is red
                if(w->col == red)
                {
                    w->col = black;
                    x->par->col = red;
                    Left_Rotate(x->par);
                    w = x->par->right;
                }

                /// Case 2: w is black.Both children of w are black
                if( (w->left->col == black) && (w->right->col == black) )
                {
                    w->col = red;
                    x = x->par;
                }
                else
                {
                    /// Case 3: w is black.The left child of w is red.The right child of w is black
                    if(w->right->col == black)
                    {
                        w->left->col = black;
                        w->col = red;
                        Right_Rotate(w);
                        w = x->par->right;
                    }
                    /// Case 3: w is black.The right child of w is red
                    w->col = x->par->col;
                    x->par->col = black;
                    w->right->col = black;
                    Left_Rotate(x->par);
                    x = root;
                }
            }

            /// x is a right child
            else
            {
                /// w is the sibling of x
                w = x->par->left;

                /// Case 1: w is red
                if(w->col == red)
                {
                    w->col = black;
                    x->par->col = red;
                    Right_Rotate(x->par);
                    w = x->par->left;
                }

                /// Case 2: w is black.Both children of w are black
                if( (w->right->col == black) && (w->left->col == black) )
                {
                    w->col = red;
                    x = x->par;
                }
                else
                {
                    /// Case 3: w is black.The right child of w is red.The left child of w is black
                    if(w->left->col == black)
                    {
                        w->right->col = black;
                        w->col = red;
                        Left_Rotate(w);
                        w = x->par->left;
                    }

                    /// Case 3: w is black.The left child of w is red
                    w->col = x->par->col;
                    x->par->col = black;
                    w->left->col = black;
                    Right_Rotate(x->par);
                    x = root;
                }
            }
        }

        x->col = black;
    }

     void Transplant(node* u, node* v)
    {
        if(u->par == nil)
            root = v;
        else if(u == u->par->left)
            u->par->left = v;
        else
            u->par->right = v;

        v->par = u->par;
    }

    node* get_min(node* x)
    {
        while(x->left != nil)
            x = x->left;

        return x;
    }

    void Print_RBT(node* root)
    {
        if(root == nil)
            return;
        cout << root->val << ":";
        if(root->col == red)cout << "r";
        else cout << "b";

        if( (root->left != nil) || (root->right != nil) )
        {
            cout << "(";
            Print_RBT(root->left);
            cout << ")";

            cout << "(";
            Print_RBT(root->right);
            cout << ")";
        }
    }

    void Insert(int val)
    {
        node* z = new node;
        z->val = val;

        Insert(z);
    }

    void Delete(int val)
    {
        node* z = Search_RBT(root, val);

        Delete(z);
    }

    bool Find(int val)
    {
        return Search_RBT(root, val) != nil;
    }

    void Print()
    {
        Print_RBT(root);
    }

    void clear_memory(node* root)
    {
        if(root == nil)
            return;

        clear_memory(root->left);
        clear_memory(root->right);

        delete root;
    }

    ~RBT()
    {
        clear_memory(root);
        delete nil;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    FILE *fp;
    ///uncomment to output in a file
    fp = freopen("output.txt", "w+", stdout);
    char op;
    int key;

    RBT t;
    while(true)
    {
        ///cin >> op >> val;
        if( scanf("%c%d\n", &op, &key) == EOF )
            break;

        if(op == 'I')
        {
            t.Insert(key);
            t.Print();
        }
        else if(op == 'D')
        {
            t.Delete(key);
            t.Print();
        }
        else if(op == 'F')
        {
            if(t.Find(key))
                cout << "True";
            else
                cout << "False";
        }
        cout << endl;
    }

    return 0;
}
