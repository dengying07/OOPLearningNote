#include "Reflector.hpp"

/*
 * file: input file from **argv. contains reflector configuration.
 *
 * initialize(): implements the virtual method in the base class RfPgBase.
 */
void Reflector::initialize(char* file){
    ifstream wire(file);
    if(wire.fail()){
        errorChecked(ERROR_OPENING_CONFIGURATION_FILE);
        this->error = ERROR_OPENING_CONFIGURATION_FILE;
        return;
    }
    
    int count = 0;
    int right = -1;
    int left = -1;
    while(wire >> left){
        if(wire >> right);
        else{
            errorChecked(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
            this->error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
            return;
        }

        // if preset value or set(left-right) value, not any other value.
        if(right == left || wiring[left] != left || wiring[right] != right){
            errorChecked(INVALID_REFLECTOR_MAPPING);
            this->error = INVALID_REFLECTOR_MAPPING;
            return;
        }

        this->wiring[right] = left; //allocate the mapping
        this->wiring[left] = right;
        count ++;
    }

    // if not exact 13 pairs of mapping.
    if(count != 13){
        errorChecked(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
        this->error = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        return;
    }
}


/*
 * file: input file from **argv. contains reflector configuration.
 *
 * constructor Reflector: inherit the base class constructor.
 */
Reflector::Reflector(char* file)
    :RfPgBase(file){
    if(this->error != 0){
        return;
    }
    initialize(file);
}



