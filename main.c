//------------------------------------------------------------------------------
//  Description: This file contains the Main Routine - "While" Operating System
//  Sai Nelluri
//  Aug 2025
//------------------------------------------------------------------------------

// Includes
#include  "msp430.h"                  // MSP430 definitions
#include  "macros.h"                  // Project macros
#include  <string.h>                  // String functions
#include  "functions.h"               // Project functions
#include  "LCD.h"                     // LCD support
#include  "ports.h"                   // Port setup
#include  "wheels.h"                  // Wheel control

// Global Variables
volatile char slow_input_down;        // Slow input flag
volatile unsigned int Movement_State_Machine_Enable = 0;  // Movement flag
extern char display_line[4][11];      // LCD display lines
extern char *display[4];              // LCD display pointer array
unsigned char display_mode;           // Display mode
extern volatile unsigned char display_changed; // Display changed flag
extern volatile unsigned char update_display;  // Display update flag
extern volatile unsigned int update_display_count; // Display update counter
extern volatile unsigned int Time_Sequence;        // Time sequence counter
extern volatile unsigned int Time_Counter;         // Time counter
extern volatile unsigned int elapsed_time_ticks;   // Tick counter (each tick = 200ms)
extern volatile char one_time;                     // One-time flag
extern volatile unsigned int ADC_Left_Detect;      // Left sensor ADC
extern volatile unsigned int ADC_Right_Detect;     // Right sensor ADC
extern volatile unsigned int ADC_Thumb_Wheel;      // Thumb wheel ADC
extern char adc_char[4];                           // ADC character buffer
char esp_ip_one[10];                // First part of ESP IP
char esp_ip_two[10];                // Second part of ESP IP
extern volatile char iot_rx_buffer[SMALL_RING_SIZE];  // RX buffer for IoT
extern volatile unsigned int iot_rx_rd;               // RX read pointer
extern volatile unsigned int iot_rx_wr;               // RX write pointer
extern volatile unsigned int ping_timer_ticks;         // Ping timer
unsigned int wheel_move;             // Wheel movement variable
char forward;                        // Forward flag

unsigned int Last_Time_Sequence;     // Last time sequence value
unsigned int cycle_time = 0;         // Cycle time counter
unsigned int time_change = 0;        // Time change flag

// Main program
void main(void){                     // Main function start

//    WDTCTL = WDTPW | WDTHOLD;      // stop watchdog timer (not used)

  PM5CTL0 &= ~LOCKLPM5;              // Disable GPIO high-impedance mode

  Init_Ports();                      // Init ports
  Init_Clocks();                     // Init clocks
  Init_Conditions();                 // Init conditions
  Init_Timers();                     // Init timers

  elapsed_time_ticks = 0;            // Reset ticks (each tick = 200ms)
  while (elapsed_time_ticks < 1);    // Delay 200ms

  Init_LCD();                        // Init LCD

  elapsed_time_ticks = 0;            // Reset ticks
  while (elapsed_time_ticks < 1);    // Delay 200ms

  Init_ADC();                        // Init ADC

  elapsed_time_ticks = 0;            // Reset ticks
  while (elapsed_time_ticks < 1);    // Delay 200ms

  Init_Serial_UCA1('a');             // Init UART1
  Init_Serial_UCA0();                // Init UART0

  elapsed_time_ticks = 0;            // Reset ticks
  while (elapsed_time_ticks < 1);    // Delay 200ms

  P3OUT |= IOT_EN;                   // Enable IoT module

  elapsed_time_ticks = 0;            // Reset ticks
  while (elapsed_time_ticks < 1);    // Delay 200ms

  Init_DAC();                        // Init DAC
  _enable_interrupt();               // Enable interrupts

  strcpy(display_line[0], "Project 10"); // LCD line 1
  strcpy(display_line[1], "   Sai    "); // LCD line 2
  strcpy(display_line[2], " Nelluri  "); // LCD line 3
  strcpy(display_line[3], "          "); // LCD line 4
  Display_Update(0,0,0,0);           // Update LCD

  while (elapsed_time_ticks < 20);   // Delay 20 ticks (4 seconds)

  startup_cmds();                    // Send ESP startup commands
  uart0_puts("AT+CIFSR\r\n");        // Request IP address

  read_esp_ip();                     // Read ESP IP into display strings

  strcpy(display_line[0], "Project 10"); // Update LCD
  strcpy(display_line[1], esp_ip_one);
  strcpy(display_line[2], esp_ip_two);
  strcpy(display_line[3], "Waiting...");
  Display_Update(0,0,0,0);

  elapsed_time_ticks = 0;            // Reset ticks

  P2OUT |= IR_LED;                   // Turn on IR LED
  wheel_move = 0;                    // Reset wheel movement
  forward = TRUE;                    // Set forward flag
  stop_all();                        // Stop motors
  LCD_BACKLITE_DIMING = 0;           // Backlight at 0

//------------------------------------------------------------------------------
//  Start of the "While" Operating System
//------------------------------------------------------------------------------

  while(ALWAYS) {                    // Infinite loop
    checking();                      // Run checking function
    Carlson_StateMachine();          // Run state machine
    Switches_Process();              // Handle switches
    Display_Process();               // Update display
    P3OUT ^= TEST_PROBE;             // Toggle test probe

    if(Last_Time_Sequence != Time_Sequence){  // Check sequence change
           Last_Time_Sequence = Time_Sequence; // Update last sequence
           cycle_time++;                       // Increment cycle time
           time_change = 1;                    // Mark time change
    }

    if (ping_timer_ticks == 1){      // Ping timer
        ping_google();               // Ping Google
        ping_timer_ticks = 0;        // Reset ping timer
    }

    cmd_parsing();                   // Parse incoming commands

  } // end while(ALWAYS)

} // end main

//------------------------------------------------------------------------------
// Reads ESP IP from UART buffer
//------------------------------------------------------------------------------
void read_esp_ip(void) {
    unsigned int rd = iot_rx_rd;     // Read index
    unsigned int ip_index = 0;       // IP buffer index
    char *ip_ptr = esp_ip_one;       // Pointer to IP buffer
    int quote_found = 0;             // Quote counter

    memset(esp_ip_one, 0, sizeof(esp_ip_one)); // Clear buffer 1
    memset(esp_ip_two, 0, sizeof(esp_ip_two)); // Clear buffer 2

    while (quote_found < 2) {        // Look for two quoted IP strings
        while (rd != iot_rx_wr) {    // Loop through buffer
            char c = iot_rx_buffer[rd]; // Read char
            rd = (rd + 1) % SMALL_RING_SIZE; // Increment pointer

            if (c == '"') {          // Quote found
                quote_found++;       // Count quote
                if (quote_found == 1) {
                    ip_ptr = esp_ip_one; // Fill first buffer
                    ip_index = 0;
                } else if (quote_found == 2) {
                    for (; ip_index < 10; ip_index++) {
                        esp_ip_two[ip_index] = ' '; // Pad second buffer
                    }
                    iot_rx_rd = rd;   // Update read pointer
                    break;
                }
                continue;             // Skip quote char
            }

            if (quote_found == 1) {  // Inside quoted string
                if (ip_ptr == esp_ip_one && ip_index >= 10) {
                    ip_ptr = esp_ip_two; // Switch to second buffer
                    ip_index = 0;
                }
                if (ip_index < 10) {
                    ip_ptr[ip_index++] = c; // Store char
                    ip_ptr[ip_index] = '\0'; // Null terminate
                }
            }
        }
    }
}
