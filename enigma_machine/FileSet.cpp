
#include "FileSet.hpp"

using namespace std;

FileSet::FileSet(int argc, char** argv){
    this->error = initialize(argc, argv);
    errorChecked(this->error);
}

/*
 * getPlugboardfile(): getter for file.
 */
char* FileSet::getPlugboardfile(){
    return this->plugBoardFile;
}

/*
 * getReflectorfile(): getter for file.
 */
char* FileSet::getReflectorfile(){
    return this->reflectorFile;
}

/*
 * getRotorsfile(): getter for file.
 */
vector<char*> &FileSet::getRotorsfile(){
    return this->rotorsFile;
}

/*
 * getStartpositionfile(): getter for file.
 */
char* FileSet::getStartpositionfile(){
    return this->startPositionFile;
}

/*
 * getInputFile(): getter for file.
 */
char* FileSet::getInputFile(){
    return this->inputFile;
}

/*
 * getOutputFile(): getter for file.
 */
char* FileSet::getOutputFile(){
    return this->outputFile;
}

/*
 * getError(): getter for error code
 */
int FileSet::getError(){
    return this->error;
}

/*
 * argc: parameter index from command input.
 * **argv: parameters from command input.
 *
 * initialize(): allocate the command input parameters to different files, also
 * check for any error relevant to parameters.
 */
int FileSet::initialize(int argc, char ** argv){

    if(argc >= 3){
        this->plugBoardFile = argv[1];
        this->reflectorFile = argv[2];

        // only reflector and plugboard file
        if(argc == 3){
            this->rotorsFile.clear();
            this->startPositionFile = NULL;
            return NO_ERROR;
        }

        // has at least one rotor file
        else if(argc > 4){
            for (int i = 0; i < argc - 4; i++){
                this->rotorsFile.push_back(argv[i + 3]);
            }
            this->startPositionFile = argv[argc - 1];
            return NO_ERROR;
        }

        // error: no position file
        else if(argc == 4){
            return INSUFFICIENT_NUMBER_OF_PARAMETERS;
        }
    }

    // do not have reflector or plugboard
    else{
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    return NO_ERROR;
}

