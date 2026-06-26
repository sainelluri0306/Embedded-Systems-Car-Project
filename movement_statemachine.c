/*
 * description: includes functions for project 10 / Demo Day
 * movement_statemachine.c
 * Created on: Nov 30, 2025
 * Author: Sai Nelluri
 */
#include "msp430.h"
#include <string.h>
#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"

extern unsigned int elapsed_time_ticks;          // Timer ticks (each tick = 200ms)
extern volatile unsigned int ADC_Left_Detect;    // Left sensor ADC reading
extern volatile unsigned int ADC_Right_Detect;   // Right sensor ADC reading
extern volatile unsigned int ADC_Thumb_Wheel;    // Thumbwheel ADC (not used here)
extern char display_line[4][11];                 // LCD line buffer (4 lines, 10 chars + NULL)
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;   // LCD update flag
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
volatile unsigned int BoW;
extern unsigned int elapsed_time_ticks;

extern volatile char iot_rx_buffer[SMALL_RING_SIZE];  // Ring buffer for IoT UART
extern volatile unsigned int iot_rx_rd;               // Read index
extern volatile unsigned int iot_rx_wr;               // Write index
unsigned char travel_msg_shown = 0;                   // Prevents repeating BLD Travel text


// ===============================
// Parses commands starting with '^'
// ===============================
void cmd_parsing(void) {
    while (1) {

        if (iot_rx_rd == iot_rx_wr) {
            return;   // Buffer empty
        }

        char c = iot_rx_buffer[iot_rx_rd]; // Fetch character
        iot_rx_rd = (iot_rx_rd + 1) % SMALL_RING_SIZE;

        if (c != '^') {
            continue; // Not a command start
        }

        while (iot_rx_rd == iot_rx_wr); // Wait for command byte

        char cmd = iot_rx_buffer[iot_rx_rd];   // Command character
        iot_rx_rd = (iot_rx_rd + 1) % SMALL_RING_SIZE;

        switch (cmd) {

            case 'T':   // Toggle backlight brightness
                LCD_BACKLITE_DIMING =
                    (LCD_BACKLITE_DIMING == PERCENT_0 ?
                     PERCENT_80 : PERCENT_0);
                return;

            case 'F':   // Forward command
                handle_cmd(cmd, " Forward  ");
                strcpy(display_line[0], "          ");
                Display_Update(0,0,0,0);
                forward_moving();   // Move forward
                stop_all();
                return;

            case 'B':   // Reverse command
                handle_cmd(cmd, " Reverse  ");
                reverse_moving();
                stop_all();
                return;

            case 'V':   // 15° right turn
                handle_cmd(cmd, " 15R Turn ");
                fifteen_deg_turning_R();
                stop_all();
                return;

            case 'W':   // 15° left turn
                handle_cmd(cmd, " 15L Turn ");
                fifteen_deg_turning_L();
                stop_all();
                return;

            case 'N':   // 90° right turn
                handle_cmd(cmd, " 90R Turn ");
                ninty_deg_turning_R();
                stop_all();
                return;

            case 'M':   // 90° left turn
                handle_cmd(cmd, " 90L Turn ");
                ninty_deg_turning_L();
                stop_all();
                return;

            case 'D':   // Begin black line detection
                handle_cmd(cmd, "BLD Detect");
                black_line_detection();
                stop_all();
                return;

            case 'S':   // BLD setup routine
                handle_cmd(cmd, " BLD Setup ");
                bld_setup();
                stop_all();
                return;

            // Arrival messages 0–8
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7': case '8':
                handle_cmd(cmd, " Arrived  ");
                strcpy(display_line[0], "Arrived   ");
                display_line[0][9] = cmd;   // Place number in last column
                Display_Update(0,0,0,0);
                display_changed = TRUE;
                stop_all();
                return;

            default:
                break;
        }
    }
}


// Displays command msg on line 3
static void handle_cmd(char cmd, const char *msg) {
    strcpy(display_line[3], msg);
    strcpy(display_line[0], "          ");
    Display_Update(0,0,0,0);
    display_changed = TRUE;
}


// Forward for 5 ticks = 1 second
void forward_moving(void){
    Forward_Move();
    elapsed_time_ticks = 0;
    while (elapsed_time_ticks < 5);     // 5 ticks × 200ms = 1s
    stop_all();
}

// Reverse for 5 ticks = 1 second
void reverse_moving(void){
    Reverse_Move();
    elapsed_time_ticks = 0;
    while (elapsed_time_ticks < 5);
    stop_all();
}

// 15° right turn (1 tick = 200ms)
void fifteen_deg_turning_R(void){
    clockwiser_right();
    elapsed_time_ticks = 0;
    while (elapsed_time_ticks < 1);
    stop_all();
}

// 15° left turn
void fifteen_deg_turning_L(void){
    clockwiser_left();
    elapsed_time_ticks = 0;
    while (elapsed_time_ticks < 1);
    stop_all();
}

// 90° right turn (5 ticks = 1 second)
void ninty_deg_turning_R(void){
    clockwiser_right();
    elapsed_time_ticks = 0;
    while (elapsed_time_ticks < 5);
    stop_all();
}

// 90° left turn
void ninty_deg_turning_L(void){
    clockwiser_left();
    elapsed_time_ticks = 0;
    while (elapsed_time_ticks < 5);
    stop_all();
}


