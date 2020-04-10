#include<bits/stdc++.h>
using namespace std;
int L[50][50];
void lcs_len(string a,string b,int m,int n)
{
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (a[i-1] == b[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
}
vector<string> LCS(string a, string b, int m, int n)
{
    if (m==0||n==0)
    {
        vector<string> v(1);
        return v;
    }
    if (a[m - 1]==b[n - 1])
    {
        vector<string> lcs = LCS(a, b, m - 1, n - 1);

        for (int i=0; i<lcs.size(); i++)
        {
            lcs[i].push_back(a[m - 1]);
        }
        return lcs;
    }

    if (L[m - 1][n] > L[m][n - 1])
        return LCS(a, b, m - 1, n);

    if (L[m][n - 1] > L[m - 1][n])
        return LCS(a, b, m, n - 1);

    vector<string> top = LCS(a, b, m - 1, n);
    vector<string> left = LCS(a, b, m, n - 1);

    top.insert(top.end(), left.begin(), left.end());
    return top;
}
set<string> LCS(string a, string b)
{
    int m = a.length(), n = b.length();
    lcs_len(a, b, m, n);
    vector<string> v = LCS(a, b, m, n);
    set<string> lcs(v.begin(), v.end());

    return lcs;
}

int main()
{
    string a,b;
    cin>>a>>b;

    set<string> lcs = LCS(a,b);
    for (string str : lcs)
        cout << str << endl;

    return 0;
}


