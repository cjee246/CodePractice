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
static uint16_t UpdateDist(vector<vector<uint8_t>> &rVecGrid,
                           vector<vector<uint8_t>> &rVecVisited,
                           vector<vector<uint16_t>> &rVecDist,
                           vector<uint16_t> nodeCoords,
                           int8_t xOffset, int8_t yOffset);

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

    // initialize
    vecDist[0][0] = vecGrid[0][0];
    vecPath.push_back({0, 0});
    vector<uint16_t> newCoord;
    uint16_t currDist, currVal;
    uint16_t maxSize = vecGrid.size() * vecGrid[0].size();

    for (uint32_t i = 0; i < vecPath.size(); i++)
    {
        if (i == maxSize)
        {
            break;
        }
        newCoord = CheckNeighbors(vecGrid, vecVisited, vecDist, vecPath[i]);
        vecPath.push_back(newCoord);
        currDist = vecDist[newCoord[0]][newCoord[1]];
        currVal = vecGrid[newCoord[0]][newCoord[1]];

    }

    // maybe see here: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    // also this for windows printing variables: https://stackoverflow.com/questions/62537957/vs-code-local-variables-not-showing-correctly

    // print and exit
    cout << vecDist[vecGrid.size() - 1][vecGrid[0].size() - 1] << '\n';
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
    int8_t xOffset = 0, yOffset = 0;
    uint16_t xFinal, yFinal;
    uint16_t dist1 = 60000, dist2 = 0;
    if (x < rVecDist.size() - 1)
    {
        xOffset = +1;
        yOffset = 0;
        dist2 = UpdateDist(rVecGrid, rVecVisited, rVecDist, nodeCoords, xOffset, yOffset);
        if (dist2 < dist1)
        {
            dist1 = dist2;
            xFinal = x + xOffset;
            yFinal = y + yOffset;
        }
    }
    if (x > 0)
    {
        xOffset = -1;
        yOffset = 0;
        dist2 = UpdateDist(rVecGrid, rVecVisited, rVecDist, nodeCoords, xOffset, yOffset);
        if (dist2 < dist1)
        {
            dist1 = dist2;
            xFinal = x + xOffset;
            yFinal = y + yOffset;
        }
    }
    if (y < rVecDist[0].size() - 1)
    {
        xOffset = 0;
        yOffset = +1;
        dist2 = UpdateDist(rVecGrid, rVecVisited, rVecDist, nodeCoords, xOffset, yOffset);
        if (dist2 < dist1)
        {
            dist1 = dist2;
            xFinal = x + xOffset;
            yFinal = y + yOffset;
        }
    }
    if (y > 0)
    {
        xOffset = 0;
        yOffset = -1;
        dist2 = UpdateDist(rVecGrid, rVecVisited, rVecDist, nodeCoords, xOffset, yOffset);
        if (dist2 < dist1)
        {
            dist1 = dist2;
            xFinal = x + xOffset;
            yFinal = y + yOffset;
        }
    }

    // if in a corner
    if (dist1 == 60000)
    {
        uint16_t minDist = 60000;
        for (uint16_t i = 0; i < rVecGrid.size(); i++)
        {
            for (uint16_t j = 0; j < rVecGrid[i].size(); j++)
            {
                if (rVecVisited[i][j] == 0 && rVecDist[i][j] < minDist)
                {
                    minDist = rVecDist[i][j];
                    xFinal = i;
                    yFinal = j;
                }
            }
        }
    }

    rVecVisited[x][y]++;
    return {xFinal, yFinal};
}

static uint16_t UpdateDist(vector<vector<uint8_t>> &rVecGrid,
                           vector<vector<uint8_t>> &rVecVisited,
                           vector<vector<uint16_t>> &rVecDist,
                           vector<uint16_t> nodeCoords,
                           int8_t xOffset, int8_t yOffset)
{
    uint16_t x = nodeCoords[0], y = nodeCoords[1];
    uint16_t xNew = x + xOffset, yNew = y + yOffset;
    if (rVecVisited[xNew][yNew])
    {
        return 60000;
    }
    uint16_t newDist = rVecDist[x][y] + rVecGrid[xNew][yNew];
    if (newDist < rVecDist[xNew][yNew])
    {
        rVecDist[xNew][yNew] = newDist;
    }
    else
    {
        newDist = rVecDist[xNew][yNew];
    }
    return newDist;
}
