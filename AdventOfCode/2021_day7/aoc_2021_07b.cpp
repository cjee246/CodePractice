/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-13
 */

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "../Libraries/aocFile.h"

using namespace std;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define DAYS 80u

/******************************************************************************/
/* ADDITIONAL FUNCTIONS */
/******************************************************************************/
static void func()
{
}

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

    // get values into vector
    vector<uint16_t> pos;
    string str, substr;
    fileInput >> str;
    stringstream strStream(str);
    while (strStream.good())
    {
        getline(strStream, substr, ',');
        pos.push_back(stoi(substr));
    }

    // vector of counts
    vector<uint64_t> counts;
    uint64_t max;
    for (uint16_t i = 0; i < pos.size(); i++)
    {
        if (pos[i] >= counts.size())
        {
            max = pos[i];
            counts.resize(pos[i] + 1);
        }
        counts[pos[i]]++;
    }
    int check = accumulate(counts.begin(), counts.end(), 0);
    
    // set up scaling vector
    vector<uint64_t> scale(counts.size());
    for (uint64_t i = 1; i < scale.size(); i++)
    {
        scale[i] = scale[i-1] + i;
    }

    // iterate starting positions, look for change
    uint64_t minThis = 0, minLast = 0;
    uint16_t startPos = 0;
    bool minReached = false;
    while (!minReached)
    {
        minThis = 0;
        for (uint16_t i = 0; i < counts.size(); i++)
        {
            minThis += counts[i] * scale[abs(startPos - i)];
        }
        if (minThis > minLast && startPos > 0)
        {
            break;
        }
        else
        {
            minLast = minThis;
            startPos++;
        }
    }

    // print and exit
    cout << minLast << '\n';
    fileInput.close();
    return 0;
}
