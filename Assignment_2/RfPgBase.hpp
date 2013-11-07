#ifndef RFPGBASE_HPP
#define RFPGBASE_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include "errors.h"
#include "errorCheck.h"

using namespace std; //for using vector library

class RfPgBase{

protected:
    vector<int> wiring;

    // initialize() for constructor. it does nothing at this base class
    void initialize();

    // in case there is null input file, this method will load default settings.
    // reflector/plugboard will act as a short circuit, do nothing to input.
    // it is also the pre-setting for error checking and mapping.
    void initializeWithoutFile();

public:
    RfPgBase(char* file);

    // method to get a output according to the input signal
    int getWiredOutput(int sig);

};

#endif // RFPGBASE_HPP
