// Given two lines find if they intersect or not 
// (USE ORIENTATION OF 3-ORDERED TRIPLETS)

#include<iostream>
#include<algorithm>

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
    int value = (point2.y - point1.y)*(point3.x - point2.x)
               -(point2.x - point1.x)*(point3.y - point2.y);
    if(value == 0)
      return 0; //colllinear

    return (value>0)?1:2; // clockwise and anti-clockwise  
}

// Given 3 collinear points point1, point2, point3 
// It checks if point point2 lies on line segment formed by
// point1 and point3
bool onSegment(Point point1, Point point2, Point point3)
{
    if 
    (
        point2.x <= max(point1.x, point3.x) &&
        point2.x >= min(point1.x, point3.x) &&
        point2.y <= max(point1.y, point3.y) &&
        point2.y >= min(point1.y, point3.y)
    )
      return true;

    return false;  
}

//main method to check whether two lines intersect or not
//First Line Segment (Formed by point1 and point2)
//Second Line Segment (Formed by point3 and point4)
bool doIntersect(Point point1, Point point2, Point point3, Point point4)
{
  int o1 = orientation(point1, point2, point3);
  int o2 = orientation(point1, point2, point4);
  int o3 = orientation(point3, point4, point1);
  int o4 = orientation(point3, point4, point2);

  //General Case
  if(o1 != o2 && o3 != o4)
   return true;

  //Special cases (collinear)
  //point1, point2 & point3 are collinear & point3 lies in point1 & point2 
  if(o1 == 0 && onSegment(point1, point3, point2))
   return true;

  //point1, point2 & point4 are collinear & point4 lies in point1 & point2
  if(o2 == 0 && onSegment(point1, point4, point2))
      return true; 
  
  //point3, point4 & point1 are collinear & point1 lies in point3 & point4
  if(o3 == 0 && onSegment(point3, point1, point4))
      return true; 
      
  //point3, point4 & point2 are collinear & point2 lies in point3 & point4
  if(o4 == 0 && onSegment(point3, point1, point4))
      return true;

  return false;    
}

int main()
{
    Point p1 = {1, 1}, q1 = {10, 1};
    Point p2 = {1, 2}, q2 = {10, 2};

    doIntersect(p1, q1, p2, q2) ? cout<<"Yes\n" : cout<<"No\n";

    p1 = {10, 0}, q1 = {0, 10};
    p2 = {0, 0}, q2 = {10, 10};
    doIntersect(p1, q1, p2, q2) ? cout<<"Yes\n" : cout<<"No\n";

    p1 = {-5, -5}, q1 = {0, 0};
    p2 = {1, 1}, q2 = {10, 10};
    doIntersect(p1, q1, p2, q2) ? cout<<"Yes\n" : cout<<"No\n";
    return 0;
}