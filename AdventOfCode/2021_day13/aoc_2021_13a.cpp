/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-24
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
static void func();
static void GetInstr(string instr, vector<vector<uint16_t>> &rVec);

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

    // string vector and then grid
    vector<string> vecString;
    vector<vector<uint16_t>> vecPlot;
    vector<vector<uint16_t>> vecInstr;
    GetStrVec(fileInput, vecString);
    for (uint32_t i = 0; i < vecString.size(); i++)
    {
        if (isalpha(vecString[i][0]))
        {
            GetInstr(vecString[i], vecInstr);
        }
        else
        {
            PlotVec(vecString[i], ',', vecPlot, false);
        }
    }


    // print and exit
    cout << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static void GetInstr(string instr, vector<vector<uint16_t>> &rVec)
{
    stringstream strStream(instr);
    string axis, valStr;
    uint16_t val;
    {
        getline(strStream, axis, ' ');
        getline(strStream, axis, ' ');
        getline(strStream, axis, '=');
        getline(strStream, valStr);
        val = stoi(valStr);
        if (axis == "x")
        {
            rVec.push_back({0, val});
        }
        else
        {
            rVec.push_back({1, val});
        }
    }
}