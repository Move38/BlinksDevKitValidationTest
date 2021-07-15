# Validation Test for Dev Kit Blinks

1. Validate RGB on all 6 faces together
2. Validate RGB on each of the 6 faces individually
3. Validate communication w/ awake neighbors
4. Validate cold sleep (<0.2µA)

Cycle RED, GREEN, BLUE to verify all 6 LEDs light
- look for equal brightness
- look for discreet light, i.e. no two colors should be on at the same time

Press button to switch modes
- When button is pressed down, the lights should glow WHITE (RGB together)

Individual mode
- a single R, G, or B LED lights up and cycles through all 6 faces
- continues to the next color in line and repeats
- makes it obvious if a single LED is faulty

Communication mode
- Low level white by default 
- when neighboring Blink is awake, it will glow bright white

Sleep mode
- instantly starts "cold sleep" requires button press to be woken
- cold sleep is reserved for ~10 minutes after warm sleep by default


A little bit of serial printing just in case we want to also look at what is executing via serial monitor
