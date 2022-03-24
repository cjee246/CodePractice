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
static uint32_t pathCount;
static vector<uint8_t> vecSmall;

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void ParsePath(string line, vector<string> &rCaves,
                      vector<vector<string>> &rNodes);
static uint8_t CheckCaves(string cave, vector<string> &rCaves,
                          vector<vector<string>> &rNodes);
static void FindAllPaths(vector<string> &caves, vector<vector<string>> nodes,
                         uint8_t idx, vector<uint8_t> max,
                         vector<uint8_t> track, string out);

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
    vector<uint8_t> vecMax = vector<uint8_t>(vecCaves.size(), 0);
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
    FindAllPaths(vecCaves, vecNodes, startIdx, vecMax, vecTracker, "");

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
                         uint8_t idx, vector<uint8_t> max,
                         vector<uint8_t> track, string out)
{
    // reaching end
    string currCave = caves[idx];
    out += currCave;
    if (currCave == "end")
    {
        vector<uint8_t>::iterator it1 = find(max.begin(), max.end(), 2);
        vector<uint8_t>::iterator it2 = find(track.begin(), track.end(), 2);
        if (it1 == max.end() || it2 != track.end())
        {
            pathCount++;
            //cout << out << '\n';
            return;
        }
    }
    out += ", ";

    // do sesarch
    for (uint8_t i = 0; i < nodes[idx].size(); i++)
    {
        string currCave = caves[idx];
        uint8_t next = CheckCaves(nodes[idx][i], caves, nodes);
        string nextCave = caves[next];
        if (max[next] == 0 || track[next] < max[next])
        {
            if (islower(currCave[0]))
            {
                track[idx]++;
                FindAllPaths(caves, nodes, next, max, track, out);
                if (idx != startIdx && idx != endIdx &&
                    find(max.begin(), max.end(), 2) == max.end())
                {
                    max[idx]++;
                    FindAllPaths(caves, nodes, next, max, track, out);
                    max[idx]--;
                }
                track[idx]--;
            }
            else
            {
                FindAllPaths(caves, nodes, next, max, track, out);
            }
        }
    }
}