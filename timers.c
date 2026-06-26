/*
 * description: includes timer configurations and interrupts for ticks and adc
 * timers.c
 * Sai Nelluri
 * September 2025
 */

#include "msp430.h"
#include "macros.h"
#include <string.h>
#include "functions.h"
#include "LCD.h"
#include "ports.h"
#include "wheels.h"

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
#define TB0CCR0_INTERVAL   (25000)
#define TB0CCR1_INTERVAL   (25000)
#define TB0CCR2_INTERVAL   (25000)


volatile unsigned int Time_Sequence = 0;
volatile char one_time;
volatile unsigned int Time_Counter = 0;
extern volatile unsigned int update_display;
volatile unsigned int ADC_Channel = 0;
volatile unsigned int ADC_Left_Detect;
volatile unsigned int ADC_Right_Detect;
volatile unsigned int ADC_Thumb_Wheel;
volatile unsigned int elapsed_time_ticks;
volatile unsigned int ping_timer_ticks;
volatile unsigned int overflow_counter = 0;
extern unsigned int DAC_data;
int counts = 0;


void Init_Timers(void){
    Init_Timer_B0();
    //Init_Timer_B1();
    //Init_Timer_B2();
    Init_Timer_B3();
}


//------------------------------------------------------------------------------
// Function: Init_Timer_B0
// Description: Initializes Timer B0 for continuous mode operation with
//              CCR0, CCR1, and CCR2 interrupt support.
//------------------------------------------------------------------------------
void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK;          // SMCLK source
    TB0CTL |= TBCLR;                 // Reset TB0R, clock divider, count direction
    TB0CTL |= MC__CONTINOUS;         // Continuous mode
    TB0CTL |= ID__8;                 // Divide clock by 8

    TB0EX0 = TBIDEX__8;              // Divide clock by an additional 8

    TB0CCR0 = TB0CCR0_INTERVAL;      // Set CCR0 interval
    TB0CCTL0 |= CCIE;                // Enable CCR0 interrupt

    //TB0CCR1 = TB0CCR1_INTERVAL;      // Set CCR1 interval
    //TB0CCTL1 |= CCIE;                // Enable CCR1 interrupt

    //TB0CCR2 = TB0CCR2_INTERVAL;      // Set CCR2 interval
    //TB0CCTL2 |= CCIE;                // Enable CCR2 interrupt


    TB0CTL &= ~TBIE;                 // Disable overflow interrupt
    TB0CTL &= ~TBIFG;                // Clear overflow interrupt flag
}

void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.1 L_FORWARD
// TB3.2 P6.2 R_FORWARD
// TB3.3 P6.3 L_REVERSE
// TB3.4 P6.4 R_REVERSE
// TB3.5 P6.5 LCD_BACKLITE
//------------------------------------------------------------------------------
     TB3CTL = TBSSEL__SMCLK; // SMCLK
     TB3CTL |= MC__UP; // Up Mode
     TB3CTL |= TBCLR; // Clear TAR
     PWM_PERIOD = WHEEL_PERIOD; // PWM Period [Set this to 50005]
     TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
     LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM duty cycle
     TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
     RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.2 Right Forward PWM duty cycle
     TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
     LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
     TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
     RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Right Reverse PWM duty cycle
     TB3CCTL5 = OUTMOD_7; // CCR5 reset/set
     LCD_BACKLITE_DIMING = PERCENT_80; // P6.5 LCD_BACKLITE On Diming percent
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Interrupt Service Routine: Timer0_B0_ISR
// Description: Handles Timer B0 CCR0 interrupts.
//------------------------------------------------------------------------------
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
    Time_Counter++;//ticks every 200ms;
    elapsed_time_ticks++;//ticks every 200ms, used as timer;
    if (counts == 50){//pings google every 10 secs
        ping_timer_ticks++;//timer ticks for google ping
        counts = 0;
    }
    else{
        counts++;
    }
    update_display = TRUE;
    Switches_Process();
    //P6OUT ^= LCD_BACKLITE;
    TB0CCR0 += TB0CCR0_INTERVAL;     // Add offset to TBCCR0
}

//------------------------------------------------------------------------------
// Interrupt Service Routine: TIMER0_B1_ISR
// Description: Handles Timer B0 CCR1, CCR2, and overflow interrupts.
//------------------------------------------------------------------------------
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void) {
    switch (__even_in_range(TB0IV, 14)) {
        case 0:                      // No interrupt
            break;

        case 2:                      // CCR1
            TB0CCR1 += TB0CCR1_INTERVAL;  // Add offset to TBCCR1
            break;

        case 4:                      // CCR2
            TB0CCR2 += TB0CCR2_INTERVAL;  // Add offset to TBCCR2
            break;

        case 14:                     // Overflow
            overflow_counter++;
            if (overflow_counter == 3){
                P2OUT |= DAC_ENB;//Enable dac
            }
            if (overflow_counter > 3){
                DAC_data = DAC_data - 100;
                 SAC3DAT = DAC_data; // Initial DAC data

                 if(DAC_data <= DAC_Limit){
                     DAC_data = DAC_Adjust;
                     SAC3DAT = DAC_data; // Initial DAC data
                     TB0CTL &= ~TBIE; // disable TimerB0 overflow interrupt
                 }
            }
            break;

        default:
            break;
    }
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
 switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
     case ADCIV_NONE:
         break;
     case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
             // before its previous conversion result was read.
             break;
     case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
             break;
     case ADCIV_ADCHIIFG: // Window comparator interrupt flags
             break;
     case ADCIV_ADCLOIFG: // Window comparator interrupt flag
             break;
     case ADCIV_ADCINIFG: // Window comparator interrupt flag
             break;
     case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
             ADCCTL0 &= ~ADCENC; // Disable ENC bit
             switch (ADC_Channel++){
                 case 0x00: // Channel A2 Interrupt
                     ADC_Left_Detect = ADCMEM0; // Move result into Global Values
                     ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
                     ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
                     ADCCTL0 |= ADCSC;
                     break;
                 case 0x01: // Channel A3 Interrupt
                     ADC_Right_Detect = ADCMEM0; // Move result into Global Values
                     ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
                     ADCMCTL0 |= ADCINCH_5; // Enable Next channel ?
                     ADCCTL0 |= ADCSC;
                     break;
                  case 0x02:
                      ADC_Thumb_Wheel = ADCMEM0; // Move result into Global Values
                      ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A?
                      ADCMCTL0 |= ADCINCH_2; // Enable First channel 2
                      ADC_Channel=0;
                      break;
                  default:
                      break;
                  }
             ADCCTL0 |= ADCENC; // Enable Conversions
             ADCCTL0 |= ADCSC;

             break;
     default:
         break;
 }
}

