// Given a set of points find the smallest convex polygon that contains 
// all points
//Convex polygon : (All inner angle does not exceeds 180-degree)
// T = O(n^2)

#include<iostream>
#include<vector>

using namespace std;

//Data structure to represent points of line
struct Point
{
    int x, y; // x-coordinate and y-coordinate
};

//Returns 0(collinear) , 1(clockwise), 2(anti-clockwise)
// slope1 =  (point2.y - point1.y)/(point2.x - point1.x)
// slope2 =  (point3.y - point2.y)/(point3.x - point2.x)
// ---> check the sign of the following equation :
//   (point2.y - point1.y)*(point3.x - point2.x)
//  -(point2.x - point1.x)*(point3.y - point2.y)
int orientation(Point point1, Point point2, Point point3)
{
    int value = (point2.y - point1.y) * (point3.x - point2.x) - (point2.x - point1.x) * (point3.y - point2.y);
    if(value == 0)
        return 0; //colllinear

    return (value > 0) ? 1 : 2; // clockwise and anti-clockwise
}

//print Convex Hull
void convexHull(Point points[], int size)
{
    //There must be at least 3 points
    if(size < 3)
      return;

    // For storing result
    vector<Point> hull;

    //Find leftmost point
    int leftMostPoint = 0; //initialised with point at 0-th index
    for(int i = 1; i < size; ++i)
    {
        if(points[i].x < points[leftMostPoint].x)
          leftMostPoint = i;
    }

    // Start from left-most point and keep moving counter-clockwise 
    // until we reach the start point again
    // It runs O(h) { h = no. of points in result }
    
    int currentPoint = leftMostPoint, nextPoint;

    do
    {
        //Add currentPoint to result
        hull.push_back(points[currentPoint]);

        // Search 'nextPoint' such that orientation of '
        // (currentPoint, i, nextPoint) = counter-clockwise 
        // for all points 'i'
        //The idea is to keep track of last-visited most counter-clockwise 
        // point in 'nextPoint'
        //If any point 'i' is more counter-clockwise than 'nextPoint'
        //then update 'nextPoint' to 'i'
        nextPoint = (currentPoint+1)%size;

        for(int i = 0; i < size; ++i)
        {
            if(orientation(points[currentPoint], points[i],
                           points[nextPoint]) == 2)
                nextPoint = i;           
        }
         
        //Now 'nextPoint' is most counter-clockwise w.r.t, 'currentPoint'
        //set the 'currentPoint' as 'nextPoint' 
        //So that it could be included in output (if its not leftMostPoint)
        currentPoint = nextPoint;
    } while(currentPoint != leftMostPoint);

    //print convex hull
    int hullSize = hull.size();
    cout<<"Points of Conevx Hull are : \n";
    for(int i = 0; i < hullSize; ++i)
      cout<<"("<<hull[i].x<<", "<<hull[i].y<<")\n";  
}

int main()
{
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};
    int size = sizeof(points)/sizeof(points[0]);
    convexHull(points, size);

    return 0;
}