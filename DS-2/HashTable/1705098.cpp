/**Bismillahir Rahmanir Rahimm**/

//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#include<bits/stdc++.h>
#include <unistd.h>
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


class HashNode
{
public:
    string key;
    int val;
    HashNode *next;

    HashNode()
    {
        key = "";
        val = 0;
    }

    HashNode(string _key, int _value)
    {
        val = _value;
        key = _key;
        next = NULL;
    }

};

class chain_hash
{
public:
    HashNode** data;
    int maxsize,size;
    int collision,probe;
    chain_hash(int n)
    {
        maxsize = n;
        size = 0;
        collision = 0;
        probe = 0;
        data = new HashNode*[maxsize];
        ffr(i, 0, maxsize)
        {
            data[i] = nullptr;
        }
    }
    int hash1(string key)
    {
        int hashVal = 0;
        int M = maxsize;
        for(int i = 0; i<key.length();  i++)
        {
            hashVal = 37*hashVal+key[i];
        }
        hashVal %= M;

        if(hashVal<0)
            hashVal += M;

        return hashVal;
    }
    int hash2(string s)
    {
        int p = 31;
        int m = maxsize;
        int h = 0;
        int p_pow = 1;
        for (char c : s)
        {
            h = (h ^ ((c - 'a' + 1) + (h<<5) + (h>>2) ))%m;
            //p_pow = (p_pow * p) % m;
        }
        return h%m ;
    }
    int getsize()
    {
        return size;
    }
    void Insert(string key , int hf)
    {
        int pos ;
        if(hf==1)pos = hash1(key);
        else pos = hash2(key);

        if(pos<0)pos += maxsize;
        int value = size + 1;
        HashNode *temp = new HashNode(key, value);
        if (data[pos] == nullptr)
        {
            data[pos] = temp;
            size++;
        }
        else
        {
            temp->next = data[pos];
            data[pos] = temp;
            size++;
            collision++;
        }
    }
    int get_collision()
    {
        return collision;
    }
    int Search(string key, int hf)
    {
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        HashNode* hn = data[pos];

        while(hn != NULL){

            if(hn->key == key){
                return hn->val;
            }
            hn = hn->next;
            probe++;
        }

        return -1;///key not found
    }
    int getprobe()
    {
        return probe;
    }
    void Delete(string key , int hf)
    {
        if(Search(key , hf)== -1){
            cout<<"Key doesn't exist!"<<endl;
            return;
        }
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        HashNode* tmp = data[pos];
        if(tmp->key == key){
            data[pos] = tmp->next;
            delete tmp;
            cout<<key<<" deleted"<<endl;
            size--;
            return;
        }
        HashNode* prev;
        while(tmp != NULL)
        {
            if(tmp->key == key){
                prev->next = tmp->next;
                delete tmp;
                cout<<key<<" deleted"<<endl;
                size--;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }

    void print()
    {
        //cout<<"          key    value"<<endl;
        ffr(i , 0 , maxsize)
        {
            HashNode* hn = data[i];
            bool paisi = false;
            if(hn != NULL)cout<<"Pos "<<i<<": ";
            while(hn != NULL){
                paisi = true;
                cout<<"("<<hn->key<<" , "<<hn->val<<") ";
                hn = hn->next;
            }
            if(paisi){
                cout<<endl;
            }
        }
    }
};
class double_hash{
public:
    HashNode* ara;
    int maxsize , size;
    int collision,probe;
    bool filledup;

    double_hash(int n){
       maxsize = n;
       size = 0;
       collision = 0;
       probe = 0;
       filledup = false;
       ara = new HashNode[maxsize];
    }
    int hash1(string key)
    {
        int hashVal = 0;
        int M = maxsize;
        for(int i = 0; i<key.length();  i++)
        {
            hashVal = 37*hashVal+key[i];
        }
        hashVal %= M;

        if(hashVal<0)
            hashVal += M;

        return hashVal;
    }
    int hash2(string s)
    {
        int p = 31;
        int m = maxsize;
        int h = 11;
        int p_pow = 1;
        for (char c : s)
        {
            h = (h ^ ((c - 'a' + 1) + (h<<5) + (h>>2) ))%m;
        }
        return h%m ;
    }
    int aux_hash(string key)
    {
        int hashVal = 1;
        int M = maxsize;
        for(int i = 0; i<key.length();  i++)
        {
            hashVal = ((hashVal*37) + ((int)key[i]))%M;
        }
        hashVal =(hashVal*10 + 1)% maxsize;
        if(hashVal<0) hashVal += maxsize;
        return hashVal;
    }
    int getsize()
    {
        return size;
    }
    int get_collision()
    {
        return collision;
    }
    void Insert(string key , int hf)
    {
        if(filledup){
            return;
        }

        bool hoise=false;
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        int pos2 = aux_hash(key);
        ffr(i , 0 ,maxsize)
        {
            pos = pos + i*pos2;
            pos %= maxsize;
            if(pos<0)pos += maxsize;
            if(ara[pos].key == "" and ara[pos].val == 0){
                HashNode tmp(key , size+1);
                ara[pos] = tmp;
                size++;
                hoise = true;

                break;
            }
            collision++;

        }
        if(!hoise)filledup = true;

    }
    int Search(string key , int hf)
    {
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        int pos2 = aux_hash(key);//DBG(pos2);
        ffr(i , 0 ,maxsize)
        {
            pos = pos + i*pos2;
            pos %= maxsize;
            if(ara[pos].key == key ){
                return ara[pos].val;
                break;
            }
            probe++;
        }

        return -1;
    }
    int getprobe()
    {
        return probe;
    }
    void Delete(string key , int hf)
    {
        if(Search(key,hf) ==-1 ){
            cout<<key<<" doesn't exist!"<<endl;
            return;
        }
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        int pos2 = aux_hash(key);
        int i = 1;
        while(ara[pos].key != "" and ara[pos].val != 0){
            if(ara[pos].key == key){
                HashNode hn;
                ara[pos] = hn;
                size--;
                return;
            }
            pos = pos + i*pos2;
            pos %= maxsize;
            i++;
        }
    }
    void print()
    {
        ffr(i , 0 , maxsize){
            if(ara[i].key != "" and ara[i].val != 0){
                cout<<"Pos "<<i<<": ("<<ara[i].key<<" , "<<ara[i].val<<")"<<endl;
            }
        }
    }
};

class custom_probing_hash{
public:
    HashNode* ara;
    int maxsize , size;
    int collision,probe;
    bool filledup;

    custom_probing_hash(int n)
    {
       maxsize = n;
       size = 0;
       collision = 0;
       probe = 0;
       filledup = false;
       ara = new HashNode[maxsize];
    }
    int hash1(string key)
    {
        int hashVal = 0;
        int M = maxsize;
        for(int i = 0; i<key.length();  i++)
        {
            hashVal = 37*hashVal+key[i];
        }
        hashVal %= M;

        if(hashVal<0)
            hashVal += M;

        return hashVal;
    }
    int hash2(string s)
    {
        int p = 31;
        int m = maxsize;
        int h = 0;
        int p_pow = 1;
        for (char c : s)
        {
            h = (h ^ ((c - 'a' + 1) + (h<<5) + (h>>2) ))%m;
            //p_pow = (p_pow * p) % m;
        }
        return h%m ;
    }
    int aux_hash(string key)
    {
        int hashVal = 1;
        int M = maxsize;
        for(int i = 0; i<key.length();  i++)
        {
            hashVal = ((hashVal*37) + ((int)key[i]))%M;
        }
        hashVal =(hashVal*10 + 1)% maxsize;
        if(hashVal<0) hashVal += maxsize;
        return hashVal;
    }
    int get_collision()
    {
        return collision;
    }
    int getsize()
    {
        return size;
    }
    void Insert(string key , int hf)
    {
        if(filledup){
            return;
        }

        bool hoise=false;
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        int pos2 = aux_hash(key);
        ffr(i , 0 ,maxsize)
        {
            pos = pos + 7*i*pos2 + 11*i*i;
            pos %= maxsize;
            if(ara[pos].key == "" and ara[pos].val == 0){
                HashNode tmp(key , size+1);
                ara[pos] = tmp;
                size++;
                hoise = true;
                break;
            }
            collision++;
        }
        if(!hoise)filledup = true;

    }
    int Search(string key , int hf)
    {
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        int pos2 = aux_hash(key);//DBG(pos2);
        ffr(i , 0 ,maxsize)
        {
            pos = pos + 7*i*pos2 + 11*i*i;
            pos %= maxsize;
            if(ara[pos].key == key ){
                return ara[pos].val;
                break;
            }
            probe++;
        }

        return -1;
    }
    int getprobe()
    {
        return probe;
    }
    void Delete(string key , int hf)
    {
        if(Search(key,hf) ==-1 ){
            cout<<key<<" doesn't exist!"<<endl;
            return;
        }
        int pos;
        if(hf==1) pos = hash1(key);
        else pos = hash2(key);

        int pos2 = aux_hash(key);
        int i = 1;
        while(ara[pos].key != "" and ara[pos].val != 0){
            if(ara[pos].key == key){
                HashNode hn;
                ara[pos] = hn;
                size--;
                return;
            }
            pos = pos + 7*i*pos2 + 11*i*i;
            pos %= maxsize;
            i++;
        }
    }
    void print()
    {
        ffr(i , 0 , maxsize){
            if(ara[i].key != "" and ara[i].val != 0){
                cout<<"Pos "<<i<<": ("<<ara[i].key<<" , "<<ara[i].val<<")"<<endl;
            }
        }
    }

};
string gen_random(int len=7){

    string tmp_s="";
    ffr(i , 0 , len)
    {
        char ch = 'a' + rand()%26;
        char ch2 = 'A' + rand()%26;
        if(rand()%2)tmp_s += ch;
        else tmp_s += ch2;
    }
    return tmp_s;
}
main()
{
    int heap_size;
    cout<<"Enter HashTable Size : "<<endl;
    cin>>heap_size;

    set<string> s;
    ffr(i , 0 , 10000)
    {
        string str = gen_random();
        s.insert(str);
    }
    //cout<<s.size()<<endl;
    chain_hash c2(heap_size);
    chain_hash c1(heap_size);
    double_hash d1(heap_size);
    double_hash d2(heap_size);
    custom_probing_hash cp1(heap_size);
    custom_probing_hash cp2(heap_size);
    vector<string> v;
    set<string >::iterator itr;
    for (itr = s.begin(); itr != s.end(); ++itr)
    {
        c2.Insert(*itr , 2);
        c1.Insert(*itr , 1);
        d1.Insert(*itr, 1);
        d2.Insert(*itr , 2);
        cp1.Insert(*itr , 1);
        cp2.Insert(*itr , 2);
    }

    int ch_coll_h2 = c2.get_collision();
    int ch_coll_h1 = c1.get_collision();

    int db_coll_h1 = d1.get_collision();
    int db_coll_h2 = d2.get_collision();

    int cp_coll_h1 = cp1.get_collision();
    int cp_coll_h2 = cp1.get_collision();

    cout<<"No Of Collisions\n\n                Hash1    Hash2\n";
    cout<<"Chaining Method  "<<ch_coll_h1<<"  "<<ch_coll_h2<<endl;
    cout<<"Double Hashing  "<<db_coll_h1<<"  "<<db_coll_h2<<endl;
    cout<<"Custom Probing  "<<cp_coll_h1<<"  "<<cp_coll_h2<<endl<<endl;

    ///counting avg probes
    int idx;
    string str;
    ffr(i , 0 , 1000)
    {
        idx = rand()%(s.size());
        set<string>::iterator it = s.begin();
        advance(it, idx);
        str = *it;
        c1.Search(str , 1);
        c2.Search(str , 2);
        d1.Search(str , 1);

        d2.Search(str , 2);
        cp1.Search(str , 1);
        cp2.Search(str , 2);
    }
    db ch_avg_probe_h1 = 1.0*c1.getprobe()/c1.getsize();
    db ch_avg_probe_h2 = 1.0*c2.getprobe()/c2.getsize();

    db db_avg_probe_h1 = 1.0*d1.getprobe()/d1.getsize();
    db db_avg_probe_h2 = 1.0*d2.getprobe()/d2.getsize();

    db cp_avg_probe_h1 = 1.0*cp1.getprobe()/cp1.getsize();
    db cp_avg_probe_h2 = 1.0*cp2.getprobe()/cp2.getsize();
    cout<<"Avg Probe\n\n                Hash1      Hash2\n";
    cout<<"Chaining Method  "<<ch_avg_probe_h1<<"  "<<ch_avg_probe_h2<<endl;
    cout<<"Double Hashing  "<<db_avg_probe_h1<<"  "<<db_avg_probe_h2<<endl;
    cout<<"Custom Probing  "<<cp_avg_probe_h1<<"  "<<cp_avg_probe_h2<<endl;

}
