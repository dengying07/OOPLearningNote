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
    Reflector *mReflector; // to distinguish from the class Reflector.
    vector<Rotor*> mRotor; // to distinguish from the class Rotor.
	int error;
public:
    Machine(FileSet files);

    /* a signal flow through the machine just as the physical model */
    char signalFlow(char input);
    
	int getError();
};

#endif // MACHINE_HPP
