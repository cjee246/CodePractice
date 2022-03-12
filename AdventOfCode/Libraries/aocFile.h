
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

#endif