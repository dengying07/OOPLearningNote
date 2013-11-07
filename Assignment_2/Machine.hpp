#ifndef MACHINE_HPP
#define MACHINE_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include "errorCheck.h"
#include "errors.h"
#include "IOBoard.h"
#include "FileSet.hpp"
#include "PlugBoard.hpp"
#include "Reflector.hpp"
#include "Rotor.hpp"

using namespace std; //for using vector library

class Machine{

private:
    PlugBoard *mPlugBoard; // to distinguish from the class PlugBoard.
    Reflector *mReflector;
    vector<Rotor*> mRotor;
public:
    Machine(FileSet files);
    ~Machine();

    // a signal flow through the machine just as the physical model
    char signalFlow(char input);
};

#endif // MACHINE_HPP
