// Given 2 - assembly lines having same number of stations

// [ An item has to move from one end to other with minimum cost ]

// An item can move from one station to next station with no cost if they
// are on the same line, moving to other line have some cost
// based on station and assembly line

// Entering and exiting the assembly line also has some cost
//Staying at a station also has some cost

#include <iostream>
#include <algorithm>

using namespace std;
#define NUM_LINE 2
#define NUM_STATION 4

//changeOfLinecost[i][j] ---> Stores cost to transfer item from line - 'i'
//                            to the other line to station - 'j'
int carAssembly(int costAtStation[NUM_LINE][NUM_STATION],
                int changeOfLineCost[NUM_LINE][NUM_STATION],
                int entranceCost[NUM_LINE],
                int exitCost[NUM_LINE])
{
    //Finally first and last variables will store min cost to leave 
    // last station of each line.
    //Time taken to leave first station of line-1
    int first = entranceCost[0] + costAtStation[0][0];

    //Time taken to leave first station of line-2
    int second = entranceCost[1] + costAtStation[1][0];

    int newFirst, newSecond; // To store new cost of 'first' and 'second'

    for (int i = 1; i < NUM_STATION; ++i)
    {
        //station - i can be reached from EITHER first line or second line

        newFirst = min(first + costAtStation[0][i],
                    second + changeOfLineCost[1][i] + costAtStation[0][i]);

        newSecond = min(second + costAtStation[1][i],
                    first + changeOfLineCost[0][i] + costAtStation[1][i]);

        first = newFirst;
        second = newSecond;            
    }

    return min(first + exitCost[0],
               second + exitCost[1]);
}

int main()
{
    int costAtStation[NUM_LINE][NUM_STATION] = {
        {4, 5, 3, 2},
        {2, 10, 1, 4}};

    int changeOfLineCost[NUM_LINE][NUM_STATION] = {
        {0, 7, 4, 5},
        {0, 9, 2, 8}};
    int entranceCost[NUM_LINE] = {10, 12};
    int exitCost[NUM_LINE] = {18, 7};

    cout << "\nCost of Min Cost Path : " << carAssembly(costAtStation, changeOfLineCost, entranceCost, exitCost);

    return 0;
}