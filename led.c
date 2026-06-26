/*
 * description: includes led initializations
 * led.c
 * Created on: Aug 2025
 * Author: Sai Nelluri
 */
#include  "msp430.h"
#include  "macros.h"

volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;

unsigned int wheel_move;
char forward;

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}
