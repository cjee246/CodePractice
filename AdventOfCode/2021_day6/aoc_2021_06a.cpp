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
#define DAYS 80u

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
    vector<uint8_t> fish;
    string str, substr;
    fileInput >> str;
    stringstream strStream(str);
    fish.clear();
    while (strStream.good())
    {
        getline(strStream, substr, ',');
        fish.push_back(stoi(substr));
    }

    // process fishies
    int l = fish.max_size();
    for (uint16_t i = 0; i < DAYS; i++)
    {
        uint32_t fishCount = fish.size();
        for (uint32_t j = 0; j < fishCount; j++)
        {
            if (fish[j] == 0)
            {
                fish.push_back(8);
                fish[j] = 6;
            }
            else
            {
                fish[j]--;
            }
        }
    }

    // print and exit
    cout << fish.size() << '\n';
    fileInput.close();
    return 0;
}
