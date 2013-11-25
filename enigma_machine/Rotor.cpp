#include "Rotor.hpp"

/*
 * file: inputfile from the parameters **argv, containing a single string.
 * index: the number of this rotor. the rightmost rotor is number 0.
 *
 * Constructor: constructor for a single rotor; checks input for all
 * rotor-relevant errors.
 */
Rotor::Rotor(char* file,int index){
    this->numberOfRotor = index;
    this->leftRotor = NULL;
    this->rightRotor = NULL;
    this->position = 0;
    this->rotationFlag = false;
    this->rotatedFlag = false;
    this->startPosition = -1;
    this->error = 0;

    ifstream wire(file);
    if(wire.fail()){
        errorChecked(ERROR_OPENING_CONFIGURATION_FILE);
        this->error = ERROR_OPENING_CONFIGURATION_FILE;
        return;
    }

    /* begin the check for errors */
    // non-numeric character in rotors
    while(!wire.eof()){
        int testChar;
        if(wire.fail()){
            errorChecked(NON_NUMERIC_CHARACTER);
            this->error = NON_NUMERIC_CHARACTER;
            return;
        }
        wire >> testChar;

        if(testChar > 25 || testChar < 0){
            errorChecked(INVALID_INDEX);
            this->error = INVALID_INDEX;
            return;
        }
    }

    wire.clear();
    wire.seekg(0, wire.beg); // reuse the file pointer.

    //further error checking
    int count = 0;
    vector<int> testWireVector(50, -1);
    while(!wire.eof()&&count<50){
        int testWire = -1;
        wire >> testWire;
        if(testWire != -1){
            testWireVector[count] = testWire;
            count ++;
        }
    }// if more than 50 entries, the program will crash from (vector's)malloc.

    // if the rotor file exceeds or does not have enough in/out
    if( count < 26){
        errorChecked(INVALID_ROTOR_MAPPING);
        this->error = INVALID_ROTOR_MAPPING;
        return;
    }

    // if in/out connection not unique
    for(int i=0 ; i<26 ; i++){
        for(int j=i+1 ; j<26 ; j++){
            if(testWireVector[i] == testWireVector[j]){
                errorChecked(INVALID_ROTOR_MAPPING);
                this->error = INVALID_ROTOR_MAPPING;
                return;
            }
        }
    }

    wire.clear();
    wire.seekg(0, wire.beg); // reuse the pointer

    //allocate mapping from the file
    for(int i=0; i<26; i++){
        int read;
        wire >> read;
        wiring.push_back(read);
    }

    int notch;
    wire >> notch;
    this->turnover.push_back(notch);
    for(int i=0; !wire.eof(); i++){
        wire >> notch;
        this->turnover.push_back(notch);
    }

}

/*
 * ratate(): detailed change of this rotor when it rotates once.
 */
void Rotor::rotate(){
    this->rotationFlag = false; // flag of 'need to rotate'
    this->rotatedFlag = true; // flag of 'rotated'
    this->position = (this->position + 1) % 26; // clockwise rotation
}


/*
 * sig: a digital signal that is in the range of 0-25, conrrespindng to A-Z
 *
 * inputFlow(): deals with the input signal, change it into relative position
 * and then find corresponding output's absolute position and output this
 * signal. it also checks if this rotor has hit its notches, and if so, set a
 * flag in the next rotor for it to rotate before the signal flows into the next
 * rotor. the rotor always rotates before signal flows in.
 */
int Rotor::inputFlow(int sig){
    if(this->rightRotor == NULL || (this->rotationFlag == true && this->rightRotor->rotatedFlag == true)){
        rotate();
        if(this->rightRotor != NULL){
            this->rightRotor->rotatedFlag = false;
        }
    }
    else{
        // switch the 'rotated' flag so that the left rotor will not keep
        // rotating if this rotor stop at the notch for more than one input
        this->rotatedFlag = false;
    }
    if(this->leftRotor != NULL){
        for (int i=0; i<(int)this->turnover.size(); i++){

            //set or reset the left rotor every time the right rotor works
            if(position == this->turnover[i] ){
                this->leftRotor->setRotationFlag(); //send rotation flag to the left rotor
                break;
            }
            else{
                this->leftRotor->resetRotationFlag();
            }
        }
    }
    /*
     *change the input to relative position to get the output, and then
     * change the output back to absolute position */
    return (this->wiring[(sig + position) % 26 ] + 26 - position) % 26 ;

}


/*
 * sig: a digital signal that is in the range of 0-25, conrrespindng to A-Z
 *
 * outputFlow: similar to inputFlow(), but just check for output by reverse
 * finding the wiring. also it does not check for rotating conditions
 */
int Rotor::outputFlow(int sig){
    for(int i=0; i<26; i++){
        // find the output of the relative input
        if(this->wiring[i] == ((sig + position) % 26)){

            // change the ouput back to absolute position
            return ((i + 26 - position) % 26);
        }
    }
    return 0;
}

/*
 * Rotor: rotor class.
 * dir: a string containing the direction of "left" or "right"
 *
 * connectRotor(): this is a helper function for the public method of connect().
 */
void Rotor::connectRotor(Rotor* Rotor, char* dir){ //method for connection
    if(!strcmp(dir, "left")){
        this->leftRotor = Rotor;
    }
    else if(!strcmp(dir,"right")){
        this->rightRotor = Rotor;
    }
    else ; //never will happen.
}

/*
 * setRotationFlag(): the method for a connected rotor to call, to tell this rotor
 * to rotate as the connected rotor hit its notches.
 */
void Rotor::setRotationFlag(){
    this->rotationFlag = true;
}

/*
 * resetRotationFlag(): the method for a connected rotor to call, to tell this
 * rotor stop rotating if the connected rotor has not rotated for a signal
 * cycle: useful when there are more than 2 rotors connected. without it, the
 * leftmost rotor will definitely enter rotation when its right side rotor stops
 * at a notch.
 */
void Rotor::resetRotationFlag(){
    this->rotationFlag = false;
}

/*
 * connect(): public method for class Machine to call for machine setup.
 */
void Rotor::connect(Rotor* Rotor){ //call connectRotor to do a double linking
    this->connectRotor(Rotor, (char*)"left");
    this->leftRotor->connectRotor(this, (char*)"right");
}

/*
 * setRotatedFlag(): this method sets the value of the flag for a rotor rotated
 * during the last signal cycle. useful when there are more than 2 rotors
 * connected.
 */
void Rotor::setRotatedFlag(){
    this->rotatedFlag = true;
}

/*
 * getError(): return error code.
 */
int Rotor::getError(){
    return this->error;
}
