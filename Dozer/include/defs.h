#ifndef PIN_CONFIGURATIONS_H
#define PIN_CONFIGURATIONS_H

#include <Arduino.h>






const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3', '4'},
    {'4','5','6', '4'},
    {'7','8','9', '4'},
    {'*','0','#', '4'}
}; 

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad





#endif