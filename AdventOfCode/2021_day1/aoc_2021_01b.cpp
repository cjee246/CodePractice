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

using namespace std;

int main()
{

    // read text file
    string inputName;
    ifstream inputFile;
    cout << "Enter filename.\n";
    cin >> inputName;
    inputFile.open(inputName);
    while (!inputFile)
    {
        cout << "File does not exist. Enter filename.\n";
        cin >> inputName;
        inputFile.open(inputName);
    }

    // init sliding window
    uint32_t currVal = 0, lastVal = 0, count = 0;
    vector<uint32_t> vec(3, 0);
    inputFile >> vec[0] >> vec[1] >> vec[2];
    lastVal = vec[0] + vec[1] + vec[2];

    // loop through sliding window
    while (inputFile >> vec[2])
    {
        currVal = vec[0] + vec[1] + vec[2];
        if (currVal > lastVal)
        {
            count++;
        }
        lastVal = currVal;
        rotate(vec.begin(), vec.begin() + 1, vec.end());

    }
    cout << count << '\n';
    return 0;
}