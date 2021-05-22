// LCA (Lowest Common Ancestor) using binary Lifting
// T = (n * log(n))

#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

//Pre-processing to calculate values of memo[][]
void dfs(int u, int p, vector<vector<int>> &memo, vector<int> &level,
                int log, vector<int> *g)
{
   //Store parent of 'u' as 'p' 
   memo[u][0] = p;

   for(int i = 1; i <= log; ++i)
    memo[u][i] = memo[memo[u][i-1]][i-1];

   //Visit all childs of 'u'
   for(int v : g[u])
   {
       if(v != p)
       {
           level[v] = level[u] + 1;
           dfs(v, u, memo, level, log, g);
       }
   } 
}    

//To calculate LCA of nodes 'u' & 'v'
int lca(int u, int v, int log, vector<int> level, vector<vector<int>> memo)
{
    //Make sure that u is the farthest node
    if(level[u] < level[v])
      swap(u, v);

    //Find the ancestor of 'u' such that ancestor of it and 'v' are
    //at the same level
    for(int i = log; i>=0 ; --i)
      if(level[u] - pow(2,i) >= level[v])
        u = memo[u][i];

    //If 'v' is ancestor of node 'u' , LCA = 'v'
    if(u == v)
     return u;

    // Find the node closest to the root which is not the common ancestor 
    // of 'u' and 'v' i.e. a node 'x' such that  'x' is not a common
    // ancestor of 'u'  and 'v' but memo[x][0] is
    //(This is to make sure that common ancestor is farthest from root
    // not close to the root)

    for(int i = log; i>=0; i--)
    {
        if(memo[u][i] != memo[v][i])
        {
            u = memo[u][i];
            v = memo[v][i];
        }
    }       
    return memo[u][0];
}

int main()
{
    //number of nodes
    const int n = 9;

    // array of vector to store adjacent nodes
    // 1 based indexing for nodes
    vector<int> g[n+1];
    int log = (int)ceil(log2(n));
    vector<vector<int>> memo(n+1, vector<int>(log + 1,-1));

    // Stores the level of each node
    vector<int> level(n+1);

    // Add edges
    g[1].push_back(2);          //                 1_____
    g[2].push_back(1);          //                / |    |
    g[1].push_back(3);          //               /  |    |
    g[3].push_back(1);          //              2   3_   4
    g[1].push_back(4);          //             /   /| |   |
    g[4].push_back(1);          //            /   / | |   |
    g[2].push_back(5);          //           5   6  7 8   9
    g[5].push_back(2);          //
    g[3].push_back(6);         
    g[6].push_back(3);         
    g[3].push_back(7);         
    g[7].push_back(3);         
    g[3].push_back(8);         
    g[8].push_back(3);
    g[4].push_back(9);
    g[9].push_back(4);
    dfs(1, 1, memo, level, log, g);
    cout << "The LCA of 6 and 9 is " << lca(6, 9, log, level, memo) << endl;
    cout << "The LCA of 5 and 9 is " << lca(5, 9, log, level, memo) << endl;
    cout << "The LCA of 6 and 8 is " << lca(6, 8, log, level, memo) << endl;
    cout << "The LCA of 6 and 1 is " << lca(6, 1, log, level, memo) << endl;

    return 0;
}