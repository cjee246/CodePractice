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
    vector<vector<char>> vecChar = {{'(', ')'},
                                    {'[', ']'},
                                    {'{', '}'},
                                    {'<', '>'}};
    vector<int16_t> count;
    vector<vector<char>> order;
    vector<vector<char>>::iterator it;
    uint16_t idx;
    char c_return;
    for (uint16_t i = 0; i < line.size(); i++)
    {
        c_return = line.at(i);
        for (uint8_t i = 0; i < vecChar.size(); i++)
        {
            if (c_return == vecChar[i][0] || c_return == vecChar[i][1])
            {
                // find index of char set
                it = find(order.begin(), order.end(), vecChar[i]);
                if (it != order.end())
                {
                    idx = distance(order.begin(), it);
                }
                else
                {
                    order.push_back(vecChar[i]);
                    count.push_back(0);
                    idx = order.size() - 1;
                }

                // acc count of char set
                if (c_return == vecChar[i][0])
                {
                    count[idx]++;
                }
                else
                {
                    count[idx]--;
                }

                // check bracket closure
                for (uint8_t j = 1; j < count.size(); j++)
                {
                    if (count[j] > count[j - 1])
                    {
                        return c_return;
                    }
                }
                break;
            }
        }
    }
    return 'x';
}