// We can find n-th fibonacci  number using matrix exponentiation

// fib(n) = a*fib(n-1) + b*fib(n-2) + c*fib(n-3) , n>=3
// We can convert it to matrix form 
// | fib(n)  |    | a  b  c|     | fib(n-1) |
// | fib(n-1)|  = | 1  0  0|  *  | fib(n-2) |
// | fib(n-2)|    | 0  1  0|     | fib(n-3) |
//             --(n-2) times--  

// For fib series a = 1 , b = 1, c = 1 
// fib(0) = 0 , fib(1) = 1, fib(2) = 1

// T = O(log(n))

#include<iostream>

using namespace std;

//To multiply two  matrices  (3 X 3)
void multiply(int Mat1[3][3], int Mat2[3][3])
{
   int auxMat[3][3]; 
   for(int i = 0; i<3; ++i)
   {
       for(int j = 0; j<3; ++j)
       {
           auxMat[i][j] = 0;
           for(int k = 0; k<3; ++k)
             auxMat[i][j] += Mat1[i][k]*Mat2[k][j];
       }
   }

   //Store the result in Mat1
   for(int i = 0; i<3; ++i)
      for(int j = 0; j<3; ++j)
        Mat1[i][j] = auxMat[i][j];
}

// To multiply Mat n-2 times
int power(int Mat[3][3], int n)
{
    // First two elements of Mat at row = 0 { multiplied with 1 and 1 }
    if (n == 1)
        return Mat[0][0] + Mat[0][1];

    int temp[3][3] = {{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};

    power(Mat, n/2);    

    multiply(Mat, Mat);

    if(n%2 != 0) // n is odd
      multiply(Mat, temp);

    return Mat[0][0] + Mat[0][1];
}

int fib(int n)
{
    if(n==0)
     return 0;
    if(n==1 || n==2)
     return 1;

    int Mat[3][3] = {{1, 1, 0},{1, 0, 0},{0, 1, 0}} ;

    return power(Mat, n-2); 
}

int main()
{
    int n = 10; // 0 1 1 2 3 5 8 13 21 34 55 89 144 (0-12 = 13)
    cout<<"fib("<<n<<") = "<<fib(n)<<endl;
    return 0;
}