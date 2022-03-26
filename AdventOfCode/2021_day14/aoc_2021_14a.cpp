/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-26
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
#define STEPS 10

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static string ParseStrVec(vector<string> &rVecStr, vector<vector<string>> &rVecRules);
static void Polymerize(string &rPoly, const vector<vector<string>> &rVecRules);

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
    vector<string> vecString;
    vector<vector<string>> vecRules;
    GetStrVec(fileInput, vecString);
    string first = ParseStrVec(vecString, vecRules);

    // do insertion for loop
    for (uint8_t i = 0; i < STEPS; i++)
    {
        Polymerize(first, vecRules);
    }

    // print and exit
    cout << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static string ParseStrVec(vector<string> &rVecStr, vector<vector<string>> &rVecRules)
{
    string first = rVecStr[0];
    rVecStr.erase(rVecStr.begin());
    for (uint8_t i = 0; i < rVecStr.size(); i++)
    {
        rVecRules.push_back(vector<string>());
        rVecRules[i].push_back(rVecStr[i].substr(0, 2));
        rVecRules[i].push_back(rVecStr[i].substr(6, 1));
    }
    return first;
}

static void Polymerize(string &rPoly, const vector<vector<string>> &rVecRules)
{
}