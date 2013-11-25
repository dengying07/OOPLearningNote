#include "errorCheck.h"
/*
 * error: error index, according to errorCheck.h.
 *
 * errorChecked: output different error messages to standard error stream, and
 * exit the program with corresponding error index.
 */
void errorChecked(int error){
    switch(error){
    case 1:
        cerr << "Error : Insufficient number of parameters" << endl;
        break;
    case 2:
        cerr << "Error : Invalid input character" << endl;
        break;
    case 3:
        cerr << "Error : Invalid index" << endl;
        break;
    case 4:
        cerr << "Error : Non-numeric character" << endl;
        break;
    case 5:
        cerr << "Error : Impossible plugboard configuration" << endl;
        break;
    case 6:
        cerr << "Error : Incorrect number of plugboard parameters" << endl;
        break;
    case 7:
        cerr << "Error : Invalid rotor mapping" << endl;
        break;
    case 8:
        cerr << "Error : No rotor starting position" << endl;
        break;
    case 9:
        cerr << "Error : Invalid reflector mapping" << endl;
        break;
    case 10:
        cerr << "Error : Incorrect number of reflector parameters" << endl;
        break;
    case 11:
        cerr << "Error : Error opening configuration file" << endl;
        break;
    default:
        break;

    }
}
