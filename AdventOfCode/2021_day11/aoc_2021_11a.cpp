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
#include "../Libraries/aocFile.h"

using namespace std;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define MAX 1000U

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void doStep(vector<vector<uint8_t>> *pGrid,
                   vector<vector<uint8_t>> exciteIn,
                   vector<vector<uint8_t>> *pFlash,
                   uint64_t &flashCount);
static void incAdj(vector<vector<uint8_t>> *pGrid, uint8_t x, uint8_t y);

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
    getGrid(fileInput, &vecGrid);
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
        doStep(&vecGrid, excGrid, &flashGrid, stepCount);
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
static void doStep(vector<vector<uint8_t>> *pGrid,
                   vector<vector<uint8_t>> exciteIn,
                   vector<vector<uint8_t>> *pFlash,
                   uint64_t &flashCount)
{
    // excite grid
    vector<vector<uint8_t>> exciteOut(exciteIn.size(),
                                      vector<uint8_t>(exciteIn[0].size(), 0));
    for (uint16_t i = 0; i < (*pGrid).size(); i++)
    {
        for (uint16_t j = 0; j < (*pGrid)[i].size(); j++)
        {
            (*pGrid)[i][j] += exciteIn[i][j];
            if ((*pGrid)[i][j] > 9)
            {
                if ((*pFlash)[i][j] == 0)
                {
                    (*pFlash)[i][j]++;
                    flashCount++;
                    incAdj(&exciteOut, i, j);
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
            doStep(pGrid, exciteOut, pFlash, flashCount);
            return;
        }
    }

    // reset flash and grid
    for (auto &vec : (*pFlash))
    {
        fill(vec.begin(), vec.end(), 0);
    }
    for (auto &vec : (*pGrid))
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

static void incAdj(vector<vector<uint8_t>> *pGrid, uint8_t x, uint8_t y)
{
    uint16_t xMax = (*pGrid).size();
    uint16_t yMax = (*pGrid)[x].size();
    for (int8_t i = -1; i <= 1; i++)
    {
        if (x + i >= 0 && (int16_t)x + i < xMax)
        {
            for (int8_t j = -1; j <= 1; j++)
            {
                if (y + j >= 0 && (int16_t)y + j < yMax)
                {
                    (*pGrid)[x + i][y + j]++;
                }
            }
        }
    }
}