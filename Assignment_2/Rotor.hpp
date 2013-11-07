#ifndef ROTOR_HPP
#define ROTOR_HPP

#include <vector>
#include <fstream>
#include <cstring>
#include "errors.h"
#include "errorCheck.h"

using namespace std; //for using vector library

class Rotor{ 
private:

    vector<int> wiring;
    vector<int> turnover;
    int position;
    Rotor* leftRotor;
    Rotor* rightRotor;
    int numberOfRotor;  //attribute for testing, can be deleted

    bool rotationFlag;

    // flag to control the rotation: only once when the right rotor is at a notch
    bool rotatedFlag;

    // method for constructor to call
    void initialize(char* file);

    // function to connect two rotors together
    void connectRotor(Rotor* Rotor, char* dir);

public:

    int inputFlow(int sig);
    int outputFlow(int sig);
    int startPosition;

    // constructor: default settings as no other rotors linked, start position at -1
    Rotor(char* file,int index);

    // connect two rotors by setting the left and right pointer of each
    void connect(Rotor* Rotor);

    // a flag checking the rotation: if it should rotate, set to 1
    void setRotationFlag();

    void resetRotationFlag();

    // a flag checking the rotation: if rotation done, reset to 0
    void setRotatedFlag();

    // do a rotation: position adds one, and set/reset rotation flag
    void rotate();

};

#endif // ROTOR_HPP
