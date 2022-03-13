/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-12
 */

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "../Libraries/aocFile.h"

using namespace std;


static bool checkBingo(int16_t num, vector<int16_t> *list, vector<int16_t> *track)
{
    // find index of value, replace grid val with -1
    vector<int16_t>::iterator it;
    it = find((*list).begin(), (*list).end(), num);
    if (it == (*list).end())
    {
        return false;
    }
    int16_t idx = distance((*list).begin(), it);
    (*list)[idx] = -1;

    // find line code for tracking 5-in-a-row
    int16_t idx1 = idx / 5;
    int16_t idx2 = idx % 5 + 5;
    (*track)[idx1]++;
    (*track)[idx2]++;

    // if 5iar, return true
    if ((*track)[idx1] == 5 || (*track)[idx2] == 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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

    // get drawn numbers
    vector<int16_t> drawnNum;
    string drawnStr, substr;
    fileInput >> drawnStr;
    stringstream streamStr(drawnStr);
    while (streamStr.good())
    {
        getline(streamStr, substr, ',');
        drawnNum.push_back(stoi(substr));
    }

    // get grid numbers
    vector<vector<int16_t>> gridAll;
    vector<int16_t> gridNum;
    string gridStr;
    int16_t count = 0, total = 0;
    while (fileInput >> gridStr)
    {
        count++;
        gridNum.push_back(stoi(gridStr));
        if (count == 25)
        {
            count = 0;
            gridAll.push_back(gridNum);
            gridNum.clear();
            total++;
        }
    }

    // read in drawn numbers
    vector<vector<int16_t>> gridTrack(gridAll.size(), vector<int16_t>(10));
    bool winner = false;
    int16_t drawIdx = 0, drawCurr = 0, gridWin = 0;
    int16_t check = 0;
    while (!winner)
    {
        drawCurr = drawnNum[drawIdx];
        for (int i = 0; i < gridAll.size(); i++)
        {
            winner = checkBingo(drawCurr, &gridAll[i], &gridTrack[i]);
            if (check != gridTrack[2][0])
            {
                check++;
            }
            if (winner)
            {
                if (gridAll.size() > 1)
                {
                    gridAll.erase(gridAll.begin() + i);
                    gridTrack.erase(gridTrack.begin() + i);
                    i--;
                    winner = false;
                }
                else
                {
                    gridWin = i;
                    break;
                }
            }
        }
        drawIdx++;
    }

    // replace -1 with 0 and sum and mult and print
    replace(gridAll[gridWin].begin(), gridAll[gridWin].end(), -1, 0);
    uint16_t sum = accumulate(gridAll[gridWin].begin(), gridAll[gridWin].end(), 0);
    cout << drawCurr * sum << '\n';
    fileInput.close();
    return 0;
}
