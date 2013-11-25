#include "RfPgBase.hpp"

/*
 * file: input file from **argv, stating the reflector/plugboard configurations.
 *
 * RfPgBase: constructor for this base class.
 */
RfPgBase::RfPgBase(char* file){
    this->error = 0;
    ifstream testForChar(file);
    if(testForChar.fail()){
        errorChecked(ERROR_OPENING_CONFIGURATION_FILE);
        this->error = ERROR_OPENING_CONFIGURATION_FILE;
        return;
    }

    int testChar;
    while(!testForChar.eof()){
         
        if(testForChar.fail()){
            errorChecked(NON_NUMERIC_CHARACTER);
            this->error = NON_NUMERIC_CHARACTER;
            return;
        }
        
        testForChar >> testChar;
       
        if(testChar > 25 || testChar < 0 ){
            errorChecked(INVALID_INDEX);
            this->error = INVALID_INDEX;
            return;
        }
    }
    initializeWithoutFile();
}

/*
 * initializeWithoutFile(): the default setting of wirings: every input gives
 * a same output.
 */
void RfPgBase::initializeWithoutFile(){
    for(int i=0; i<26; i++){
        this->wiring.push_back(i);
    }
}

/*
 * getWiredOutput(): find an output according to the wirings and the input.
 */
int RfPgBase::getWiredOutput(int sig){
    return this->wiring[sig];
}

/*
 * getError(): return error code.
 */
int RfPgBase::getError(){
    return this->error;
}

/*
 * virtual RfPgBase(): sub classes will have different implementation.
 */
void RfPgBase::initialize(){}
