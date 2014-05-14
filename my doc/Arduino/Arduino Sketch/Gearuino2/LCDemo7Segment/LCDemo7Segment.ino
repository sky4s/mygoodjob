//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12, 11, 10, 2);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 32;
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 15);
  lc.setScanLimit(0, 4);
  /* and clear the display */
  lc.clearDisplay(0);

  lc.shutdown(1, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(1, 15);
  lc.setScanLimit(1, 4);
  /* and clear the display */
  lc.clearDisplay(1);
}


void loop() {
  for (int x = 0; x <= 10; x++) {
    lc.setDigit(0, 0, x % 10, false);
    lc.setDigit(0, 1, (x + 1) % 10, false);
    delay(500);
  }
  for (int x = 0; x <= 10; x++) {
    lc.setDigit(1, 0, x % 10, false);
    lc.setDigit(1, 1, (x + 1) % 10, false);
    lc.setDigit(1, 2, (x + 2) % 10, false);
    lc.setDigit(1, 3, (x + 3) % 10, false);
    lc.setDigit(1, 4, (x + 4) % 10, false);
    delay(1000);
  }

  for (int x = 0; x <= 8; x++) {
    lc.setLed(0, 2, x, true);
    lc.setLed(0, 3, x, true);
    lc.setLed(0, 4, x, true);
    delay(1000);
    lc.clearDisplay(0);
  }
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

