// Overgenomen uit het TicTacToe voorbeeld
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef arcadeUtils_H
#define arcadeUtils_H

#include <map>
#include <iostream>

const std::map<const std::string, std::pair<int, int>> directions = 
    {{"OMHOOG",{0,1}}, {"OMLAAG",{0,-1}}, {"LINKS",{-1,0}}, {"RECHTS",{1,0}}};

bool isDirection(std::string direction);

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);


// Closing of the ``header guard''.
#endif
