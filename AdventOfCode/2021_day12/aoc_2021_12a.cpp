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

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void ParsePath(string line, vector<string> &rCaves,
                      vector<vector<string>> &rNodes);
static uint8_t CheckCaves(string cave, vector<string> &rCaves,
                          vector<vector<string>> &rNodes);
static void FindAllPaths(vector<string> &caves, vector<vector<string>> nodes,
                         uint8_t idx, vector<uint8_t> tracker, string out);

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
    pathCount = 0;
    vector<uint8_t> vecTracker(vecCaves.size(), 0);
    FindAllPaths(vecCaves, vecNodes, startIdx, vecTracker, "");

    //

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
                         uint8_t idx, vector<uint8_t> tracker, string out)
{
    string currCave = caves[idx];
    out += currCave;
    if (currCave == "end")
    {
        pathCount++;
        //cout << out << '\n';
        return;
    }
    out += ", ";
    for (auto &nextCave : nodes[idx])
    {
        string currCave = caves[idx];
        uint8_t next = CheckCaves(nextCave, caves, nodes);
        if (islower(currCave[0]))
        {
            /* for (auto &vec : nodes)
            {
                vec.erase(remove(vec.begin(), vec.end(), currCave), vec.end());
            } */
        }
        if (currCave == "end")
        {
            pathCount++;
            break;
        }
        FindAllPaths(caves, nodes, next, tracker, out);
    }
}