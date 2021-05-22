/* Solving System of Linear Equations using Gaussian Elimination Method */

#include <iostream>
#include <math.h>

using namespace std;

#define N 3 //number of unknowns

//To swap two rows
void swap(double mat[N][N + 1], int row1, int row2)
{
    for (int i = 0; i < N + 1; ++i)
    {
        double temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

//Reduce matrix to R.E.F.(Row Echelon Form)
//mat : augmented matrix of system of linear equations
int forwardElimination(double mat[N][N + 1])
{
    for (int k = 0; k < N; ++k)
    {
        //Initialise maxValue and index for pivot (For same column)
        int maxIndex = k;
        double maxValue = mat[maxIndex][k];

        //find greater amplitude for pivot (if any)
        for (int i = k + 1; i < N; ++i)
            if (abs(mat[i][k]) > maxValue)
                maxValue = mat[i][k], maxIndex = i;

        //If principal diagonal element now is = 0 (MEANING : SINGULAR MATRIX)
        //Which will lead to division by zero
        if (!mat[maxIndex][k])
            return k;

        if (maxIndex != k)
            swap(mat, maxIndex, k); //Swap rows

        //Make all elements below that row 0 in the same column
        for (int i = k + 1; i < N; ++i)
        {
            double mult = (double)mat[i][k] / mat[k][k];

            //Upto index = k all elements must be 0 till col = k
            for (int j = k + 1; j <= N; ++j)
                mat[i][j] -= mult * mat[k][j];

            //Fill lower triangular matrix with zeroes explicitely
            //to avoid incorrect result due to less precision in division
            mat[i][k] = 0;
        }
    }
    return -1; //Matrix in non-singular
}

//Calculate values of unknowns using back substitution
void backSubstitution(double mat[N][N + 1])
{
    //Array to store solution
    double result[N];

    //Start calculating from last equation to first
    for (int i = N - 1; i >= 0; --i)
    {
        //start with the RHS of the equation
        result[i] = mat[i][N];

        //substitute already calcuated unknowns to know current unknown
        for (int j = i + 1; j < N; ++j)
        {
            result[i] -= mat[i][j] * result[j];
        }

        //divide the coefficient of current unknown from x[i] to get
        //current unknown
        result[i] = result[i] / mat[i][i];
    }

    printf("Solution of the system of linear equations :\n");
    for (int i = 0; i < N; ++i)
        printf("%lf\n", result[i]);
}

//To solve the system of linear equations
void gaussianElimination(double mat[N][N + 1])
{
    //Reduction to R.E.F.(Row Echelon Form)
    int singularFlag = forwardElimination(mat);

    //If matrix is singular
    if (singularFlag != -1)
    {
        printf("Singular Matrix\n");

        //If RHS of the equation corresponding to zero row = 0
        //Then there are infinitely many solutions
        if (mat[singularFlag][N])
            printf("Inconsistent System!\n");
        else
            printf("May have infinitely many solutions!");
    }
    backSubstitution(mat);
}

int main()
{
    double mat[N][N + 1]{{3.0, 2.0, -4.0, 3.0},
                         {2.0, 3.0, 3.0, 15.0},
                         {5.0, -3, 1.0, 14.0}};

    gaussianElimination(mat);
    return 0;
}