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
/* GLOBAL VARS */
/******************************************************************************/
static ifstream fileInput;
static vector<vector<vector<uint16_t>>> lines;



/******************************************************************************/
/* ADDITIONAL FUNCTIONS */
/******************************************************************************/
static void getLines()
{
    string str, substr;
    uint16_t x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    while (fileInput >> str)
    {
        // start string stream
        stringstream strStream(str);

        // get first pair from string
        getline(strStream, substr, ',');
        x1 = stoi(substr);
        getline(strStream, substr, '\n');
        y1 = stoi(substr);

        // get second pair from file
        fileInput >> str;
        fileInput >> str;

        // get second pair from string
        getline(strStream, substr, ',');
        x2 = stoi(substr);
        getline(strStream, substr, '\n');
        y2 = stoi(substr);

        // if vertical/horizontal, add to vector
        if (x1 == x2 || y1 == y2)
        {
            lines.push_back( { {x1, y1}, {x2, y2} } );
        }
    }
}



/******************************************************************************/
/* MAIN */
/******************************************************************************/
int main()
{
    // read file
    std::ios::sync_with_stdio(false);

    if (loadFile(fileInput))
    {
        fileInput.close();
        return 0;
    }

    // read in vector pairs
    getLines();
    uint16_t count = 0;

    //
    fileInput.close();
    return 0;
}

