#ifndef PLUGBOARD_HPP
#define PLUGBOARD_HPP

#include <fstream>
#include <vector>
#include "errorCheck.h"
#include "errors.h"
#include "RfPgBase.hpp"

using namespace std; //for vector library

class PlugBoard : public RfPgBase{

private:
    /* override the base class's method. checks the errors and reads the file*/
    void initialize(char* file);

public:
    PlugBoard(char* file);
};

#endif // PLUGBOARD_HPP
