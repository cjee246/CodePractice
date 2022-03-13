/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-13
 */

/******************************************************************************/
/* HEADER FILES */
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
#define DAYS 256u

/******************************************************************************/
/* ADDITIONAL FUNCTIONS */
/******************************************************************************/
static void func()
{
}

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

    // init vector from string stream
    vector<uint64_t> fishInit, fishCurr, fishLast;
    string str, substr;
    fileInput >> str;
    stringstream strStream(str);
    while (strStream.good())
    {
        getline(strStream, substr, ',');
        fishInit.push_back(stoi(substr));
    }

    // count # each starting number
    fishCurr = {(uint64_t)count(fishInit.begin(), fishInit.end(), 0),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 1),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 2),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 3),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 4),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 5),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 6),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 7),
                (uint64_t)count(fishInit.begin(), fishInit.end(), 8)};
    fishLast.resize(fishCurr.size(), 0);

    // process fishies
    for (uint16_t i = 0; i < DAYS; i++)
    {
        fishLast[0] = fishCurr[0];
        fishLast[1] = fishCurr[1];
        fishLast[2] = fishCurr[2];
        fishLast[3] = fishCurr[3];
        fishLast[4] = fishCurr[4];
        fishLast[5] = fishCurr[5];
        fishLast[6] = fishCurr[6];
        fishLast[7] = fishCurr[7];
        fishLast[8] = fishCurr[8];

        fishCurr[0] = fishLast[1];
        fishCurr[1] = fishLast[2];
        fishCurr[2] = fishLast[3];
        fishCurr[3] = fishLast[4];
        fishCurr[4] = fishLast[5];
        fishCurr[5] = fishLast[6];
        fishCurr[6] = fishLast[7] + fishLast[0];
        fishCurr[7] = fishLast[8];
        fishCurr[8] = fishLast[0];
    }

    // print and exit
    uint64_t sum = 0;
    for (auto& n : fishCurr)
    {
        sum += n;
    }
    cout << sum << '\n';
    fileInput.close();
    return 0;
}
