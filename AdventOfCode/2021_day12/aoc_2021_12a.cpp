/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: YYYY-MM-DD
 */

/******************************************************************************/
/* INCLUDES & NAMESPACES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "../Libraries/aocLib_v02.h"

using namespace std;
using namespace aocLib_v02;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define VAR 0

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void FindCaves(string line, vector<string> &caves);

/******************************************************************************/
/* MAIN */
/******************************************************************************/
int main()
{
    // read file
    std::ios::sync_with_stdio(false);
    ifstream fileInput;
    if (loadFile(fileInput))
    {
        fileInput.close();
        return 0;
    }

    // get string pairs
    vector<string> vecLines;
    getStrVec(fileInput, vecLines);

    // build vector of caves
    vector<string> vecCaves;
    for (auto &str : vecLines)
    {
        FindCaves(str, vecCaves);
    }

    /*
    Plan
    - save all stations in a vector
    - save all adjacents in another vector
    - save all "small caves" in a vector
    - from start, do "get all adjacent paths"
        - recursive that returns true when all paths explored 
        - increases count when reaches end
        - also removes small cave indices whenever one is left
    */

    // print and exit
    cout << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static void FindCaves(string line, vector<string> &caves)
{
        string first, last;
        vector<string>::iterator it;

        first = line.substr(0, line.find('-'));
        it = find(caves.begin(), caves.end(), first);
        if (it == caves.end())
        {
            caves.push_back(first);
        }

        last = line.substr(line.find('-') + 1, line.size());
        it = find(caves.begin(), caves.end(), last);
        if (it == caves.end())
        {
            caves.push_back(last);
        }
}