// General equation of fib series : f(n) = f(n-1) + f(n-2)
// Writing above equation in matrix form :
//               | f(n)   |     | 1   1 |       | f(n-1) |     
//               | f(n-1) |  =  | 1   0 |   X   | f(n-2) |     
//                 2 X 1          r X c            2 X 1
//                               {2 X 2} {HAVING POWER : (n-1)}

//Mat[0][0] will be the result
//T = (logn)
//Extra space : O(log(n)) {Considering function call stack size} 
//              otherwise O(1)    

#include<iostream>

using namespace std;

//To multiply two matrices 
//Also modify the Mat with their product
void multiply(int Mat[2][2], int cloneMat[2][2])
{
    int r0c0 = Mat[0][0]*cloneMat[0][0] + Mat[0][1]*cloneMat[1][0];
    int r0c1 = Mat[0][0]*cloneMat[0][1] + Mat[0][1]*cloneMat[1][1];
    int r1c0 = Mat[1][0]*cloneMat[0][0] + Mat[1][1]*cloneMat[1][0];
    int r1c1 = Mat[1][0]*cloneMat[0][1] + Mat[1][1]*cloneMat[1][1];

    Mat[0][0] = r0c0;
    Mat[0][1] = r0c1;
    Mat[1][0] = r1c0;
    Mat[1][1] = r1c1;
}

//To get Mat[2][2] to the power of n
void power(int Mat[2][2], int n)
{
  if(n == 0 || n == 1)
   return;

  int cloneMat[2][2] = {{1,1}, {1,0}}; 

  power(Mat, n/2);
  multiply(Mat, Mat);

  if(n%2 != 0)  // n is odd
   multiply(Mat, cloneMat);
}

int fib(int n)
{
    int Mat[2][2] = {{1, 1},{1, 0}};
    if(n == 0)
      return 0;

    power(Mat, n-1);

    return Mat[0][0]; 
}

int main()
{
    int n = 10;  // 1 1 2 3 5 8 13 21 34 55 
    cout<<"fib("<<n<<") = "<< fib(n) <<endl;
    return 0;
} 