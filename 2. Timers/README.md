# How does the code work?
There is a switch statement in the interrupt for the P2.3 button that defines the clock divider used for each case. Each case will switch the case read for the next P2.3 interrupt. The clock divider determines how many clock cycles it takes for the B1 timer to interrupt, and the LED is toggled during that interrupt.

# How are the peripherals configured
P2.3 is configured as an input with a pull-up resistor and interrupt. P6.6 is configured as an output and is connected to a green LED on the microcontroller.

# What design considerations did you have to account for
To switch between different blink speeds, I chose to use a clock divider. There could be problems if I needed to control other peripherals with the B1 timer, as it would have been slowed down with the clock divider. Also, a clock divider is not entirely effcient since the extra clock cycles that are being divided is wasted energy. It would be more efficient to look into slower clocks.

# How should a user use the code?
This code can be uploaded to a MSP430FR2355 and can serve as the basis for LED implementations that need variable light blinking speeds.
