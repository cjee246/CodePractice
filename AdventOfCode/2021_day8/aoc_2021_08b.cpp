/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-19
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
#include "../Libraries/aocFile.h"

using namespace std;

/******************************************************************************/
/* GLOBAL VARS */
/******************************************************************************/
#define VAR 0

/******************************************************************************/
/* FUNCTION DECLARATIONS */
/******************************************************************************/
static void getStrVec(ifstream &fileStream, vector<string> *vecStr);
static void parseStrVec(vector<string> *vecStr,
                        vector<vector<string>> *vecCode,
                        vector<vector<string>> *vecData);
static void getCode();
static void getOutput();
static uint16_t getVal(vector<string> *vecData, vector<string> *vecCode);

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

    // get code and data
    vector<string> vecStr;
    vector<vector<string>> vecCode;
    vector<vector<string>> vecData;
    getStrVec(fileInput, &vecStr);
    parseStrVec(&vecStr, &vecCode, &vecData);

    // go through each vector element and get value
    vector<uint32_t> vecVal;
    uint64_t count = 0;
    for (uint16_t i = 0; i < vecData.size(); i++)
    {
        vecVal.push_back(getVal(&vecData[i], &vecCode[i]));
    }

    // print and exit
    cout << accumulate(vecVal.begin(), vecVal.end(), 0) << '\n';
    fileInput.close();
    return 0;
}

/******************************************************************************/
/* FUNCTION DEFINITIONS */
/******************************************************************************/
static void getStrVec(ifstream &fileStream, vector<string> *vecStr)
{
    string substr;
    while (getline(fileStream, substr))
    {
        if (substr.size() > 0)
        {
            (*vecStr).push_back(substr);
        }
    }
}

static void parseStrVec(vector<string> *vecStr,
                        vector<vector<string>> *vecCode,
                        vector<vector<string>> *vecData)
{
    stringstream strStream;
    string substr;
    uint8_t i = 0;
    for (auto &str : (*vecStr))
    {
        strStream.clear();
        strStream << str;
        (*vecCode).push_back(vector<string>());
        (*vecData).push_back(vector<string>());

        while (substr != "|")
        {
            getline(strStream, substr, ' ');
            if (substr == "|")
            {
                break;
            }
            (*vecCode)[i].push_back(substr);
        }
        while (strStream.good())
        {
            getline(strStream, substr, ' ');
            (*vecData)[i].push_back(substr);
        }
        i++;
    }
}

static uint16_t getVal(vector<string> *vecData, vector<string> *vecCode)
{
    // save 4 and 7
    string knowns[2];
    for (auto &str : (*vecCode))
    {
        if (str.size() == 4)
        {
            knowns[0] = str;
        }
        else if (str.size() == 3)
        {
            knowns[1] = str;
        }
    }

    // determine digits
    char charVal[4];
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t count4 = 0;
        uint8_t count7 = 0;
        switch ((*vecData)[i].length())
        {
        case 2:
            charVal[i] = '1';
            break;
        case 4:
            charVal[i] = '4';
            break;
        case 3:
            charVal[i] = '7';
            break;
        case 7:
            charVal[i] = '8';
            break;
        case 5:
            for (uint8_t j = 0; j < 5; j++)
            {
                if (knowns[0].find((*vecData)[i][j]) != string::npos)
                {
                    count4++;
                }
                if (knowns[1].find((*vecData)[i][j]) != string::npos)
                {
                    count7++;
                }
            }
            if (count4 == 2)
            {
                charVal[i] = '2';
            }
            else if (count7 == 3)
            {
                charVal[i] = '3';
            }
            else
            {
                charVal[i] = '5';
            }
            break;
        case 6:
            for (uint8_t j = 0; j < 6; j++)
            {
                if (knowns[0].find((*vecData)[i][j]) != string::npos)
                {
                    count4++;
                }
                if (knowns[1].find((*vecData)[i][j]) != string::npos)
                {
                    count7++;
                }
            }
            if (count7 == 2)
            {
                charVal[i] = '6';
            }
            else if (count4 == 3)
            {
                charVal[i] = '0';
            }
            else
            {
                charVal[i] = '9';
            }
            break;
        default:
            break;
        }
    }

    // return final 4-digit value
    return stoi(charVal);
}

static void getCode()
{
    /*
    // init code vector
    vector<string> vec(7);

    // Define Rules:
    // size 2, val = 1
    // size 3, val = 7
    // size 4, val = 4
    // size 7, val = 8

    // Secondary Rules
    // size 5, val = 2, 3, 5
    // size 6, val = 0, 6, 9

    // size 6 unique values:
    // compare to 7, val = 6 if only 2 matches
    // compare to 4, val = 0 if only 3 matches
    // otherwise, val = 9

    // size 5 unique values:
    // compare to 4, val = 2 if only 2 matches
    // compare to 7, val = 3 if all 3 match
    // otherwise, val = 5
    */
}
