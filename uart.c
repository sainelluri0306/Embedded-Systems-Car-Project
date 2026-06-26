/*
 * description: includes uart initializations and interrupts and variables for buffer
 * UART.c
 * Created on: Oct 30, 2025
 * Author: Sai Nelluri
 */

#include "msp430.h"
#include "ports.h"
#include "functions.h"
#include "macros.h"

volatile char iot_rx_buffer[SMALL_RING_SIZE];   // Circular buffer for incoming UART0 data
volatile char iot_tx_buffer[SMALL_RING_SIZE];   // Circular buffer for outgoing UART0 data
volatile char iot_rx_rd;                        // Read index for RX ring buffer
volatile char iot_rx_wr;                        // Write index for RX ring buffer
volatile char iot_tx;                           // TX index for transmit ring buffer

extern volatile char end;                       // External flag used elsewhere



void Init_Serial_UCA0(void){
    int i;
    for(i = 0; i < SMALL_RING_SIZE; i++){
        iot_rx_buffer[i] = 0x00;                // Clear RX buffer
        iot_tx_buffer[i] = 0x00;                // Clear TX buffer
    }

    iot_rx_wr = BEGINNING;                      // Initialize write pointer
    iot_rx_rd = BEGINNING;                      // Initialize read pointer

    UCA0CTLW0 = 0;
    UCA0CTLW0 |= UCSWRST;                       // Put UART0 in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;                 // SMCLK as clock source
    UCA0CTLW0 &= ~UCMSB;                        // LSB first
    UCA0CTLW0 &= ~UCSPB;                        // One stop bit
    UCA0CTLW0 &= ~UCPEN;                        // No parity
    UCA0CTLW0 &= ~UCSYNC;                       // Asynchronous mode
    UCA0CTLW0 &= ~UC7BIT;                       // 8-bit data
    UCA0CTLW0 |= UCMODE_0;                      // UART mode

    UCA0BRW = 4;                                // Baud rate setting for 115200
    UCA0MCTLW = 0x5551;                         // Modulation config for 115200
    UCA0CTLW0 |= UCOS16;                        // Oversampling enabled

    UCA0CTLW0 &= ~UCSWRST;                      // Release UART from reset
    UCA0TXBUF = 0x00;                           // Initialize TX buffer
    UCA0IE |= UCRXIE;                           // Enable RX interrupt
}

void Init_Serial_UCA1(char speed){
    UCA1CTLW0 = 0;
    UCA1CTLW0 |= UCSWRST;                       // Put UART1 in reset
    UCA1CTLW0 |= UCSSEL__SMCLK;                 // Use SMCLK
    UCA1CTLW0 &= ~UCMSB;                        // LSB first
    UCA1CTLW0 &= ~UCSPB;                        // One stop bit
    UCA1CTLW0 &= ~UCPEN;                        // No parity
    UCA1CTLW0 &= ~UCSYNC;                       // Asynchronous
    UCA1CTLW0 &= ~UC7BIT;                       // 8-bit data
    UCA1CTLW0 |= UCMODE_0;                      // UART mode

    UCA1BRW = 4;                                // 115200 baud
    UCA1MCTLW = 0x5551;                         // Modulation for 115200

    UCA1CTLW0 &= ~UCSWRST;                      // Exit reset
    UCA1TXBUF = 0x00;                           // Initialize TX
    UCA1IE |= UCRXIE;                           // Enable RX interrupt
}

void uart0_puts(char *s){
    while (*s) {
        while (!(UCA0IFG & UCTXIFG));           // Wait until TX buffer is ready
        UCA0TXBUF = *s++;                       // Send next character
    }
}


#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void) {
    char iot_recieve;

    switch(__even_in_range(UCA0IV, 0x08)) {
    case 0:
        break;                                   // No interrupt
    case 2:                                      // RX interrupt
        iot_recieve = UCA0RXBUF;                 // Read received byte
        UCA1TXBUF = iot_recieve;                 // Echo to UART1

        iot_rx_buffer[iot_rx_wr++] = iot_recieve; // Store in RX ring buffer
        if (iot_rx_wr >= SMALL_RING_SIZE)        // Wrap index if needed
            iot_rx_wr = 0;
        break;

    case 4:                                      // TX interrupt (unused)
        break;

    default:
        break;
    }
}


#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
    char usb_value;

    switch(__even_in_range(UCA1IV, 0x08)){
        case 0:
            break;                               // No interrupt

        case 2:                                  // RX interrupt
            usb_value = UCA1RXBUF;               // Read received data
            UCA0TXBUF = usb_value;               // Echo to UART0
            break;

        case 4:                                  // TX interrupt (unused)
            break;

        default:
            break;
    }
}
