#ifndef FILESET_HPP
#define FILESET_HPP

#include <vector>
#include "errors.h"
#include "errorCheck.h"
#include <cstring>

using namespace std; //for using vector library

class FileSet{

private:
    char* plugBoardFile;
    char* reflectorFile;
    vector<char*> rotorsFile;
    char* startPositionFile;
    char* inputFile; // may not exist, then input from the terminal
    char* outputFile; // output to file in the same directory
	int error;

    /* for the constructor to call */
    int initialize(int argc, char ** argv);

public:

    FileSet(int argc, char** argv);

    char* getPlugboardfile();
    char* getReflectorfile();
    vector<char*> &getRotorsfile();//to avoid vector copying, pass by reference.
    char* getStartpositionfile();
    char* getInputFile();
    char* getOutputFile();
	int getError();
};

#endif // FILESET_HPP