// ===============================
// Black Line Detection Setup Mode
// ===============================
void bld_setup(void){
    strcpy(display_line[0], " BLD Setup");
    strcpy(display_line[1], "LEFT:     ");
    strcpy(display_line[2], "RIGHT:    ");
    Display_Update(0,0,0,0);

    unsigned int white_detect_ticks = 0; // Counts time on white
    unsigned char saw_white = 0;         // White-detection flag

    forward_moving();           // Move forward initially
    Forward_Move_ARC();         // Begin curved forward motion
    elapsed_time_ticks = 0;

    while (1) {

        unsigned int right_val = ADC_Left_Detect;
        unsigned int left_val  = ADC_Right_Detect;

        // Update sensor values on LCD
        HEXtoBCD(left_val);
        adc_line(2,6);
        HEXtoBCD(right_val);
        adc_line(3,6);
        Display_Update(0,0,0,0);

        unsigned char left_white  = (left_val  <= 2400);
        unsigned char right_white = (right_val <= 2400);

        unsigned char left_black  = (left_val  > 3000);
        unsigned char right_black = (right_val > 3000);


        // STEP 1 — Require white for >= 7 ticks (1.4 seconds)
        if (!saw_white) {

            if (left_white && right_white) {
                white_detect_ticks++;

                if (white_detect_ticks == 1) {
                    strcpy(display_line[0], "          ");
                    Display_Update(0,0,0,0);
                    strcpy(display_line[0], "  BL START");
                    Display_Update(0,0,0,0);

                    stop_all();
                    elapsed_time_ticks = 0;
                    while (elapsed_time_ticks < 60); // Pause 12s
                    Forward_Move_ARC();
                }
            }
            else {
                white_detect_ticks = 0; // Must be continuous
            }

            if (white_detect_ticks >= 7) {
                saw_white = 1;
            }
        }

        // STEP 2 — After white is confirmed, look for black
        else {

            if (left_black || right_black) {

                // Display intercept status
                strcpy(display_line[0], "          ");
                Display_Update(0,0,0,0);
                strcpy(display_line[0], " INTERCEPT");
                Display_Update(0,0,0,0);

                stop_all();

                // STEP 3 — Back up for 1 tick (200ms)
                Reverse_Move();
                elapsed_time_ticks = 0;
                while (elapsed_time_ticks < 1);
                stop_all();

                elapsed_time_ticks = 0;
                while (elapsed_time_ticks < 60); // Pause 12s

                // STEP 4 — Counterclockwise turn until black detected equally
                strcpy(display_line[0], "          ");
                Display_Update(0,0,0,0);
                strcpy(display_line[0], "  BL Turn ");
                Display_Update(0,0,0,0);

                Left_Reverse();    // CCW rotation
                Right_Forward();

                while (1) {
                    unsigned int right_val = ADC_Left_Detect;
                    unsigned int left_val  = ADC_Right_Detect;

                    HEXtoBCD(left_val);
                    adc_line(2,6);
                    HEXtoBCD(right_val);
                    adc_line(3,6);
                    Display_Update(0,0,0,0);

                    unsigned char left_black  = (left_val  > 2900);
                    unsigned char right_black = (right_val > 2900);

                    if (left_black && right_black) {
                        stop_all();
                        return;
                    }
                }
            }
        }

        // Safety timeout ~100 seconds
        if (elapsed_time_ticks > 500) {
            stop_all();
            strcpy(display_line[0], "Timeout   ");
            Display_Update(0,0,0,0);
            return;
        }
    }
}



// ===============================
// Line Following Mode
// ===============================
void black_line_detection(void){
    elapsed_time_ticks = 0;

    strcpy(display_line[0], "BLD Travel");
    strcpy(display_line[1], "LEFT:     ");
    strcpy(display_line[2], "RIGHT:    ");
    Display_Update(0,0,0,0);

    while (elapsed_time_ticks < 1000) { // ~200 seconds

        // After 10 seconds, change display to BLD Circle once
        if (!travel_msg_shown && elapsed_time_ticks > 50) {
            strcpy(display_line[0], "BLD Circle");
            Display_Update(0,0,0,0);
            travel_msg_shown = 1;

            stop_all();
            elapsed_time_ticks = 0;
            while (elapsed_time_ticks < 50); // Pause 10s
        }

        // Reads UART for exit command
        unsigned int rd_tmp = iot_rx_rd;

        if (rd_tmp != iot_rx_wr) {

            char c = iot_rx_buffer[rd_tmp];

            iot_rx_rd = (iot_rx_rd + 1) % SMALL_RING_SIZE;

            if (c == '^') {
                unsigned int next = iot_rx_rd;

                if (iot_rx_buffer[next] == 'F') {
                    iot_rx_rd = (iot_rx_rd + 1) % SMALL_RING_SIZE;

                    strcpy(display_line[0], " BLD Exit ");
                    Display_Update(0,0,0,0);

                    Forward_Move();
                    elapsed_time_ticks = 0;
                    while (elapsed_time_ticks < 20); // 4 seconds
                    stop_all();
                    strcpy(display_line[0], " BLD Stop ");
                    Display_Update(0,0,0,0);
                    return;
                }
            }
        }

        unsigned int right_val = ADC_Left_Detect;
        unsigned int left_val  = ADC_Right_Detect;

        HEXtoBCD(left_val);
        adc_line(2,6);
        HEXtoBCD(right_val);
        adc_line(3,6);
        Display_Update(0,0,0,0);

        // Line following decisions
        if (left_val > 2900 && right_val > 2900) {
            Forward_Move_BLD();         // Both on black then go straight
        }
        else if (left_val > 2900 && right_val <= 2900) {
            Right_Forward_BLD();        // Left sees black then steer right
            Left_Off();
        }
        else if (left_val <= 2900 && right_val > 2900) {
            Left_Forward_BLD();         // Right sees black then steer left
            Right_Off();
        }
    }

    strcpy(display_line[1], "          ");
    strcpy(display_line[2], "   BLD    ");
    strcpy(display_line[3], "   DONE   ");
    Display_Update(0,0,0,0);
}
