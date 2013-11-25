#include "RfPgBase.hpp"
#include "Machine.hpp"

/*
 * files: a pre-set class for the input parameters. containing a plugboard file,
 * a reflector file, arbitrary rotor/start-position files.
 *
 * constructor Machine
 */
Machine::Machine(FileSet files){
    this->error = 0;
    this->mPlugBoard = new PlugBoard(files.getPlugboardfile());
    if(mPlugBoard->getError() != 0){
        this->error = mPlugBoard->getError();
        delete this->mPlugBoard;
        return;
    }
    for(int i=0; i < (int)files.getRotorsfile().size(); i++){
        this->mRotor.push_back(NULL);
    }

    for(int i=0; i < (int)files.getRotorsfile().size(); i++){
        int sizeR = files.getRotorsfile().size() - 1 - i;
        //the first file will go last, and the last file will go first(NO.0 rotor)
        mRotor[i] = (new Rotor(files.getRotorsfile()[sizeR], i)); //make a rotor
        if(mRotor[i]->getError() != 0){
            this->error = mRotor[i]->getError();
            delete this->mPlugBoard;
            for(int j=0; j <= i; j++){
                delete this->mRotor[j]; // delete the vector space one by one.
            }
            return;
        }
        if(i > 0 && i < (int)files.getRotorsfile().size() -1){
            mRotor[i-1]->connect(mRotor[i]);  //function to assemble rotors
        }
        else if (i>0 && i == (int)files.getRotorsfile().size() -1){
            mRotor[i-1]->connect(mRotor[i]);
        }
    }
    this->mReflector = new Reflector(files.getReflectorfile());
    if(mReflector->getError() != 0){
        this->error = mReflector->getError();
        delete this->mPlugBoard;
        delete this->mReflector;

        for(int i=0; i< (int)this->mRotor.size(); i++){
            delete this->mRotor[i]; // delete the vector space one by one.
        }
        this->mRotor.clear();
        return;
    }

    //set start positions of rotors by rotating them
    if(files.getRotorsfile().size() != 0){
        if(files.getStartpositionfile()){
            fstream startPos;
            startPos.open(files.getStartpositionfile());
            if(startPos.fail()){
                errorChecked(ERROR_OPENING_CONFIGURATION_FILE);
                this->error = ERROR_OPENING_CONFIGURATION_FILE;
                delete this->mPlugBoard;
                delete this->mReflector;
                for(int i=0; i< (int)this->mRotor.size(); i++){
                    delete this->mRotor[i]; // delete the vector space one by one.
                }
                return;
            }
            char testC;
            while(startPos >> testC){
                if(testC != ' ' && ((int)testC > 57 || (int)testC < 48)){
                    errorChecked(NON_NUMERIC_CHARACTER);
                    this->error = NON_NUMERIC_CHARACTER;
                    delete this->mPlugBoard;
                    delete this->mReflector;
                    for(int i=0; i< (int)this->mRotor.size(); i++){
                        delete this->mRotor[i]; // delete the vector space one by one.
                    }
                    return;
                }
            }

            startPos.clear();
            startPos.seekg(0, startPos.beg); // reuse the file pointer.

            for (int i=(int)this->mRotor.size()-1; i>-1 &&!startPos.eof() ; i--){
                int startPosition = -1;

                startPos >> startPosition;
                // an non-integer input causing a failed bit
                if(startPos.fail()){
                    errorChecked(NO_ROTOR_STARTING_POSITION);
                    this->error = NO_ROTOR_STARTING_POSITION;
                    delete this->mPlugBoard;
                    delete this->mReflector;
                    for(int i=0; i< (int)this->mRotor.size(); i++){
                        delete this->mRotor[i]; // delete the vector space one by one.
                    }
                    return;
                }
                // start position out of range
                if (startPosition > 25 || startPosition < 0){
                    errorChecked(INVALID_INDEX);
                    this->error = INVALID_INDEX;
                    delete this->mPlugBoard;
                    delete this->mReflector;
                    for(int i=0; i< (int)this->mRotor.size(); i++){
                        delete this->mRotor[i]; // delete the vector space one by one.
                    }
                    return;
                }
                this->mRotor[i]->startPosition = startPosition;
                for(int j=0; j< mRotor[i]->startPosition; j++){
                    mRotor[i]->rotate();
                }
            }
        }
    }
}

/*
 * input: an input charactor, limited to A-Z only
 *
 * signalFlow(): put the signal into this machine and get a ouput. it flows
 * sequentially according to the physical model of the machine.
 */
char Machine::signalFlow(char input){
    int sig = getDigit(input);
    //cout << " " << sig << " "; // most useful debug outputs: kept in case
    sig = this->mPlugBoard->getWiredOutput(sig);
    //cout << " plugboard " << sig <<" ";
    for (size_t i=0; i< this->mRotor.size(); i++){
        sig = this->mRotor[i]->inputFlow(sig);
        //  cout << sig << " ";
    }
    sig = this->mReflector->getWiredOutput(sig);
    //cout << "reflection "<< sig<<" ";
    for(int j=this->mRotor.size()-1; j>=0; j--){
        sig = this->mRotor[j]->outputFlow(sig);
        //  cout <<  sig<< " " ;
    }
    sig = this->mPlugBoard->getWiredOutput(sig);
    //cout << "plugboard " << sig << " ";
    char output = getSignal(sig);
    return output;
}


/*
 * getError(): getter for error code
 */
int Machine::getError(){
    return this->error;
}
