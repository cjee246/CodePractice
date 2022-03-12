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
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    // read file
    std::ios::sync_with_stdio(false);
    ifstream fileInput;
    string fileStr;
    if (loadFile(fileInput, &fileStr))
    {
        fileInput.close();
        return 0;
    }

    // declare vars
    string binStr;
    uint16_t binVal = 0, count = 0, oneBit = 1, binStrLen = 0;
    vector<uint16_t> countOneBits(sizeof(uint16_t) * 8, 0);

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
                countOneBits[i]++;
            }
        }
        count++;
    }

    // process vector data - gamma/epsilon
    uint16_t gamma = 0, epsilon = 0;
    for (int i = 0; i < binStrLen; i++)
    {
        if (countOneBits[i] > count / 2)
        {
            gamma = gamma | oneBit << i;
        }
        else
        {
            epsilon = epsilon | oneBit << i;
        }
    }

    // restart vector elements - O2
    vector<uint16_t> o2Val(count);
    uint16_t onesCount = 0;
    float totalCount = 0.0f;
    fileInput.clear();
    fileInput.seekg(0, ios::beg);
    for (int i = 0; i < count; i++)
    {
        fileInput >> binStr;
        o2Val[i] = stoi(binStr, 0, 2);
    }

    // iterate through vectors - O2
    for (int i = binStrLen - 1; i >= 0; i--)
    {
        onesCount = 0, totalCount = 0.0f;
        for (int j = 0; j < o2Val.size(); j++)
        {
            if (o2Val[j] & oneBit << i)
            {
                onesCount++;
            }
            totalCount++;
        }
        if (onesCount != 0 && onesCount != totalCount)
        {
            for (int j = 0; j < o2Val.size(); j++)
            {
                if (onesCount >= totalCount / 2)
                {
                    if (!(o2Val[j] & oneBit << i))
                    {
                        o2Val.erase(o2Val.begin() + j--);
                    }
                }
                else
                {
                    if (o2Val[j] & oneBit << i)
                    {
                        o2Val.erase(o2Val.begin() + j--);
                    }
                }
            }
        }
        if (o2Val.size() == 1)
        {
            break;
        }
    }

    // restart vector elements - CO2
    vector<uint16_t> co2Val(count);
    fileInput.clear();
    fileInput.seekg(0, ios::beg);
    for (int i = 0; i < count; i++)
    {
        fileInput >> binStr;
        co2Val[i] = stoi(binStr, 0, 2);
    }

    // iterate through vectors - CO2
    for (int i = binStrLen - 1; i >= 0; i--)
    {
        onesCount = 0, totalCount = 0.0f;
        for (int j = 0; j < co2Val.size(); j++)
        {
            if (co2Val[j] & oneBit << i)
            {
                onesCount++;
            }
            totalCount++;
        }
        if (onesCount != 0 && onesCount != totalCount)
        {
            for (int j = 0; j < co2Val.size(); j++)
            {
                if (onesCount >= totalCount / 2)
                {
                    if (co2Val[j] & oneBit << i)
                    {
                        co2Val.erase(co2Val.begin() + j--);
                    }
                }
                else
                {
                    if (!(co2Val[j] & oneBit << i))
                    {
                        co2Val.erase(co2Val.begin() + j--);
                    }
                }
            }
        }
        if (co2Val.size() == 1)
        {
            break;
        }
    }

    // final output
    cout << o2Val[0] * co2Val[0] << '\n';
    fileInput.close();
    return 0;
}