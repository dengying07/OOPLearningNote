#include "PlugBoard.hpp"

/*
 * file: input file from **argv. contains plugboard configuration.
 *
 * initialize(): overrides the base class's method. read from file and allocate
 * wirings, also check for any errors relevant to plugboard.
 */
void PlugBoard::initialize(char* file){
    ifstream wire(file);
    if(wire.fail()){
        errorChecked(ERROR_OPENING_CONFIGURATION_FILE);
        this->error = ERROR_OPENING_CONFIGURATION_FILE;
        return;
    }
    int count = 0;
    int left = -1; //preset the wirings, to check for errors
    int right = -1;
    while( wire >> left){
        count++;
        if(wire >> right && count <14);
        else{
            if(wiring[left] != left){ // report impossible config ahead of incorrect num.
                errorChecked(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
                this->error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
                return;
            }
            errorChecked(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
            this->error = INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
            return;
        }

        // preset value or set value(left-right, two cases) are acceptable, not any other value.
        if((wiring[left] != left && wiring[left] != right) || (wiring[right] != right && wiring[right] != left) || left == right){
            errorChecked(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
            this->error = IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
            return;
        }

        this->wiring[left] = right; // allocate the mappings
        this->wiring[right] = left;
    }
}

/*
 * constructor PlugBoard
 */
PlugBoard::PlugBoard(char* file)
    :RfPgBase(file){ //use the code of the base class constructor
    if(this->error != 0){
        return;
    }
    initialize(file);
}


