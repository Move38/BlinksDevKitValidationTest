/*
   Blinks Dev-Kit
   Validation Test for Dev Kit Blinks
   4 modes for testing
   1. Verify RGB on all 6 faces together
   2. Verify RGB on each of the 6 faces individually
   3. Verify communication w/ awake neighbors
   4. Verify cold sleep (<0.2µA)
   by Jonathan Bobrow
   02.25.2020
*/

#include "Serial.h"

uint8_t sterileFlag=1; // Make this game sterile.

#define BLINKBIOS_SLEEP_NOW_VECTOR boot_vector12
// Calling BLINKBIOS_SLEEP_NOW_VECTOR() will immedeately put the blink into hardware sleep
// It can only wake up from a button press.
extern "C" void BLINKBIOS_SLEEP_NOW_VECTOR()  __attribute__((used)) __attribute__((noinline));

#define COLOR_DURATION_MS 1200
#define MESSAGE_DURATION_MS 250

enum Mode {
  DISPLAY_ALL,
  DISPLAY_PIXEL,
  DISPLAY_COMMS,
  GO_TO_SLEEP
};

Color colors[] = {RED, GREEN, BLUE};

byte mode = 0;
byte colorIndex = 0;
byte message = 1;

Timer colorSwitch;
Timer messageSwitch;
Timer longMessageSwitch;

boolean goto_sleep_flag = false;

ServicePortSerial Serial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( mode == GO_TO_SLEEP ) {

    BLINKBIOS_SLEEP_NOW_VECTOR();
    mode = DISPLAY_ALL;

  }

  if ( buttonPressed() ) {

    mode++;  // switch modes

    // No need to test for wrap here since we jump back to 1st mode (all) after last mode (sleep)

    Serial.print("Button pressed, updated mode to ");
    Serial.print(mode);
    Serial.println(" and serial printing confirmed :)");
  }

  switch (mode) {
    case DISPLAY_ALL:     displayAll();                   break;
    case DISPLAY_PIXEL:   displayPixel();                 break;
    case DISPLAY_COMMS:   displayComms();                 break;
    case GO_TO_SLEEP:     displaySleep();                 break;

  }

  // set color to white when button is pressed down
  if ( buttonDown() ) {
    // glow white to show we are down
    setColor(WHITE);
  }
}

void displayAll() {

  // switch colors every COLOR_DURATION_MS
  if ( colorSwitch.isExpired() ) {

    colorSwitch.set( COLOR_DURATION_MS );

    colorIndex = (colorIndex + 1) % COUNT_OF(colors);
  }

  // display the current color
  setColor( colors[colorIndex] );
}

void displayPixel() {

  // switch colors every COLOR_DURATION_MS
  if ( colorSwitch.isExpired() ) {

    colorSwitch.set( COLOR_DURATION_MS );

    colorIndex = (colorIndex + 1) % COUNT_OF(colors);
  }

  // display the current color
  byte index = (COLOR_DURATION_MS - colorSwitch.getRemaining()) / 200;
  setColor(OFF);
  setColorOnFace( colors[colorIndex], index);
}

void displayComms() {

  // reset display
  setColor(dim(WHITE, 64));

  // show received value
  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      setFaceColor(f, WHITE);
    }
  }

}

void displaySleep() {

  setColor(OFF);

}
