#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "TM1638Custom.h"

TM1638Custom::TM1638Custom(byte dataPin, byte clockPin, byte strobePin)
    : TM1638QYF(dataPin, clockPin, strobePin, true, 0)
{
}

void TM1638Custom::displayDecNumNibble(uint16_t numberUpper, uint16_t numberLower, boolean leadingZeros) {
    this->displayDecNumNibble(numberUpper, numberLower, 0, 0, leadingZeros);
}

void TM1638Custom::displayDecNumNibble(uint16_t numberUpper, uint16_t numberLower, uint8_t dotUpper, uint8_t dotLower, boolean leadingZeros)
{
    char valuesUpper[this->displays + 1];
    char valuesLower[this->displays / 2 + 1];
    snprintf(valuesUpper, this->displays / 2 + 1, leadingZeros ? "%04d" : "%d", numberUpper);
    snprintf(valuesLower, this->displays / 2 + 1, leadingZeros ? "%04d" : "%d", numberLower);
    strcat(valuesUpper, valuesLower);
    this->setDisplayToString(valuesUpper, (dotUpper << 4) | dotLower);
}

void TM1638Custom::setStatusBar(StatusBarEnum status)
{
    //Starts from 0x09 GRID5 - SEG9 segment E
    for (uint8_t i = 0; i < 4; i++)
    {
        uint16_t addr = 0x09 + (i * 2);
        sendData(addr, addr == (uint16_t)(0x09 + (status * 2)) ? 1 : 0);
    }
}

void TM1638Custom::setPercentage(uint8_t percentage)
{
    byte data;
    byte adr = 0x07;

    if (percentage >= 0 && percentage < 25)
    {
        data = 0x00;
    }
    else if (percentage >= 25 && percentage < 50)
    {
        data = 0x01;
    }
    else if (percentage >= 50 && percentage < 75)
    {
        data = 0x03;
    }
    else if (percentage >= 75 && percentage < 100)
    {
        data = 0x07;
    }
    else
    {
        data = 0xF;
    }

    for (uint8_t j = 0; j < 4; j++)
    {
        sendData(adr, data & 0x01);
        data = data >> 1;
        adr -= 2;
    }
}

void TM1638Custom::clearDisplay()
{
    this->reset();
}

void TM1638Custom::reset()
{
    sendCommand(0x40); // set auto increment mode

    digitalWrite(this->strobePin, LOW);
    shiftOut(this->dataPin, this->clockPin, LSBFIRST, 0xc0); // set starting address to 0
    for (uint8_t i = 0; i < 16; i++)
    {
        shiftOut(this->dataPin, this->clockPin, LSBFIRST, 0x00);
    }
    digitalWrite(this->strobePin, HIGH);
}

void TM1638Custom::setDisplayToError()
{
    clearDisplay();
    setDisplay(OVERRIDDEN_ERROR_DATA, 8);
}