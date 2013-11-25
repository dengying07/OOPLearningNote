/*********************************************
 * Auther: Ying Deng
 * Department: Computer Science
 * University: Imperial College London
 * Completion date: 06/11/2013
 *********************************************
 *
 * Notes for users:
 *
 * 1. Please be reminded that this machine will need to have exactly one
 * reflector, andone plugboard. If you want to use a defualt setting for no
 * plugboard/reflector switching signals, please input 'null.pg' and 'null.rf'.
 *
 * 2. Please notice that you can have unlimited or no rotors, but you will need
 * to provide a start position file if there is at least one rotor. Only
 * providing a rotor file or a position file without rotor will cause the
 * machine to crash. Also the position file will need to have enough starting
 * positions. more is OK but less will cause a error report.
 *
 * 3. This machine is set to allow only the input parameter sequence of .pg,
 * .rf, (.rot), (.pos) any attempt to input a wrong sequence of parameters
 * will result in unexpected errors or outputs.
 *
 * 4. This machine can either read from terminal or file, for the first choice
 * just give it normal parameters without redirecting its input/output. For the
 * seconde choice just use "< input_file.txt" and "> output_file.txt" to do so.
 *
 **********************************************/


#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

#include "errors.h"
#include "errorCheck.h"
#include "IOBoard.h"
#include "FileSet.hpp"
#include "Machine.hpp"
#include "Rotor.hpp"
#include "Reflector.hpp"
#include "PlugBoard.hpp"

using namespace std;

/*
 ./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
 --args enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
 ../plugboards/I.pb ../reflectors/I.rf ../rotors/I.rot ../rotors/II.rot ../rotors/III.rot ../rotors/I.pos
./enigma plugboards/III.pb reflectors/V.rf rotors/VI.rot rotors/VII.rot rotors/VIII.rot rotors/I.pos < input.txt > output.txt
 --args enigma test/pb.pb test/rf.rf test/rot.rot test/pos.pos
*/

int main(int argc, char** argv){
    int error_code = 0;
    FileSet files = FileSet(argc, argv);
    if(files.getError() != 0){
        return (files.getError());
    }
    Machine machineU = Machine(files);
    if(machineU.getError() != 0){;
        return (machineU.getError());
    }
    char inU;
    string inputU;
    cin >> ws;
    cin >> inputU;

    // do input once first, so that while loop can work normally.
    inU = inputU[0];
    int i = 0;
    while(inU != '\0' && inU!= ' '){
        if(int(inU) < 91 && (int)inU > 64){

            char signal = machineU.signalFlow(inU);
            cout << signal;
            i++;
            inU = inputU[i];
        }
        else{
            // check for valid input: A-Z only.
            errorChecked(INVALID_INPUT_CHARACTER);
            return(INVALID_INPUT_CHARACTER);
        }
    }

    // read input in loop, ignoring any space or carriage return.
    cin >> inputU;
    while(!cin.eof()){  //CTRL + D to exit input
        inU = inputU[0];
        int j = 0;
        while(inU != '\0' && inU!= ' '){
            if(int(inU) < 91 && (int)inU > 64){

                char signal = machineU.signalFlow(inU);
                cout << signal;
                j++;
                inU = inputU[j];
            }
            else{
                errorChecked(INVALID_INPUT_CHARACTER);
                return(INVALID_INPUT_CHARACTER);
            }
        }
        cin >> inputU;
    }
    return (error_code);
}

