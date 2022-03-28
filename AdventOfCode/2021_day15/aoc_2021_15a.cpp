/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-30
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
#include "../Libraries/aocLib_v03.h"

using namespace std;
using namespace aocLib_v03;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define VAR 0

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static vector<uint16_t> CheckNeighbors(vector<vector<uint8_t>> &rVecGrid,
                                       vector<vector<uint8_t>> &rVecVisited,
                                       vector<vector<uint16_t>> &rVecDist,
                                       vector<uint16_t> nodeCoords);

/******************************************************************************/
/* MAIN */
/******************************************************************************/
int main()
{
    // read file
    std::ios::sync_with_stdio(false);
    ifstream fileInput;
    if (LoadFile(fileInput))
    {
        fileInput.close();
        return 0;
    }
    vector<vector<uint8_t>> vecGrid;
    GetGrid(fileInput, vecGrid);

    // setup tracking vectors
    vector<vector<uint8_t>> vecVisited(vecGrid.size(), vector<uint8_t>(vecGrid[0].size(), 0));
    vector<vector<uint16_t>> vecDist(vecGrid.size(), vector<uint16_t>(vecGrid[0].size(), 60000));
    vector<vector<uint16_t>> vecPath;

    vector<uint16_t> newCoord;
    for (uint32_t i = 0; i < vecPath.size(); i++)
    {
        newCoord = CheckNeighbors(vecGrid, vecVisited, vecDist, vecPath[i]);
    }

    // maybe see here: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    // also this for windows printing variables: https://stackoverflow.com/questions/62537957/vs-code-local-variables-not-showing-correctly

    // print and exit
    cout << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static vector<uint16_t> CheckNeighbors(vector<vector<uint8_t>> &rVecGrid,
                                       vector<vector<uint8_t>> &rVecVisited,
                                       vector<vector<uint16_t>> &rVecDist,
                                       vector<uint16_t> nodeCoords)
{
    uint16_t x = nodeCoords[0], y = nodeCoords[1];
    if (x < rVecDist.size() - 1)
    {
        UpdateDist(rVecDist, nodeCoords, +1, 0);
    }
    if (x > 0)
    {
        UpdateDist(rVecDist, nodeCoords, -1, 0);
    }
    if (y < rVecDist[0].size() - 1)
    {
        UpdateDist(rVecDist, nodeCoords, 0, +1);
    }
    if (y > 0)
    {
        UpdateDist(rVecDist, nodeCoords, 0, -1);
    }
}

static void UpdateDist(vector<vector<uint16_t>> &rVecDist,
                       vector<uint16_t> nodeCoords,
                       uint8_t xOffset, uint8_t yOffset)
{
}
