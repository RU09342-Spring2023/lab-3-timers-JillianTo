# How does the code work?
The P2.3 button's interrupt blinks a LED, and the LED chosen is the one that is currently not blinking. Only one of the LEDs is blinking at a time. The red LED on P1.0 blinks when the button is not pressed down and the green LED on P6.6 blinks while the button is being pressed down.

# How are the peripherals configured
P1.0 and P6.6 .are configured as outputs and output to LEDs on the microcontroller. P2.3 is configured as an input with a pull-up resistor and interrupt.

# What design considerations did you have to account for
I had to consider that a pull-up resistor goes from logic 1 to logic 0 when pressed, so I set P2.3's edge sensitivity to high->low, which would be against what is expected, which is for a button press to go from logic 0 to logic 1. Also, I had to toggle the edge sensitivity depending on the current state. For example, if the button is pressed, then the edge sensitivity has to be changed from high->low to low->high so that the interrupt occurs again when the button is released.

# How should a user use the code?
This code can be used with a MSP430FR2355 and shows how to use a button to toggle between different outputs.
