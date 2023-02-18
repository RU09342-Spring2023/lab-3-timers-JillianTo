# How does the code work?
This code uses interrupts with the P2.3 button to signal the blink period is going to be set and with the P4.1 button to reset the blink period to a default value. The red LED on P1.0 is blinked according to the set value. Timer B1 interrupts every 8 clock cycles (which was done using the ID_3 clock divider) to blink the LED, and if the P2.3 button was pressed and not released yet, then it will increment the global timerCount variable. When the P2.3 button is let go, then the P2 interrupt is triggered to unset the global timerSet variable, which tells the next Timer B1 interrupt to not modify timerCount anymore.
# How are the peripherals configured
The only peripherals used were ones included on the board. P2.3 and P4.1 were set as inputs and had their interrupts enabled. P1.0 was set as an output.
# What design considerations did you have to account for
I had to account for timer rollover by incrementing the time that the timer would interrupt at, being TB1CCR0, by my timerCount global variable. I also had to use a /8 clock divider so that a larger period of time could be stored for the LED blink period, but this reduces the accuracy of the period. Instead of having the blink period accurate to the microsecond, as it would have been without a clock divider, it is only accurate to the eighth microsecond.
# How should a user use the code?
This code can turn the MSP430FR2355 into a dynamic metronome, as the user can define the blink period to a desired value and use it to time repetitive actions.
