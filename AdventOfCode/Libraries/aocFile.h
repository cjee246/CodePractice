
/*
 * Author: Calvin Jee
 * Email: cjee246@gmail.com
 *
 * Date: 2022-03-11
 */

#ifndef AOCFILE_H
#define AOCFILE_H

/******************************************************************************/
/* HEADER FILES */
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>

/******************************************************************************/
/* FUNCTIONS */
/******************************************************************************/

/*!
 *  @brief      Function description
 *  @param      parameter description
 */
void exampleFunc(int parameter);

/*!
 *  @brief      iostream prompt for file with warnings for "does not exist"
 *  @param      stream variable to modify
 */
int loadFile(std::ifstream &filestream);

/*!
 *  @brief      iostream prompt for file with warnings for "does not exist"
 *  @param      filestream variable to modify
 *  @param      filestr modify string pointer
 */
int loadFile(std::ifstream &filestream, std::string *filestr);

/*!
 *  @brief      get a vector of strings from each line of a filestream
 *  @param      filestream file to access
 *  @param      vecStr modify vector<string> pointer
 */
void getStrVec(std::ifstream &filestream, std::vector<std::string> *vecStr);

#endif