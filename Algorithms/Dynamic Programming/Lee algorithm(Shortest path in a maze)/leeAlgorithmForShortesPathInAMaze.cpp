// Given a maze in the form of binary rectangular matrix, find length of 
// the shortest path in a maze from given source to given destination

// Lee Algorithm
// T = O(MN) , M & N : Total rows and columns in a maze

#include<iostream>
#include<queue>
#include<climits>
#include<string.h>

using namespace std;
#define M  10
#define N  10

//Data structure to store node in queue for BFS
// x & y are row and column indexes of the cell and dist = minimum 
// distance from the source 
struct Node
{
    int x, y, dist;
};

//All possible movements from a cell (N, E, S, W)
int row[4] = {-1, 0, 1, 0};
int col[4] = {0, 1, 0, -1};

bool isValidMove(int maze[M][N], bool visited[M][N], int row, int col)
{
    return (row < M) && (col < N) && (row >= 0) && (col >= 0) &&
           (!visited[row][col]) && (maze[row][col] == 1) ;
}

//BFS based function to find shortest path from source to destination
//BFS will visit all cells which have shortest path from source cell
// i.e 1 then 2 and so on until we reach destination vertex OR
// covered all vertices
void BFS(int maze[M][N], int sourceX, int sourceY,
                                 int destX, int destY)
{
    bool visited[M][N];
    memset(visited, false, sizeof(visited));

    int result = INT_MAX;

    queue<Node> Q;

    Q.push({sourceX, sourceY, 0});
    visited[sourceX][sourceY] = true;

    while(!Q.empty())
    {
        Node node = Q.front();
        Q.pop();

        //(x, y) : current cell AND dist : cell(x, y) shortest distance
        // from source
        int x = node.x, y = node.y, dist = node.dist;

        //If destination is found
        if(x == destX && y == destY)
        {
            result = dist;
            break;
        }    

        for(int i = 0 ; i < 4; ++i)
        {
            if(isValidMove(maze, visited, x+row[i], y+col[i]))
            {
                Q.push({x + row[i], y + col[i], dist + 1});
                visited[x + row[i]][y + col[i]] = true;
            }
        }    
    }

    if(result != INT_MAX)
       cout<<"\nShortest path from source to destination : "<<result;
    else
       cout<<"\nPath not possible from source to desination";  
}

int main()
{
    int mat[M][N] =
        {
            {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
            {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
            {0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        };

    // Find shortest path from source (0, 0) to
    // destination (7, 5)
    BFS(mat, 0, 0, 7, 5);
    return 0;
}