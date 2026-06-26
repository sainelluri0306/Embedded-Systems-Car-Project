/*
 * description: includes initialization commands for wifi and function for pinging google
 * init_cmds.c
 * Created on: Nov 2025
 * Author: Sai Nelluri
 */
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "wheels.h"

extern volatile char esp_ip_one;         // ESP IP first digit
extern volatile char esp_ip_two;         // ESP IP second digit

extern volatile char iot_rx_buffer[SMALL_RING_SIZE]; // IoT RX ring buffer
extern volatile unsigned int iot_rx_rd;  // RX buffer read index
extern volatile unsigned int iot_rx_wr;  // RX buffer write index

extern char display_line[4][11];         // Display buffer
extern char *display[4];                 // Display pointers
unsigned char display_mode;              // Display mode
extern volatile unsigned char display_changed;        // Display changed flag
extern volatile unsigned char update_display;         // Update display request
extern volatile unsigned int update_display_count;    // Display update counter

extern volatile unsigned int elapsed_time_ticks;      // Tick counter (each tick = 200ms)

void startup_cmds(void) {                // Send startup AT commands
    wait_for_ip();                       // Wait for IP message from ESP
    uart0_puts("AT+SYSSTORE=0\r\n");     // Disable auto-saving settings
    wait_for_ok();                       // Wait for OK response
    uart0_puts("AT+CIPMUX=1\r\n");       // Enable multiple connections
    wait_for_ok();                       // Wait for OK response
    uart0_puts("AT+CIPSERVER=1,2007\r\n"); // Start TCP server on port 2007
    wait_for_ok();                       // Wait for OK response
}

int wait_for_ok_or_fail(unsigned int timeout_ticks) { // Wait for OK or timeout
    unsigned int start = elapsed_time_ticks;          // Record start time

    while (1) {                                       // Loop until OK or timeout
        if ((elapsed_time_ticks - start) > timeout_ticks) { // Check for timeout
            return 0;                                 // Timeout -> FAIL
        }

        unsigned int rd = iot_rx_rd;                  // Local copy of read index

        while (rd != iot_rx_wr) {                     // Scan buffer
            char c = iot_rx_buffer[rd];               // Read character
            rd = (rd + 1) % SMALL_RING_SIZE;          // Advance temp index

            if (c == 'O') {                           // Detect 'O'
                unsigned int next = rd % SMALL_RING_SIZE; // Next index
                if (iot_rx_buffer[next] == 'K') {     // Check for 'K'
                    iot_rx_rd = (next + 1) % SMALL_RING_SIZE; // Advance real read index
                    return 1;                         // Found OK
                }
            }
        }
    }
}

int wait_for_ok(void) {                               // Wait for OK response
    unsigned int rd;                                  // Read temp index

    while (1) {                                       // Loop until OK found
        rd = iot_rx_rd;                               // Local copy read index

        while (rd != iot_rx_wr) {                     // Scan buffer
            char c = iot_rx_buffer[rd];               // Read character
            rd = (rd + 1) % SMALL_RING_SIZE;          // Advance temp index

            if (c == 'O') {                           // Detect 'O'
                unsigned int next = (rd) % SMALL_RING_SIZE; // Next index
                if (iot_rx_buffer[next] == 'K') {     // Check for 'K'
                    iot_rx_rd = (next + 1) % SMALL_RING_SIZE; // Advance read index
                    return 1;                         // OK found
                }
            }
        }
    }
}

int wait_for_ip(void) {                               // Wait for "IP" message
    unsigned int rds;                                 // Temp read index

    while (1) {                                       // Loop until IP found
        rds = iot_rx_rd;                              // Local copy read index

        while (rds != iot_rx_wr) {                    // Scan buffer
            char c = iot_rx_buffer[rds];              // Read character
            rds = (rds + 1) % SMALL_RING_SIZE;        // Advance temp index

            if (c == 'I') {                           // Detect 'I'
                unsigned int next = (rds) % SMALL_RING_SIZE; // Next index
                if (iot_rx_buffer[next] == 'P') {     // Check for 'P'
                    iot_rx_rd = (next + 1) % SMALL_RING_SIZE; // Advance real read index
                    return 1;                         // Found IP
                }
            }
        }
    }
}

void ping_google(void) {                              // Ping Google DNS
    uart0_puts("AT+PING=\"8.8.8.8\"\r\n");            // Send ping command
}
