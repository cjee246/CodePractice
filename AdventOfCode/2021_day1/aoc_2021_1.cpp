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
    string inputFile;
    ifstream input;
    cout << "Enter filename.\n";
    cin >> inputFile;
    input.open(inputFile);
    while (!input) {
        cout << "File does not exist. Enter filename.\n";
        cin >> inputFile;
        input.open(inputFile);
    }

    return 0;
}