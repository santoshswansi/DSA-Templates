//Flood Fill (Seed Fill) is an algorithm that determines the area connected
//to a given node in a multi-dimensional array

//Flood Fill Algorithm Using DFS
// T = O(MN)   M = total rows , N = total columns

#include <iostream>

using namespace std;
#define M 10
#define N 10

//8 possible movements from a given cell
int row[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int col[8] = {0, 1, 1, 1, 0, -1, -1, -1};

bool isValidMove(char Mat[M][N], int row, int col, char target)
{
    return (row < M) && (row >= 0) && (col < N) && (col >= 0) &&
           Mat[row][col] == target;
}

//DFS based function to replace color of target to color of replacement
//We don't need visited[][] because we are updating the color of 'target'
// to 'replacement' color as we process it
void floodFillDFS(char Mat[M][N], int startX, int startY,
                  int targetColor, int replacementColor)
{
    Mat[startX][startY] = replacementColor;

    for(int i = 0 ; i < 8; ++i)
    {
        if(isValidMove(Mat, startX + row[i], startY + col[i],targetColor))
            floodFillDFS(Mat, startX + row[i], startY + col[i],
                         targetColor, replacementColor);           
    }
}

int main()
{ // matrix showing portion of the screen having different colors
    char mat[M][N] =
        {
            {'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
            {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X'},
            {'G', 'X', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X'},
            {'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X'},
            {'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X'},
            {'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X'},
            {'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X'},
            {'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X'},
            {'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X'},
            {'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

    // start node
    int x = 3, y = 9; // target color = "X"

    // replacement color
    char replacementColor = 'C';
    int targetColor = mat[x][y];

    // replace target color with replacement color
    floodFillDFS(mat, x, y, targetColor, replacementColor);

    // print the colors after replacement
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j];
        cout << "\n";
    }
    return 0;
}