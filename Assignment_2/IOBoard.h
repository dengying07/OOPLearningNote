#ifndef IOBOARD_H
#define IOBOARD_H

// get a input character and return a integer for input to the machine
int getDigit(char signal);

// change the ouput of the machine back to character
char getSignal(int digit);

#endif // IOBOARD_H
