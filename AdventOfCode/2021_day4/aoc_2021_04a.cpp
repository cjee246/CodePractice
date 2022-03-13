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
#include "../Libraries/aocFile.h"
#include <algorithm>
#include <vector>

using namespace std;

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

    // declare vars
    string binStr;
    uint16_t binVal = 0, count = 0, oneBit = 1, binStrLen = 0;
    vector<uint16_t> vec(sizeof(uint16_t) * 8, 0);

    // read loop
    while (fileInput >> binStr)
    {
        if (count == 0)
        {
            binStrLen = binStr.length();
        }
        
        binVal = stoi(binStr, 0, 2);
        for (int i = 0; i < binStrLen; i++)
        {
            if (binVal & oneBit << i)
            {
                vec[i]++;
            }
        }
        count++;
    }

    // process vector data
    uint16_t gamma = 0, epsilon = 0;
    for (int i = 0; i < binStrLen; i++)
    {
        if (vec[i] > count / 2)
        {
            gamma = gamma | oneBit << i;
        }
        else
        {
            epsilon = epsilon | oneBit << i;
        }
    }

    // final output
    cout << epsilon * gamma << '\n';
    fileInput.close();
    return 0;
}