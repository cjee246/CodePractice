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

    // parse brackets

    // print and exit
    cout << '\n';
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