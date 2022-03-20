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
static vector<uint64_t> vecScore = {3, 57, 1197, 25137};

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static char checkSyntax(string line);

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
    vector<char> vecErr;
    getStrVec(fileInput, &vecStr);
    for (auto &str : vecStr)
    {
        vecErr.push_back(checkSyntax(str));
    }

    // final count and score
    vector<char>::iterator it;
    vector<uint16_t> count(4, 0);
    uint8_t idx;
    uint64_t score = 0;
    for (auto &ch : vecErr)
    {
        if (ch != ' ')
        {
            it = find(vecClose.begin(), vecClose.end(), ch);
            idx = it - vecClose.begin();
            count[idx]++;
        }
    }
    for (uint8_t i = 0; i < count.size(); i++)
    {
        score += count[i] * vecScore[i];
    }

    // print and exit
    cout << score << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static char checkSyntax(string line)
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
                    return c_return;
                }
                else
                {
                    vecTrack.pop_back();
                }
                break;
            }
        }
    }
    return ' ';
}