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
static void FoldVec(vector<vector<uint16_t>> &rVec,
                    const vector<uint16_t> &rVecInstr);
static void SplitFlipVec(vector<vector<uint16_t>> &rVecIn,
                         vector<vector<uint16_t>> &rVecOut,
                         const vector<uint16_t> &rVecInstr);
static void StackVec(vector<vector<uint16_t>> &rVec1,
                     vector<vector<uint16_t>> &rVec2);
static uint32_t CountDots(const vector<vector<uint16_t>> &rVec);

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
    GetStrVec(fileInput, vecString);

    // Get instructions and plot
    vector<vector<uint16_t>> vecPlot;
    vector<vector<uint16_t>> vecInstr;
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
    vecString.clear();
    vecString.shrink_to_fit();

    // fold vector
    uint32_t firstFold = 0;
    for (uint32_t i = 0; i < vecInstr.size(); i++)
    {
        FoldVec(vecPlot, vecInstr[i]);
        if (i == 0)
        {
            firstFold = CountDots(vecPlot);
        }
    }

    // print and exit
    cout << "\nFirst fold: " << firstFold << "\n\n";
    for (uint8_t i = 0; i < vecPlot[0].size(); i++)
    {
        for (uint8_t j = 0; j < vecPlot.size(); j++)
        {
            if (vecPlot[j][i] == 0)
            {
                cout << ".";
            }
            else
            {
                cout << "#";
            }
        }
        cout << '\n';
    }
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

static void FoldVec(vector<vector<uint16_t>> &rVec,
                    const vector<uint16_t> &rVecInstr)
{
    vector<vector<uint16_t>> tempVec;
    SplitFlipVec(rVec, tempVec, rVecInstr);
    StackVec(rVec, tempVec);
}

static void SplitFlipVec(vector<vector<uint16_t>> &rVecIn,
                         vector<vector<uint16_t>> &rVecOut,
                         const vector<uint16_t> &rVecInstr)
{
    if (rVecInstr[0] == 0)
    {
        for (uint16_t i = 0; i <= rVecInstr[1] - 1; i++)
        {
            rVecOut.push_back(rVecIn.back());
            rVecIn.pop_back();
        }
        rVecIn.pop_back();
    }
    else
    {
        for (uint16_t i = 0; i < rVecIn.size(); i++)
        {
            rVecOut.push_back(vector<uint16_t>());
            for (uint16_t j = 0; j <= rVecInstr[1] - 1; j++)
            {
                rVecOut[i].push_back(rVecIn[i].back());
                rVecIn[i].pop_back();
            }
            rVecIn[i].pop_back();
        }
    }
    return;
}

static void StackVec(vector<vector<uint16_t>> &rVec1,
                     vector<vector<uint16_t>> &rVec2)
{
    for (uint16_t i = 0; i < rVec1.size(); i++)
    {
        for (uint16_t j = 0; j < rVec1[i].size(); j++)
        {
            rVec1[i][j] += rVec2[i][j];
        }
    }
    return;
}

static uint32_t CountDots(const vector<vector<uint16_t>> &rVec)
{
    uint32_t dotCount = 0;
    for (auto &vec : rVec)
    {
        for (auto &elem : vec)
        {
            if (elem > 0)
            {
                dotCount++;
            }
        }
    }
    return dotCount;
}