/*
 * description: includes display configurations
 * Display.c
 * Created on: Aug 2025
 * Author: Sai Nelluri
 */
#include  "msp430.h"
#include  "macros.h"
#include  "ports.h"
#include  "functions.h"
#include  "LCD.h"

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
extern volatile unsigned int elapsed_time_ticks;

unsigned int wheel_move;
char forward;


void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}

void Display_Elapsed_Time(void) {
    unsigned int total_ticks = elapsed_time_ticks;
    unsigned int total_tenths = total_ticks * 2;  // Each tick = 0.2s
    unsigned int seconds = total_tenths / 10;
    unsigned int tenths = total_tenths % 10;

    // Clear or overwrite part of the display buffer line 3
    display_line[3][6] = '0' + (seconds / 100) % 10;   // Hundreds place (if 0–999s range)
    display_line[3][7] = '0' + (seconds / 10) % 10;    // Tens
    display_line[3][8] = '0' + (seconds % 10);         // Ones
    display_line[3][9] = '.';
    display_line[3][10] = '0' + tenths;                 // Tenths place

    update_display = TRUE;  // Trigger LCD update in your main loop
}
