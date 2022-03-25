
/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-24
 */

#ifndef AOCLIB_V03_H
#define AOCLIB_V03_H

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/******************************************************************************/
/* FUNCTIONS */
/******************************************************************************/
namespace aocLib_v03
{
    /*!
     *  @brief      Function description
     *  @param      parameter description
     */
    void ExampleFunc(int parameter);

    /*!
     *  @brief      iostream prompt for file with warnings for "does not exist"
     *  @param      stream variable to modify
     */
    int LoadFile(std::ifstream & rFilestream);

    /*!
     *  @brief      iostream prompt for file with warnings for "does not exist"
     *  @param      filestream variable to modify
     *  @param      filestr modify string pointer
     */
    int LoadFile(std::ifstream & rFilestream, std::string & rFilestr);

    /*!
     *  @brief      get a vector of strings from each line of a filestream
     *  @param      filestream file to access
     *  @param      vecStr modify vector<string> pointer
     */
    void GetStrVec(std::ifstream & rFilestream, std::vector<std::string> & rVecStr);

    /*!
     *  @brief      get a 2D grid vector of uint8_t from a filestream
     *  @param      filestream file to access
     *  @param      vecGrid modify vector<vector<uint8_t>> pointer
     */
    void GetGrid(std::ifstream & rFilestream, std::vector<std::vector<uint8_t>> & rVecGrid);

    /*!
     *  @brief      plot a coordinate string to a vector
     *  @param      str coordinate pair
     *  @param      delim separator (usually ',')
     *  @param      rVecPlot vector to modify with plotted points
     */
    void PlotVec(string &str, char delim, std::vector<std::vector<uint16_t>> &rVecPlot);
}
#endif