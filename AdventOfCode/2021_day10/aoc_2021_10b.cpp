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
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "../Libraries/aocFile.h"

using namespace std;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define VAR 0

static vector<char> vecOpen = {'(', '[', '{', '<'};
static vector<char> vecClose = {')', ']', '}', '>'};
static vector<uint64_t> vecScore = {1, 2, 3, 4};

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static string checkSyntax(string line);

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

    // get vector of strings;
    vector<string> vecStr;
    getStrVec(fileInput, &vecStr);
    vector<string> vecCorrect;
    string err;
    for (uint8_t i = 0; i < vecStr.size(); i++)
    {
        err = checkSyntax(vecStr[i]);
        if (err.size() == 1)
        {
            vecStr.erase(vecStr.begin() + i--);
        }
        else
        {
            vecCorrect.push_back(err);
        }
    }

    // final count and score
    vector<uint64_t> vecPoints(vecCorrect.size(), 0);
    vector<char>::iterator it;
    uint8_t idx;
    for (uint8_t i = 0; i < vecPoints.size(); i++)
    {
        for (int8_t j = vecCorrect[i].size() - 1; j >= 0; j--)
        {
            vecPoints[i] *= 5;
            it = find(vecOpen.begin(), vecOpen.end(), vecCorrect[i].at(j));
            idx = it - vecOpen.begin();
            vecPoints[i] += vecScore[idx];
        }
    }
    sort(vecPoints.begin(), vecPoints.end());
    while (vecPoints.size() > 1)
    {
        vecPoints.erase(vecPoints.begin());
        vecPoints.pop_back();
    }
    uint64_t score = vecPoints[0];

    // print and exit
    cout << score << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static string checkSyntax(string line)
{
    stringstream strStream;
    vector<char> vecTrack;
    char c_return;

    for (uint16_t i = 0; i < line.size(); i++)
    {
        c_return = line.at(i);
        for (uint8_t j = 0; j < vecOpen.size(); j++)
        {
            if (c_return == vecOpen[j])
            {
                vecTrack.push_back(c_return);
                break;
            }
            else if (c_return == vecClose[j])
            {
                if (vecTrack.back() != vecOpen[j])
                {
                    string s;
                    s = c_return;
                    return s;
                }
                else
                {
                    vecTrack.pop_back();
                }
                break;
            }
        }
    }
    string s(vecTrack.begin(), vecTrack.end());
    return s;
}