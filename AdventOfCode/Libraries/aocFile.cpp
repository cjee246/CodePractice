
/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-11
 */

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include "aocFile.h"
using namespace std;

/******************************************************************************/
/* FUNCTIONS */
/******************************************************************************/

/*!
 *  @brief      Function description
 *  @param      parameter description
 */
void exampleFunc(int parameter) {}

int loadFile(ifstream &filestream)
{
    // read text file
    string inputName;
    cout << "Enter filename.\n";
    cin >> inputName;
    filestream.open(inputName);
    while (!filestream)
    {
        cout << "File does not exist. Enter filename or type 'q' to quit.\n";
        cin >> inputName;
        if (inputName == "q")
        {
            return 1;
        }
        filestream.open(inputName);
    }
    return 0;
}

int loadFile(ifstream &filestream, string *filestr)
{
    // read text file
    string inputName;
    cout << "Enter filename.\n";
    cin >> inputName;
    filestream.open(inputName);
    while (!filestream)
    {
        cout << "File does not exist. Enter filename or type 'q' to quit.\n";
        cin >> inputName;
        if (inputName == "q")
        {
            return 1;
        }
        filestream.open(inputName);
    }
    *filestr = inputName;
    return 0;
}

void getStrVec(ifstream &filestream, vector<string> *vecStr)
{
    string substr;
    while (getline(filestream, substr))
    {
        if (substr.size() > 0)
        {
            (*vecStr).push_back(substr);
        }
    }
}

void getGrid(ifstream &filestream, vector<vector<uint8_t>> *vecGrid)
{
    char fileChar;
    uint64_t row = 0;
    (*vecGrid).push_back(vector<uint8_t>());
    while (filestream.get(fileChar))
    {
        if (isdigit(fileChar))
        {
            (*vecGrid)[row].push_back(stoi(&fileChar));
        }
        else
        {
            row++;
            (*vecGrid).push_back(vector<uint8_t>());
        }
    }
    (*vecGrid).pop_back();
}