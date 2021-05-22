// Given a set of points find the smallest convex polygon that contains
// all points
//Convex polygon : (All inner angle does not exceeds 180-degree)
// T = O(N*LogN)

#include<iostream>
#include<stack>
#include<stdlib.h>

using namespace std;

//Data structure to represent points of line
struct Point
{
    int x, y; // x-coordinate and y-coordinate
};

//To store first point of convex hull
Point p0;

//Returns 0(collinear) , 1(clockwise), 2(anti-clockwise)
// slope1 =  (point2.y - point1.y)/(point2.x - point1.x)
// slope2 =  (point3.y - point2.y)/(point3.x - point2.x)
// ---> check the sign of the following equation :
//   (point2.y - point1.y)*(point3.x - point2.x)
//  -(point2.x - point1.x)*(point3.y - point2.y)
int orientation(Point point1, Point point2, Point point3)
{
    int value = (point2.y - point1.y) * (point3.x - point2.x)
              + (point2.x - point1.x) * (point3.y - point2.y);
    if (value == 0)
        return 0; //colllinear

    return (value > 0) ? 1 : 2; // clockwise and anti-clockwise
}

//To get point next to top in the stack
//It will not modify original stack
Point nextToTop(stack<Point> S)
{
  S.pop();
  return S.top();
}

//Find square of distance between two points
int squareDistance(Point point1, Point point2)
{
    return (point1.x - point2.x) * (point1.x - point2.x) 
         - (point1.y - point2.y) * (point1.y - point2.y);
}

// Compare function to be used in qsort to sort the points
// w.r.t. first point in output hull (increasing order of polar angle)
// We use orientation for sorting them A/T polar angle

int compare(const void *p1, const void *p2)
{
   Point *point1 = (Point*)p1;
   Point *point2 = (Point*)p2;

   //Find orientation
   int o = orientation(p0, *point1, *point2);

   //Orientation = collinear
   // Arrange the farthest point be present later than the other point
   // which are collinear with p0(first point OR bottom most point)
   if(o==0)
      return (squareDistance(p0, *point2) >= squareDistance(p0, *point1))?-1:1;

   return (o==2)?-1:1;   
}

//print convex hull
//Same points[] array is used to store the result also
void convexHull(Point points[], int size)
{
    //Find bottom most point
    int yMin = points[0].y;
    int min = 0; // to track point with min y-value
    int y;

    for(int i = 1; i < size; ++i)
    {
        y = points[i].y;
        if(y < yMin || ( y == yMin && points[i].x < points[min].x))
           yMin = points[i].y, min = i; 
    }

    //swap 1st point of points[] with point at 'min'
    swap(points[0], points[min]); 
    int sizeOfModifiedArray = 1; //To keep track of total output points

    p0 = points[0];

    //Now sort (size -1) points w.r.t. the first point
    //They are arranged in increasing order of polar angle w.r.t 1st point
    qsort(&points[1], size-1, sizeof(Point), compare) ;

    //Now if two or more points have same polar angle with p0
    // Remove all of them except the one that is farthest from p0
    //REMEMBER : We have put the farthest one later than all other points
    //           which have same polar angle
    for(int i = 1; i < size; ++i)
    {
        //Keep removing 'i' while angle  of 'i' and 'i+1' is same 
        // w.r.t. p0
        while(i < size-1 && orientation(p0, points[i], points[i+1]) == 0)
               ++i;
        points[sizeOfModifiedArray] = points[i];
        ++sizeOfModifiedArray; //update size of modified array     
    }

    // size of modified array < 3 (convex hull not possible)
    if(sizeOfModifiedArray < 3)
      return;

    //Push the 1st three points of points[] in stack
    stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    //Process remaining sizeOfModifiedArray-3 elements
    for(int i = 3; i < sizeOfModifiedArray; ++i)
    {
        // If orientation != counter-clockwise remove top element from
        // stack (ONLY INCLUDE IF IT MAKE LEFT TURN)
        while(orientation(nextToTop(hull), hull.top(), points[i]) != 2)
              hull.pop();

       hull.push(points[i]);  
    }

    //print points of convex hull
    while(!hull.empty())
    {
        Point p = hull.top();
        cout<<"("<<p.x<<", "<<p.y<<")"<<endl;
        hull.pop();
    }
}

int main()
{
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int size = sizeof(points)/sizeof(points[0]);
    convexHull(points, size);
    return 0;
}