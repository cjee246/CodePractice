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

using namespace std;

int main() {

    //read text file
    string inputName;
    ifstream inputFile;
    cout << "Enter filename.\n";
    cin >> inputName;
    inputFile.open(inputName);
    while (!inputFile) {
        cout << "File does not exist. Enter filename.\n";
        cin >> inputName;
        inputFile.open(inputName);
    }

    //loop through text file
    string line;
    uint32_t currVal = 0, lastVal = 0, count = 0;
    inputFile >> currVal;
    lastVal = currVal;
    while ( inputFile >> currVal ) {
        if (currVal > lastVal) {
            count++;
        }
        lastVal = currVal;
    }
    cout << count << '\n';
    return 0;
}