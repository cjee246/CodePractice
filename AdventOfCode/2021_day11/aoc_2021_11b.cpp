/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2021-03-20
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
#define MAX 1000U

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void doStep(vector<vector<uint8_t>> &rGrid,
                   vector<vector<uint8_t>> exciteIn,
                   vector<vector<uint8_t>> &rFlash,
                   uint64_t &rFlashCount);
static void incAdj(vector<vector<uint8_t>> &rGrid, uint8_t x, uint8_t y);

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

    // initialize grids
    vector<vector<uint8_t>> vecGrid;
    getGrid(fileInput, vecGrid);
    vector<vector<uint8_t>> excGrid(vecGrid.size(), vector<uint8_t>(vecGrid[0].size(), 0));
    vector<vector<uint8_t>> flashGrid = excGrid;

    // do stuff
    bool update = true;
    uint64_t totalCount = 0, sync = 0;
    for (uint16_t i = 0; i < MAX; i++)
    {
        uint64_t stepCount = 0;
        for (auto &vec : excGrid)
        {
            fill(vec.begin(), vec.end(), 1);
        }
        doStep(vecGrid, excGrid, flashGrid, stepCount);
        totalCount += stepCount;
        if (stepCount == flashGrid.size() * flashGrid[0].size())
        {
            sync = i + 1;
            break;
        }
    }

    // print and exit
    cout << sync << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static void doStep(vector<vector<uint8_t>> &rGrid,
                   vector<vector<uint8_t>> exciteIn,
                   vector<vector<uint8_t>> &rFlash,
                   uint64_t &rFlashCount)
{
    // excite grid
    vector<vector<uint8_t>> exciteOut(exciteIn.size(),
                                      vector<uint8_t>(exciteIn[0].size(), 0));
    for (uint16_t i = 0; i < rGrid.size(); i++)
    {
        for (uint16_t j = 0; j < rGrid[i].size(); j++)
        {
            rGrid[i][j] += exciteIn[i][j];
            if (rGrid[i][j] > 9)
            {
                if (rFlash[i][j] == 0)
                {
                    rFlash[i][j]++;
                    rFlashCount++;
                    incAdj(exciteOut, i, j);
                }
            }
        }
    }

    // do excitations
    for (auto &vec : (exciteOut))
    {
        if (!all_of(vec.begin(), vec.end(),
                    [](uint64_t n)
                    { return n == 0; }))
        {
            doStep(rGrid, exciteOut, rFlash, rFlashCount);
            break;
        }
    }

    // reset flash and grid
    for (auto &vec : rFlash)
    {
        fill(vec.begin(), vec.end(), 0);
    }
    for (auto &vec : rGrid)
    {
        for (auto &elem : vec)
        {
            if (elem > 9)
            {
                elem = 0;
            }
        }
    }
}

static void incAdj(vector<vector<uint8_t>> &rGrid, uint8_t x, uint8_t y)
{
    uint16_t xMax = rGrid.size();
    uint16_t yMax = rGrid[x].size();
    for (int8_t i = -1; i <= 1; i++)
    {
        if (x + i >= 0 && (int16_t)x + i < xMax)
        {
            for (int8_t j = -1; j <= 1; j++)
            {
                if (y + j >= 0 && (int16_t)y + j < yMax)
                {
                    rGrid[x + i][y + j]++;
                }
            }
        }
    }
}