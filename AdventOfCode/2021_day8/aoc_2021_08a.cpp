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
static void getString(ifstream &fileStream, vector<string> *vecStr);
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

    // get encryption and data
    vector<string> vecStr;
    getString(fileInput, &vecStr);

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
static void getString(ifstream &fileStream, vector<string> *vecStr)
{
    string substr;
    while (getline(fileStream, substr))
    {
        (*vecStr).push_back(substr);
    }

}