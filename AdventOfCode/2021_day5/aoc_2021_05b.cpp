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
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "../Libraries/aocFile.h"

using namespace std;

/******************************************************************************/
/* ADDITIONAL FUNCTIONS */
/******************************************************************************/
static uint16_t getLines(ifstream &filestream, vector<vector<vector<uint16_t>>> *lines)
{
    string str, substr;
    uint16_t x1 = 0, y1 = 0, x2 = 0, y2 = 0, max = 0;
    stringstream strStream;
    while (filestream >> str)
    {
        // get first pair from string
        strStream.clear();
        strStream << str;
        getline(strStream, substr, ',');
        x1 = stoi(substr);
        getline(strStream, substr, '\n');
        y1 = stoi(substr);

        // get second pair from file
        filestream >> str;
        filestream >> str;

        // get second pair from string
        strStream.clear();
        strStream << str;
        getline(strStream, substr, ',');
        x2 = stoi(substr);
        getline(strStream, substr);
        y2 = stoi(substr);

        //get max
        vector<uint16_t> temp = {x1, y1, x2, y2};
        uint16_t tempMax = *max_element(temp.begin(), temp.end());
        if (tempMax > max)
        {
            max = tempMax;
        }

        // if vertical/horizontal, add to vector
        if (x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2))
        {
            (*lines).push_back({{x1, y1}, {x2, y2}});
        }
    }
    return max;
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

    // read in vector pairs
    vector<vector<vector<uint16_t>>> lines;
    uint16_t x = 0, y = 0, gridSize = 0;
    gridSize = getLines(fileInput, &lines) + 1;
    uint16_t grid[gridSize][gridSize] = { 0 };
    for (int16_t i = 0; i < lines.size(); i++)
    {
        x = lines[i][0][0];
        y = lines[i][0][1];
        bool iseq = false;
        while (x != lines[i][1][0] || y != lines[i][1][1])
        {
            grid[x][y]++;
            if (x < lines[i][1][0])
            {
                x++;
            }
            if (x > lines[i][1][0])
            {
                x--;
            }
            if (y < lines[i][1][1])
            {
                y++;
            }
            if (y > lines[i][1][1])
            {
                y--;
            }
        }
        grid[x][y]++;
    }

    //count numbers greater than or equal to x
    uint16_t thresh = 2;
    uint16_t count = 0;
    for (uint16_t i = 0; i < sizeof(grid)/sizeof(grid[1]); i++)
    {
        for (uint16_t j = 0; j < sizeof(grid)/sizeof(grid[0]); j++)
        {
            if (grid[i][j] >= thresh)
            {
                count++;
            }
        }
    }

    // print and exit
    cout << count << '\n';
    fileInput.close();
    return 0;
}
