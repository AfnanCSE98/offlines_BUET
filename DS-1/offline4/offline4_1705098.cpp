#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int key;
    Node* left;
    Node* right;
};
class BST
{
    int sz;
public:
    Node* rootnode;
    BST(Node* ob)
    {
        rootnode = new Node;
        rootnode->key=ob->key;
        rootnode->left=NULL;
        rootnode->right=NULL;
        sz=1;
    }
    BST()
    {
        rootnode = new Node;
        rootnode->left=NULL;
        rootnode->right=NULL;
        sz=0;
    }
    Node* newNode(int val)
    {
        Node* tmp = new Node;
        tmp->key = val;
        tmp->left = tmp->right = nullptr;
        return tmp;
    }

    bool search(Node* root, int val)
    {
        if(!root){
            return false;
        }

        if(root->key==val)
            return true;
        else if(val > root->key)
        {
            return search(root->right, val);
        }
        else
            return search(root->left, val);
    }
    bool search(int val)
    {
        return search(rootnode, val);
    }

    Node* Insert(Node* root, int val)
    {
        //cout << "second insert" << endl;
        if(sz==0)
        {
            rootnode->key = val;
            sz++;
            return rootnode;
        }
        else if(!search(root, val))
        {
            if(root==NULL)
            {
                sz++;
                Node* ptr=newNode(val);
                return ptr;
            }
            else if(val>root->key)
            {
                root->right = Insert(root->right, val);
            }
            else
                root->left = Insert(root->left, val);
        }
        else
            return nullptr;
    }
    void Insert(int val)
    {
        rootnode = Insert(rootnode, val);
    }
    Node* minvalue(Node* tmp)
    {
        Node* curr = tmp;
        while(curr->left)
        {
            curr = curr->left;
            if(curr->left==NULL and curr->right==NULL)
                return curr;
        }
    }

    Node* deleteNode(Node* root, int val)
    {
        if(!search(root,val))
            return nullptr;
        if (root == NULL){

            return root;
        }
        if(val>root->key)
            root->right = deleteNode(root->right, val);
        else if(val<root->key)
            root->left = deleteNode(root->left, val);
        else
        {

            if(root->left == NULL and root->right == NULL)
            {
                free(root);
                if(sz==1)rootnode=NULL;
                sz--;
                return nullptr;
            }
            if(root->left == NULL)
            {
                Node* tmp = root->right;
                free(root);
                sz--;
                return tmp;
            }
            else if(root->right == NULL)
            {
                Node* tmp = root->left;
                free(root);
                sz--;
                return tmp;
            }
            ///having two child
            Node* tmp = minvalue(root->right);
            root->key = tmp->key;
            root->right = deleteNode(root->right, tmp->key);
        }
        //sz--;
        return root;
    }
    Node* deleteNode(int val)
    {
        //if(search(rootnode,val))sz--;
        return deleteNode(rootnode, val);
    }

    void Inorder(Node* root)
    {
        if (root == nullptr)
            return;

        Inorder(root->left);
        cout << root->key << " ";
        Inorder(root->right);
    }
    void Inorder()
    {
        cout<<"Inorder traversal: ";
        Inorder(rootnode);
        cout<<endl;
    }

    void Preorder(Node* root)
    {
        if (root == nullptr)
            return;

        cout << root->key << " ";
        Preorder(root->left);
        Preorder(root->right);
    }
    void Preorder()
    {
        cout<<"Preorder traversal: ";
        Preorder(rootnode);
        cout<<endl;
    }
    int getsize()
    {
        cout<<"The size is ";
        return sz;
    }
};

main()
{

    BST t;
    int choice,num;

    while(1)
    {
        cout<<"\n1: Insert an element"<<endl<<"2: Delete an element"<<endl<<"3: Search an element"<<endl<<
        "4: Print Preorder Traversal"<<endl<<"5: Print Inorder Traversal"<<endl<<"6: EXIT"<<endl;

        cout<<"Enter a choice: ";

        cin>>choice;

        if(choice==1)
        {
            cout<<"Enter the number you want to insert: ";
            cin>>num;
            t.Insert(num);
        }

        else if(choice==2)
        {
            cout<<"Enter the number you want to delete: ";
            cin>>num;
            t.deleteNode(num);
        }

        else if(choice==3)
        {
            cout<<"Enter the number you want to search: ";
            cin>>num;
            if(t.search(num)) cout<<"The number exists in the tree"<<endl;
            else cout<<"The number does not exist in the tree"<<endl;
        }

        else if(choice==4)
        {
            cout<<"The preorder traversal of the tree is:"<<endl;
            t.Preorder();
            cout<<endl;
        }

        else if(choice==5)
        {
            cout<<"The inorder traversal of the tree is:"<<endl;
            t.Inorder();
            cout<<endl;
        }

        else if(choice==6) break;
    }


//    cout<<t.search(15);
}
