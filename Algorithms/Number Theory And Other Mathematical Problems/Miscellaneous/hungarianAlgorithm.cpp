//Solving assignment problem using maximum weight bi-partite matching

#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>

using namespace std;

#define INF 1000000000
#define N 50 // Maximum number of jobs

vector<vector<int>> cost(N, vector<int>(N)); //Given cost matrix
int n, maxMatch; //Total jobs and Maximum Matching
vector<int> labelX(N); //Label of  X(agents)
vector<int> labelY(N); //label of Y(jobs)
vector<int> xy(N); //Matching of X in Y
vector<int> yx(N); //Mathcing of Y in X
vector<bool> T(N); 
vector<bool> S(N);
vector<int> slack(N); // slack[y] = labelX[yx[y]] + labelY[y] - weight(yx[y], y)
vector<int> slackX(N);
vector<int> pre(N); //For remembering alternating paths

// For vertices belongs to Y, label = 0
// For vertices belongs  to X, label = max weight edge connected to it
void init_labels()
{
   labelX = vector<int> (n, 0);
   labelY = vector<int> (n, 0);

   for(int x = 0; x < n; ++x)
     for(int y = 0; y < n; ++y)
       labelX[x] = max(labelX[x], cost[x][y]);

}

//Update label when there does not exist augmenting path in current 
//equality graph
// delta = min(labelX[x] + labelY[y] - weight(x, y)) 
//         x belongs to S, y does not belongs to T
// If vertices belong to S, label  = label - delta
// If vertices belong to T, label = lable + delta
// Do slack[y] = slack[y] - delta (If y does not belong to T)  
void update_labels()
{
    int x, y, delta = INF;

    //Calculate delta
    for(y = 0; y<n; ++y)
      if(!T[y])
        delta = min(delta, slack[y]);

    for(x = 0; x<n; ++x)
      if(S[x])
        labelX[x] -= delta;

    for(y = 0; y<n; ++y)
      if(T[x])
        labelY[y] += delta;

    //Update slack array
    for(y = 0; y < n; ++y)
        if(!T[y])
          slack[y] -= delta;
}

//Function to add new edges to the alternating tree
// x -> Current Vertex
// prevx -> vertex from X before x(current vertex) in the alternating path

//Add edges (prevx, xy[prevx]) AND (xy[prevx], x) to the alternating tree
void add_to_tree(int x, int prevx)
{
   S[x] = true; //Add x to S
   pre[x] = prevx; //We need this when augmenting
   
   //Since we have added vertices to S, update slack array
   for(int y = 0; y<n; ++y)
   {
       slack[y] = labelX[x] + labelY[y] - cost[x][y];
       slackX[y] = x;
   }
}

//main function
void augment()
{
   //Check for perfect matching
   if(maxMatch == n)
     return;    

   int x, y, root; // root = root of the alternating tree
   int q[N], rd = 0, wr = 0; // queue for BFS, read and write operation in queue

   S = vector<bool>(n, false);
   T = vector<bool>(n, false);
   pre = vector<int>(n, -1);

   //Find root of the alternating tree
   for(x = 0; x<n; ++x)
     if(xy[x] == -1)
     {
         q[wr++] = root = x;
         pre[x] = -2; // -2 = prev of root of the alternating tree
         S[x] = true;
         break;
     } 

   //Initialise slack array
   for(y = 0; y < n; ++y)
   {
       slack[y] = labelX[root] + labelY[y] - cost[root][y];
       slackX[y] = root;
   }   

   while(true)
   {
       //Build alternating tree with BFS
       while(rd < wr)
       {
           x = q[rd++]; //Current vertex from X 

           //Iterate through all edges in the equality graph
           for(y = 0; y<n; ++y)
             if(cost[x][y] == labelX[x] + labelY[y] && !T[y])
             {
                 if(yx[y] == -1) //Exposed vertex found -> Augment path exists
                   break;

                 //Else add y to T
                 T[y] = true;

                 //Add vertex yx[y] which is matched with y to the queue 
                 q[wr++] = yx[y];

                 //Add edges (x, y) AND (y, yx[y]) to the alternating tree
                 add_to_tree(yx[y], x); 
             }
            if(y < n)//To move out of inner while loop if augmenting path found
              break; 
       }
        
       if(y<n)
         break; 

       //If augmenting path not found, improve labeling
       update_labels();

       rd = wr = 0;

       //Add edges to the equality graph due to improved labeling
       //Add EDGE(slackX[y], y) to the alternating tree iff
       //    !T[y] && slack[y] == 0
       //Add another EDGE(y, yx[y])

       //If (y was exposed) --> Augment the matching

       for(y = 0; y<n; ++y)
         if(!T[y] && slack[y] == 0)
         {
             //If exposed vertex found, augmenting path exist
             if(yx[y] == -1)
             {
                 x = slackX[y];
                 break;
             }
             else
             {
                 T[y] = true; //Add y to T
                 if(!S[yx[y]])
                 {
                     //Add vertex yx[y] which is matched with y to the queue
                     q[wr++] = yx[y]; 

                     //Add edges (x, y) AND (y, yx[x]) to the alterating tree
                     add_to_tree(yx[y], slackX[y]);
                 }
             }      
         } 

        // Augemnting path exists
        if(y < n)
          break;    
   }

   //Found an augmenting path
   //Increment matching AND reverse the edges of the augemnting path
   if(y < n)
   {
       maxMatch++;

       //Inverse edges of the augmenting path
       for(int cx = x, cy = y, ty; cx != -2; cx = pre[cx], cy = ty)
       {
           ty = xy[cx];
           yx[cy] = cx;
           xy[cx] = cy;
       }

       //Recall function after matching has been incremented
       augment();
   }
}

int hunagrian()
{
    int result = 0;
    maxMatch = 0;

    xy = vector<int> (n, -1);
    yx = vector<int> (n, -1);

    init_labels();
    augment();

    //Forming answer
    for(int x = 0; x<n; ++x)
      result += cost[x][xy[x]];

    cout<<"Matchings : "<<endl;
    for(int x = 0; x<n; ++x)
     cout<<x<<" ---> "<<xy[x]<<endl;  

    return result;  
}

//Convert to max-weight matching problem from min-weight matching problem 
void convert()
{
    for(int x = 0; x<n; ++x)
      for(int y = 0; y<n; ++y)
        cost[x][y] = -cost[x][y];
}

int main()
{
    n = 3;

    vector<vector<int>> temp = {
                           {1, 4, 5},
                           {5, 7, 6},
                           {5, 8, 8}
                          };

    for(int x = 0; x < n; ++x)
        for(int y = 0; y < n; ++y)
            cost[x][y] = temp[x][y];

    //Since it is a minimum weight matching problem AND we are  
    //using max weight matching to solve the problem, we need to
    //Convert it to max weight matching problem using :-
    //   1.)  -cost[x][y]   OR
    //   2.)  W - cost[x][y]  , where W = max weight edge
    
    convert();

    cout<<"Minimum Cost Sum Matching : "<<abs(hunagrian());

    return 0;
}