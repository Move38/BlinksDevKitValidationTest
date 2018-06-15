# Validation Test for Dev Kit Blinks

1. Validate RGB LEDs
2. Validate Button
3. Validate IR Comms

Cycle RED, GREEN, BLUE to verify all 6 LEDs light
- look for equal brightness
- look for discreet light, i.e. no two colors should be on at the same time

Press button to switch modes
When button is pressed down, the lights should glow WHITE (RGB together)

Communication mode
Dark by default 
when neighboring Blink is in Communication mode, show CYAN and MAGENTA data

Hold button until YELLOW to enter send mode
Send Mode is for surrounding Blinks to be used to test a single Blink
Shows YELLOW on sides without Blinks attached
Show CYAN and MAGENTA for Blink attached

A little bit of serial printing just in case we want to also look at what is executing via serial monitor
