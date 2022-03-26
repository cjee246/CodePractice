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
static vector<char> GetUnique(string first, vector<vector<string>> &rVecRules);
static void Polymerize(string &rPoly, vector<vector<string>> &rVecRules);
static uint32_t FinalCount(const string &rPoly, vector<char> &rUnique, vector<uint32_t> &rCount);

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

    // setup vectors
    vector<string> vecString;
    vector<vector<string>> vecRules;
    GetStrVec(fileInput, vecString);
    string poly = ParseStrVec(vecString, vecRules);
    vector<char> vecUnique = GetUnique(poly, vecRules);
    vector<uint32_t> vecCount(vecUnique.size(), 0);

    // do insertion for loop
    for (uint8_t i = 0; i < STEPS; i++)
    {
        Polymerize(poly, vecRules);
    }

    // print and exit
    cout << FinalCount(poly, vecUnique, vecCount) << '\n';
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
    rVecRules.push_back(vector<string>());
    rVecRules.push_back(vector<string>());
    for (uint8_t i = 0; i < rVecStr.size(); i++)
    {
        rVecRules[0].push_back(rVecStr[i].substr(0, 2));
        rVecRules[1].push_back(rVecStr[i].substr(6, 1));
    }
    rVecStr.clear();
    rVecStr.shrink_to_fit();
    return first;
}

static vector<char> GetUnique(string first, vector<vector<string>> &rVecRules)
{
    vector<char>::iterator it;
    vector<char> unique;

    // find unique values in first poly
    for (uint8_t i = 0; i < first.size(); i++)
    {
        it = find(unique.begin(), unique.end(), first[i]);
        if (it == unique.end())
        {
            unique.push_back(first[i]);
        }
    }

    // find unique values in poly rules
    for (uint8_t i = 0; i < rVecRules[1].size(); i++)
    {
        it = find(unique.begin(), unique.end(), rVecRules[1][i][0]);
        if (it == unique.end())
        {
            unique.push_back(rVecRules[1][i][0]);
        }
    }

    return unique;
}

static void Polymerize(string &rPoly, vector<vector<string>> &rVecRules)
{
    string substr;
    vector<string>::iterator it;
    uint8_t idx;
    for (uint64_t i = 0; i < rPoly.size() - 1; i++)
    {
        substr = rPoly.substr(i, 2);
        it = find(rVecRules[0].begin(), rVecRules[0].end(), substr);
        idx = it - rVecRules[0].begin();
        rPoly.insert(rPoly.begin() + i + 1, rVecRules[1][idx][0]);
        i++;
    }
}

static uint32_t FinalCount(const string &rPoly, vector<char> &rUnique, vector<uint32_t> &rCount)
{
    uint32_t current = 0, min = 0, max = 0;
    for (uint8_t i = 0; i < rUnique.size(); i++)
    {
        current = count(rPoly.begin(), rPoly.end(), rUnique[i]);
        rCount[i] = current;
        if (current > max)
        {
            max = current;
        }
        if (current < min || min == 0)
        {
            min = current;
        }
    }
    return max - min;
}