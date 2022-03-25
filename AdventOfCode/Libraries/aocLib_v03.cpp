
/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-24
 */

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include "aocLib_v03.h"
using namespace std;

/******************************************************************************/
/* FUNCTIONS */
/******************************************************************************/
namespace aocLib_v03
{
    /*!
     *  @brief      Function description
     *  @param      parameter description
     */
    void ExampleFunc(int parameter) {}

    int LoadFile(ifstream &rFilestream)
    {
        // read text file
        string inputName;
        cout << "Enter filename.\n";
        cin >> inputName;
        rFilestream.open(inputName);
        while (!rFilestream)
        {
            cout << "File does not exist. Enter filename or type 'q' to quit.\n";
            cin >> inputName;
            if (inputName == "q")
            {
                return 1;
            }
            rFilestream.open(inputName);
        }
        return 0;
    }

    int LoadFile(ifstream &rFilestream, string &rFilestr)
    {
        // read text file
        string inputName;
        cout << "Enter filename.\n";
        cin >> inputName;
        rFilestream.open(inputName);
        while (!rFilestream)
        {
            cout << "File does not exist. Enter filename or type 'q' to quit.\n";
            cin >> inputName;
            if (inputName == "q")
            {
                return 1;
            }
            rFilestream.open(inputName);
        }
        rFilestr = inputName;
        return 0;
    }

    void GetStrVec(ifstream &rFilestream, vector<string> &rVecStr)
    {
        string substr;
        while (getline(rFilestream, substr))
        {
            if (substr.size() > 0)
            {
                rVecStr.push_back(substr);
            }
        }
    }

    void GetGrid(ifstream &rFilestream, vector<vector<uint8_t>> &rVecGrid)
    {
        char fileChar;
        uint64_t row = 0;
        rVecGrid.push_back(vector<uint8_t>());
        while (rFilestream.get(fileChar))
        {
            if (isdigit(fileChar))
            {
                rVecGrid[row].push_back(stoi(&fileChar));
            }
            else
            {
                row++;
                rVecGrid.push_back(vector<uint8_t>());
            }
        }
        rVecGrid.pop_back();
    }

    void PlotVec(string &str, char delim, vector<vector<uint16_t>> &rVecPlot, bool invert)
    {
        stringstream strStream(str);
        string first, last;
        uint16_t *p1, *p2, x, y;
        getline(strStream, first, delim);
        getline(strStream, last);
        if (invert)
        {
            x = stoi(last);
            y = stoi(first);
        }
        else
        {
            y = stoi(last);
            x = stoi(first);
        }
        if (rVecPlot.size() < x + 1)
        {
            rVecPlot.resize(x + 1);
        }
        for (auto &yvec : rVecPlot)
        {
            if (yvec.size() < y + 1)
            {
                yvec.resize(y + 1);
            }
        }
        rVecPlot[x][y]++;
    }
}