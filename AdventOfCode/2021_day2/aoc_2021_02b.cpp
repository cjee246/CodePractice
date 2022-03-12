/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-11
 */

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Libraries/aocFile.h"

using namespace std;

int main()
{
    // apparently this makes iostream faster
    std::ios::sync_with_stdio(false);
    ifstream inputFile;
    if (loadFile(inputFile))
    {
        inputFile.close();
        return 0;
    }

    // get position
    uint32_t xPos = 0, zPos = 0, aim = 0, mult = 0;
    string cmd, val;
    while (inputFile >> cmd >> val)
    {
        if (cmd == "forward")
        {
            xPos += stoi(val);
            zPos += aim * stoi(val);
        }
        else if (cmd == "down")
        {
            aim += stoi(val);
        }
        else if (cmd == "up")
        {
            aim -= stoi(val);
        }
    }
    mult = xPos * zPos;

    // finish
    cout << mult << '\n';
    inputFile.close();
    return 0;
}