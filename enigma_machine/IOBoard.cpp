#include "IOBoard.h"

/* getDigit():change input charactor into digital:to model the machine better.*/
int getDigit(char signal){
    return int(signal)-65;
}

/* getSignal(): change output digital signal into charactor. */
char getSignal(int digit){
    return char(digit+65);
}
