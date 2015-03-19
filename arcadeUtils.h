// Overgenomen uit het TicTacToe voorbeeld
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef arcadeUtils_H
#define arcadeUtils_H


#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);


// Closing of the ``header guard''.
#endif
