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

    // read in vector pairs
    string str, substr;
    vector<vector<vector<uint8_t>>> lines;
    uint16_t count = 0;
    uint8_t x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    while (fileInput >> str)
    {
        stringstream strStream(str);
        getline(strStream, substr, ',');
        x1 = stoi(substr);
        getline(strStream, substr, '\n');
        y1 = stoi(substr);
        fileInput >> str;
        fileInput >> str;
        getline(strStream, substr, ',');
        x2 = stoi(substr);
        getline(strStream, substr, '\n');
        y2 = stoi(substr);
    }

    // 
    fileInput.close();
    return 0;
}
