/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-19
 */

/******************************************************************************/
/* INCLUDES & NAMESPACES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "../Libraries/aocFile.h"

using namespace std;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define VAR 0

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void getGrid(ifstream &fileStream, vector<vector<uint8_t>> *vecGrid);
static void scanX(vector<vector<uint8_t>> *vecGrid,
                  vector<vector<uint8_t>> *vecCoords);
static void scanY(vector<vector<uint8_t>> *vecGrid,
                  vector<vector<uint8_t>> *vecCoords);
static uint64_t scanBasin(vector<vector<uint8_t>> *vecGrid,
                          vector<uint8_t> *coord);
static void raiseDirection(vector<vector<uint8_t>> *vecGrid,
                           vector<vector<uint8_t>> *basinGrid,
                           vector<uint8_t> coord, char dir, int stage);

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

    // get grid and min coords
    vector<vector<uint8_t>> grid;
    getGrid(fileInput, &grid);
    vector<vector<uint8_t>> coords;
    scanX(&grid, &coords);
    scanY(&grid, &coords);

    // sum  values of coords and count
    uint64_t risk = 0;
    for (auto &coord : coords)
    {
        risk++;
        risk += (uint64_t)grid[coord[0]][coord[1]];
    }

    // get basin height maps
    vector<uint64_t> basinSize;
    for (auto &coord : coords)
    {
        basinSize.push_back(scanBasin(&grid, &coord));
    }
    vector<uint64_t> basinMax(3, 0);
    for (auto &size : basinSize)
    {
        for (uint8_t i = 0; i < basinMax.size(); i++)
        {
            if (size > basinMax[i])
            {
                basinMax.insert(basinMax.begin() + i, size);
                basinMax.pop_back();
                break;
            }
        }
    }

    // print and exit
    cout << basinMax[0] * basinMax[1] * basinMax[2] << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static void getGrid(ifstream &fileStream, vector<vector<uint8_t>> *vecGrid)
{
    char fileChar;
    uint8_t row = 0;
    (*vecGrid).push_back(vector<uint8_t>());
    while (fileStream.get(fileChar))
    {
        if (isdigit(fileChar))
        {
            (*vecGrid)[row].push_back(stoi(&fileChar));
        }
        else
        {
            row++;
            (*vecGrid).push_back(vector<uint8_t>());
        }
    }
    (*vecGrid).pop_back();
}

static void scanX(vector<vector<uint8_t>> *vecGrid,
                  vector<vector<uint8_t>> *vecCoords)
{
    for (uint8_t i = 0; i < (*vecGrid).size(); i++)
    {
        if ((*vecGrid)[i][0] < (*vecGrid)[i][1])
        {
            (*vecCoords).push_back({i, 0});
        }
        for (uint8_t j = 1; j < (*vecGrid)[i].size() - 1; j++)
        {
            if (((*vecGrid)[i][j] < (*vecGrid)[i][j + 1]) &&
                ((*vecGrid)[i][j] < (*vecGrid)[i][j - 1]))
            {
                (*vecCoords).push_back({i, j});
                j++;
            }
        }
        if ((*vecGrid)[i][(*vecGrid)[i].size() - 1] <
            (*vecGrid)[i][(*vecGrid)[i].size() - 2])
        {
            (*vecCoords).push_back({i, (*vecGrid)[i].size() - 1});
        }
    }
}

static void scanY(vector<vector<uint8_t>> *vecGrid,
                  vector<vector<uint8_t>> *vecCoords)
{
    const uint8_t gridSize = (*vecGrid).size();
    for (int64_t i = 0; i < (*vecCoords).size(); i++)
    {
        if ((*vecCoords)[i][0] == 0)
        {
            if ((*vecGrid)[(*vecCoords)[i][0]][(*vecCoords)[i][1]] >
                (*vecGrid)[(*vecCoords)[i][0] + 1][(*vecCoords)[i][1]])
            {
                (*vecCoords).erase((*vecCoords).begin() + i);
                i--;
            }
        }
        else if ((*vecCoords)[i][0] == (*vecGrid).size() - 1)
        {
            if ((*vecGrid)[(*vecCoords)[i][0]][(*vecCoords)[i][1]] >
                (*vecGrid)[(*vecCoords)[i][0] - 1][(*vecCoords)[i][1]])
            {
                (*vecCoords).erase((*vecCoords).begin() + i);
                i--;
            }
        }
        else
        {
            if (((*vecGrid)[(*vecCoords)[i][0]][(*vecCoords)[i][1]] >
                 (*vecGrid)[(*vecCoords)[i][0] - 1][(*vecCoords)[i][1]]) ||
                ((*vecGrid)[(*vecCoords)[i][0]][(*vecCoords)[i][1]] >
                 (*vecGrid)[(*vecCoords)[i][0] + 1][(*vecCoords)[i][1]]))
            {
                (*vecCoords).erase((*vecCoords).begin() + i);
                i--;
            }
        }
    }
}

static uint64_t scanBasin(vector<vector<uint8_t>> *vecGrid,
                          vector<uint8_t> *coord)
{
    vector<vector<uint8_t>> basinGrid((*vecGrid).size(), vector<uint8_t>((*vecGrid)[0].size(), 0));

    raiseDirection(vecGrid, &basinGrid, (*coord), 'u', 2);
    raiseDirection(vecGrid, &basinGrid, (*coord), 'd', 2);
    raiseDirection(vecGrid, &basinGrid, (*coord), 'l', 2);
    raiseDirection(vecGrid, &basinGrid, (*coord), 'r', 2);

    uint64_t sizeCount = 0;
    for (auto &row : basinGrid)
    {
        for (auto &height : row)
        {
            if (height > 0)
            {
                sizeCount++;
            }
        }
    }
    return sizeCount;
}

static void raiseDirection(vector<vector<uint8_t>> *vecGrid,
                           vector<vector<uint8_t>> *basinGrid,
                           vector<uint8_t> coord, char dir, int stage)
{
    int16_t x = coord[0];
    int16_t y = coord[1];
    int8_t inc = 0;
    int16_t *p_inc;
    char dir1, dir2;

    switch (dir)
    {
    case 'u':
        p_inc = &x;
        inc = -1;
        dir1 = 'l';
        dir2 = 'r';
        break;
    case 'd':
        p_inc = &x;
        inc = +1;
        dir1 = 'l';
        dir2 = 'r';
        break;
    case 'l':
        p_inc = &y;
        inc = -1;
        dir1 = 'u';
        dir2 = 'd';
        break;
    case 'r':
        p_inc = &y;
        inc = +1;
        dir1 = 'u';
        dir2 = 'd';
        break;
    }

    while ((*vecGrid)[x][y] != 9)
    {
        (*basinGrid)[x][y]++;
        (*p_inc) += inc;
        if (x < 0 || y < 0 ||
            x >= (*vecGrid).size() || y >= (*vecGrid)[0].size())
        {
            break;
        }
        if (stage > 0)
        {
            raiseDirection(vecGrid, basinGrid,
                           {(uint8_t)x, (uint8_t)y}, dir1, stage - 1);
            raiseDirection(vecGrid, basinGrid,
                           {(uint8_t)x, (uint8_t)y}, dir2, stage - 1);
        }
    }
    return;
}
