#include <TM1638Custom.h>

const uint8_t strobe = 7;
const uint8_t clock = 9;
const uint8_t data = 8;

TM1638Custom disp(data, clock, strobe);

void setup() {}

void loop() {
  disp.clearDisplay();
  delay(500);

  disp.displayDecNumNibble(1234, 4321);
  delay(1000);
  disp.displayDecNumNibble(1234, 4321, 1, 8, false);
  delay(1000);
  disp.displayDecNumNibble(1234, 4321, 2, 4);
  delay(1000);
  disp.displayDecNumNibble(1234, 4321, 4, 2);
  delay(1000);
  disp.displayDecNumNibble(1234, 4321, 8, 1, false);
  delay(1000);
  
  disp.clearDisplay();
  delay(500);

  disp.displayDecNumNibble(34, 12, true);
  delay(1000);

  disp.setPercentage(25);
  delay(500);
  disp.setPercentage(50);
  delay(500);
  disp.setPercentage(75);
  delay(500);
  disp.setPercentage(100);
  delay(1000);
  disp.setPercentage(0);

  disp.setStatusBar(ZERO);
  delay(500);
  disp.setStatusBar(ONE);
  delay(500);
  disp.setStatusBar(TWO);
  delay(500);
  disp.setStatusBar(THREE);
  delay(1000);

  disp.setDisplayToError();
  delay(1000);
}