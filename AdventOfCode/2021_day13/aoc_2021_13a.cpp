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
static vector<vector<uint16_t>> GetSplitVec(const vector<vector<uint16_t>> &vec,
                                            uint16_t axisDir,
                                            uint16_t axisVal,
                                            bool first);
static void FlipVec(vector<vector<uint16_t>> &rVec, uint8_t dir);
static void StackVec(vector<vector<uint16_t>> &rVec1,
                     vector<vector<uint16_t>> &rVec2);
static void FoldVec(vector<vector<uint16_t>> &rVec,
                    const vector<uint16_t> &rVecInstr);
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
    cout << firstFold << '\n';
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

static vector<vector<uint16_t>> GetSplitVec(const vector<vector<uint16_t>> &vec,
                                            uint16_t axisDir,
                                            uint16_t axisVal,
                                            bool first)
{
    vector<vector<uint16_t>> splitVec = vec;
    uint16_t start, end;
    if (axisDir == 0)
    {
        for (uint16_t i = 0; i <= axisVal; i++)
        {
            if (first)
            {
                splitVec.pop_back();
            }
            else
            {
                splitVec.erase(splitVec.begin());
            }
        }
    }
    else
    {
        for (auto &yvec : splitVec)
        {
            for (uint16_t i = 0; i <= axisVal; i++)
            {
                if (first)
                {
                    yvec.pop_back();
                }
                else
                {
                    yvec.erase(yvec.begin());
                }
            }
        }
    }
    return splitVec;
}

static void FlipVec(vector<vector<uint16_t>> &rVec, uint8_t dir)
{
    if (dir == 0)
    {
        for (int16_t i = rVec.size() - 1; i >= 0; i--)
        {
            rVec.push_back(rVec[i]);
            rVec.erase(rVec.begin() + i);
        }
    }
    else
    {
        for (auto &yvec : rVec)
        {
            for (int16_t i = yvec.size() - 1; i >= 0; i--)
            {

                yvec.push_back(yvec[i]);
                yvec.erase(yvec.begin() + i);
            }
        }
    }
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

static void FoldVec(vector<vector<uint16_t>> &rVec,
                    const vector<uint16_t> &rVecInstr)
{
    vector<vector<uint16_t>> vec1 = GetSplitVec(rVec, rVecInstr[0], rVecInstr[1], true);
    vector<vector<uint16_t>> vec2 = GetSplitVec(rVec, rVecInstr[0], rVecInstr[1], false);
    rVec.clear();
    FlipVec(vec2, rVecInstr[0]);
    StackVec(vec1, vec2);
    copy(vec1.begin(), vec1.end(), back_inserter(rVec));
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