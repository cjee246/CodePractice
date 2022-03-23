/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: YYYY-MM-DD
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
#include "../Libraries/aocLib_v02.h"

using namespace std;
using namespace aocLib_v02;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define VAR
static uint8_t startIdx, endIdx;
static uint16_t pathCount;
static vector<uint8_t> vecSmall;
static vector<uint8_t> vecMax;

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void ParsePath(string line, vector<string> &rCaves,
                      vector<vector<string>> &rNodes);
static uint8_t CheckCaves(string cave, vector<string> &rCaves,
                          vector<vector<string>> &rNodes);
static void FindAllPaths(vector<string> &caves, vector<vector<string>> nodes,
                         uint8_t idx, uint8_t bonus,
                         vector<uint8_t> tracker, string out);

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

    /*
    Plan
    - save all stations in a vector
    - save all adjacents in another vector
    - save all "small caves" in a vector
    - from start, do "get all adjacent paths"
        - recursive that returns true when all paths explored
        - increases count when reaches end
        - also removes small cave indices whenever one is left
    */

    // get string pairs
    vector<string> vecLines;
    getStrVec(fileInput, vecLines);

    // build vector of caves
    vector<string> vecCaves;
    vector<vector<string>> vecNodes;
    for (auto &str : vecLines)
    {
        ParsePath(str, vecCaves, vecNodes);
    }

    // get small caves vector
    vecMax = vector<uint8_t>(vecCaves.size(), 0);
    for (uint8_t i = 0; i < vecCaves.size(); i++)
    {
        if (islower(vecCaves[i][0]))
        {
            vecMax[i]++;
            if (vecCaves[i] != "start" && vecCaves[i] != "end")
            {
                vecSmall.push_back(i);
            }
        }
    }

    // process all pathways
    pathCount = 0;
    vector<uint8_t> vecTracker(vecCaves.size(), 0);
    FindAllPaths(vecCaves, vecNodes, startIdx, startIdx, vecTracker, "");

    // print and exit
    cout << pathCount << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static void ParsePath(string line, vector<string> &rCaves,
                      vector<vector<string>> &rNodes)
{
    string node1, node2;
    uint8_t idx1, idx2;
    vector<string>::iterator it;

    node1 = line.substr(0, line.find('-'));
    idx1 = CheckCaves(node1, rCaves, rNodes);
    node2 = line.substr(line.find('-') + 1, line.size());
    idx2 = CheckCaves(node2, rCaves, rNodes);

    rNodes[idx1].push_back(node2);
    rNodes[idx2].push_back(node1);
}

static uint8_t CheckCaves(string cave, vector<string> &rCaves,
                          vector<vector<string>> &rNodes)
{
    uint8_t idx;
    vector<string>::iterator it;
    it = find(rCaves.begin(), rCaves.end(), cave);
    if (it == rCaves.end())
    {
        rCaves.push_back(cave);
        it = rCaves.end() - 1;
        rNodes.push_back(vector<string>());
        idx = it - rCaves.begin();
        if (cave == "start")
        {
            startIdx = idx;
        }
        else if (cave == "end")
        {
            endIdx = idx;
        }
    }
    else
    {
        idx = it - rCaves.begin();
    }
    return idx;
}

static void FindAllPaths(vector<string> &caves, vector<vector<string>> nodes,
                         uint8_t idx, uint8_t bonus,
                         vector<uint8_t> tracker, string out)
{
    // setting up max
    vector<uint8_t> max = vecMax;
    if (bonus != startIdx)
    {
        max[bonus]++;
    }
    
    // reaching end
    string currCave = caves[idx];
    out += currCave;
    if (currCave == "end")
    {
        pathCount++;
        cout << out << '\n';
        return;
    }
    out += ", ";

    // paths in the middle
    for (uint8_t j = 0; j < vecSmall.size(); j++)
    {
        for (uint8_t i = 0; i < nodes[idx].size(); i++)
        {
            string currCave = caves[idx];
            uint8_t next = CheckCaves(nodes[idx][i], caves, nodes);
            string nextCave = caves[next];
            if (vecMax[next] == 0 || tracker[next] < max[next])
            {
                if (islower(currCave[0]))
                {
                    tracker[idx]++;
                }
                FindAllPaths(caves, nodes, next, j, tracker, out);
            }
        }
    }
}