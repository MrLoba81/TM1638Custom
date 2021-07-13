#ifndef TM1638CUSTOM_h
#define TM1638CUSTOM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <TM1638QYF.h>
const byte OVERRIDDEN_ERROR_DATA[] = {
  0b01111001, // E
  0b01010000, // r
  0b01010000, // r
  0,
  0b01111001, // E
  0b01010000, // r
  0b01010000, // r  
  0
};

enum StatusBarEnum {
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3
};

class TM1638Custom : public TM1638QYF
{
    public:
        TM1638Custom(byte dataPin, byte clockPin, byte strobePin);
        void setStatusBar(StatusBarEnum status);
        void setPercentage(uint8_t percentage);
        virtual void clearDisplay();
        virtual void setDisplayToError();
        // From an idea by Gavin Lyons
        // https://github.com/gavinlyonsrepo/TM1638plus
        // Divides the display into two nibbles and displays a Decimal number in each
        void displayDecNumNibble(uint16_t numberUpper, uint16_t numberLower, boolean leadingZeros = false);
        void displayDecNumNibble(uint16_t  numberUpper, uint16_t numberLower, uint8_t dotUpper, uint8_t dotLower, boolean leadingZeros = false);
    
    private:
        void reset();
};
#endif