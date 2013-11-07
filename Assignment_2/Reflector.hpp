#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP

#include <fstream>
#include <vector>
#include "errors.h"
#include "errorCheck.h"
#include "RfPgBase.hpp"

using namespace std; //for using vector library

class Reflector : public RfPgBase{

private:
    // override the base class's method. checks the errors and reads the file
    void initialize(char* file);

public:
    Reflector(char* file);

};

#endif //REFLECTOR_HPP

