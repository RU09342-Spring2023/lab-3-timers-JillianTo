/*
 * Part2.c
 *
 *  Created on: Feb 11, 2023
 *  Revised on: Feb 15, 2023
 *      Author: Russell Trafford
 *      Author: Jillian To
 *
 *      This code will need to change the speed of an LED between 3 different speeds by pressing a button.
 */

#include <msp430.h>

char speed = 0;

void gpioInit();
void timerInit();

void main(){

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    gpioInit();
    timerInit();

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);

}


void gpioInit(){
    P6OUT &= ~BIT6; // reset P6.6 green LED
    P6DIR |= BIT6; // set P6.6 to output

    P2DIR &= ~BIT3; // set P2.3 to input
    P2REN |= BIT3; // enable P2.3 resistor
    P2OUT |= BIT3; // set P2.3 resistor to pull-up
    P2IES |= BIT3; // P2.3 High -> Low edge
    P2IE |= BIT3; // P2.3 interrupt enabled

}

void timerInit(){
    TB1CCTL0 = CCIE; // TBCCR0 interrupt enabled
    TB1CCR0 = 10000; // interrupt when timer counts to 50,000
    TB1CTL = TBSSEL_1 | MC_2 | ID_3; // ACLK, continuous mode

}


/*
 * INTERRUPT ROUTINES
 */

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3; // clear P2.3 interrupt flag

    switch(speed) {
    case 1: // medium speed, clock divider of 4
        TB1CTL &= ~BIT7; // change clock divider from 4 to 1
        speed--;
        break;
    case 2: // slowest speed, clock divider of 8
        TB1CTL &= ~BIT6; // change clock divider from 8 to 4
        speed--;
        break;
    default: // fastest speed, no clock divider
        TB1CTL |= ID_3; // set clock divider to 8
        speed=2;
        break;
    }

}


// Timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    P6OUT ^= BIT6; // toggle P6.6 LED
    TB1CCR0 += 10000; // change time to next interrupt
}


