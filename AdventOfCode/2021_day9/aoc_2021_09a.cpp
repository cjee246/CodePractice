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

    // get grid
    vector<vector<uint8_t>> grid;
    getGrid(fileInput, &grid);

    // how to find low points?
    // scan horizontally, save positions
    // scan vertically at positions only?

    // print and exit
    cout << '\n';
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
            (*vecGrid)[row].push_back((uint8_t)fileChar);
        }
        else
        {
            row++;
            (*vecGrid).push_back(vector<uint8_t>());
        }
    }
    (*vecGrid).pop_back();
}
