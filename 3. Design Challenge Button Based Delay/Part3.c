/*
 * Part3.c
 *
 *  Created on: Feb 15, 2023
 *      Author: Jillian To
 *
 */

#include <msp430.h>

#define DEFAULT_TIMER_COUNT 100

char timerSet = 0; // 0 to blink at defined speed, 1 to turn off LED and record new blink time
int timerCount = DEFAULT_TIMER_COUNT; // default value for timer to count to

void gpioInit();
void timerInit();

void main() {

	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
	
	gpioInit();
	timerInit();

	PM5CTL0 &= ~LOCKLPM5; // disable GPIO power-on default high-impedance mode to activate previously configured port settings
	
	__bis_SR_register(LPM3_bits | GIE);

	while(1) {
			
	}

}

void gpioInit() {
	P1OUT &= ~BIT0; // reset P1.0 red LED
	P1DIR |= BIT0; // set P1.0 to output 
	
	P2DIR &= ~BIT3; // set P2.3 to input
	P2REN |= BIT3; // enable P2.3 resistor
	P2OUT |= BIT3; // set P2.3 resistor to pull-up
	P2IES &= ~BIT3; // P2.3 Low -> High edge
	P2IE |= BIT3; // P2.3 interrupt enable

	P4DIR &= ~BIT1; // set P4.1 to input
	P4REN |= BIT1; // enable P4.1 resistor
	P4OUT |= BIT1; // set P4.1 resistor to pull-up
	P4IES &= ~BIT1; // P4.1 Low -> High edge
	P4IE |= BIT1; // P4.1 interrupt mode

}

void timerInit() {
	TB1CCTL0 = CCIE; // TBCCR0 interrupt enabled
	TB1CCR0 = timerCount; // interrupt after timer counts to value in timerCount
	TB1CTL = TBSSEL_1 | MC_2 | ID_3; // ACLK, continuous mode

}

// port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
	P2IFG &= ~BIT3; // clear P2.3 interrupt flag
	if(timerSet) {
		timerSet = 0;
		P2IES |= BIT3; // P2.3 Low -> High edge
	} else {	
		timerSet = 1;
		timerCount = 0; // reset timerCount for new timerCount value
		P2IES &= ~BIT3; // P2.3 High -> Low edge
	}

}

// port 4 interrupt service routine
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void) {
    P4IFG &= ~BIT1; // clear P4.1 interrupt flag
    timerCount = DEFAULT_TIMER_COUNT; // set timerCount to default value
}

// timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void) {
	P1OUT ^= BIT0; // blink LED
	TB1CCR0 += timerCount; // increment time to next interrupt
	if(timerSet)
	    timerCount++; // if P2.3 is continuing to be pressed, increment the timerCount
}



