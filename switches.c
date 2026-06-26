/*
 * description: includes switches functions
 * switches.c
 * Sai Nelluri
 * September 2025
 */
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "wheels.h"


// Global variables
volatile unsigned char sw1_position = RELEASED;
volatile unsigned char sw2_position = RELEASED;

volatile unsigned char okay_to_look_at_switch1 = OKAY;
volatile unsigned char okay_to_look_at_switch2 = OKAY;

volatile unsigned int count_debounce_SW1 = 0;
volatile unsigned int count_debounce_SW2 = 0;

extern char event;
extern volatile unsigned int Movement_State_Machine_Enable;
extern char state;
unsigned int shape_selection = 0;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern unsigned int BoW;

extern char display_line[4][11];

char p3_smclk_mode = USE_GPIO;

//------------------------------------------------------------------------------
// Top-level function called from main loop
//------------------------------------------------------------------------------
void Switches_Process(void){
  Switch1_Process();
  Switch2_Process();
}

//------------------------------------------------------------------------------
// Switch 1 Processing (P4.1)
//------------------------------------------------------------------------------
// Switch 1 Processing (P4.1) — triggers calibration
void Switch1_Process(void){
//    static unsigned char sw1_state = RELEASED;
//
//    // Check if switch is pressed (active low)
//    if (!(P4IN & SW1)) {
//        if (sw1_state == RELEASED) {  // Edge detection: trigger only once per press
//            sw1_state = PRESSED;
//
//            // Trigger calibration
//            calibrate_BoW();
//        }
//    } else {
//        sw1_state = RELEASED; // Reset when released
//    }
}


//------------------------------------------------------------------------------
// Switch 2 Processing (P2.3)
//------------------------------------------------------------------------------
void Switch2_Process(void) {
//  if (okay_to_look_at_switch2 && sw2_position) {
//    if (!(P2IN & SW2)) {                     // Active low pressed
//      sw2_position = PRESSED;
//      okay_to_look_at_switch2 = NOT_OKAY;
//      count_debounce_SW2 = DEBOUNCE_RESTART;
//      P2OUT |= IR_LED;
//      // --- Run calibration when Switch 2 is pressed ---
//      Movement_State_Machine_Enable = 1;
//
//    }
//  }
//
//  if (count_debounce_SW2 <= DEBOUNCE_TIME) {
//    count_debounce_SW2++;
//  } else {
//    okay_to_look_at_switch2 = OKAY;
//    if (P2IN & SW2) {
//      sw2_position = RELEASED;
//    }
//  }
}
