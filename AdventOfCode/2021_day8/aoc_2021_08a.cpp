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
static void getLine();
static void getEncryption();
static void getOutput();

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

    // look for     1, 4, 7, 8 (unique segments)
    // equates to   2, 4, 3, 7 counts

    // print and exit
    cout << '\n';
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
        (*vecStr).push_back(substr);
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