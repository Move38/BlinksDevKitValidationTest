/*
   Blinks Dev-Kit

   Validation Test for Dev Kit Blinks

   1) Validate RGB LEDs
   2) Validate Button
   3) Validate IR Comms

   Cycle RED, GREEN, BLUEto verify all 6 LEDs light
   - look for equal brightness
   - look for discreet light, i.e. no two colors should be on at the same time

   Press button to switch modes
   When button is pressed down, the lights should glow WHITE (RGB together)

   Communication mode is dark by default, 
   When neighboring Blink is in Communication mode, show CYAN and MAGENTA data

   Hold button until YELLOW to enter send mode
   Send Mode is for surrounding Blinks to be used to test a single Blink
   Shows YELLOW on sides without Blinks attached
   Show CYAN and MAGENTA for Blink attached

   A little bit of serial printing just in case we want to also look at what is executing via serial monitor

   by Jonathan Bobrow
   05.10.2018
*/

#include "Serial.h"


#define COLOR_DURATION_MS 500
#define MESSAGE_DURATION_MS 250
#define LONG_MESSAGE_DURATION_MS 500

enum Mode {
  DISPLAY,
  COMMS,
  SENDMODE
};

Color colors[] = {RED, GREEN, BLUE};

byte mode = 0;
byte colorIndex = 0;
byte message = 1;

Timer colorSwitch;
Timer messageSwitch;
Timer longMessageSwitch;

ServicePortSerial Serial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( buttonPressed() ) {

    Serial.println("Button pressed, serial printing confirmed :)");

    // switch modes
    mode++;

    if (mode >= 2) {
      mode = 0;
    }
  }

  if ( buttonLongPressed() ) {

    Serial.println("Button long pressed. Entering only send mode");

    // switch modes
    mode = SENDMODE;
  }

  if ( mode == DISPLAY ) {

    // make sure the message on all sides is 0
    setValueSentOnAllFaces(0);

    // switch colors every COLOR_DURATION_MS
    if ( colorSwitch.isExpired() ) {

      colorSwitch.set( COLOR_DURATION_MS );

      colorIndex = (colorIndex + 1) % COUNT_OF(colors);
    }

    // display the current color
    setColor( colors[colorIndex] );
  }

  if ( mode == COMMS ) {

    // send
    if ( messageSwitch.isExpired() ) {

      messageSwitch.set( MESSAGE_DURATION_MS );

      message = (message % 2) + 1;

    }

    setValueSentOnAllFaces( message );

    // reset display
    setColor(OFF);

    // show received value
    FOREACH_FACE(f) {
      if (!isValueReceivedOnFaceExpired(f)) {

        byte faceValue = getLastValueReceivedOnFace(f);

        if ( faceValue == 1 ) {
          setFaceColor(f, MAGENTA);
        }
        else if ( faceValue == 2 ) {
          setFaceColor(f, CYAN);
        }
      }
    }

  }

  // set color to white when button is pressed down
  if ( buttonDown() ) {
    // glow white to show we are down
    setColor(WHITE);
  }

  
  if ( mode == SENDMODE ) {

    // send
    if ( longMessageSwitch.isExpired() ) {

      longMessageSwitch.set( LONG_MESSAGE_DURATION_MS );

      message = (message % 2) + 1;

    }

    setValueSentOnAllFaces( message );

    // reset display
    setColor(YELLOW);

    // show sending value
    FOREACH_FACE(f) {
      if (!isValueReceivedOnFaceExpired(f)) {

        if ( message == 1 ) {
          setFaceColor(f, MAGENTA);
        }
        else if ( message == 2 ) {
          setFaceColor(f, CYAN);
        }
      }
    }

  }
}
