/*
 * description: includes port configurations
 * ports.c
 * Sai Nelluri
 * September 12, 2025
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

unsigned int wheel_move;
char forward;
extern char p3_smclk_mode;

void Init_Ports(void){
    Init_Ports_1();
    Init_Ports_2();
    Init_Ports_3(p3_smclk_mode);
    Init_Ports_4();
    Init_Ports_5();
    Init_Ports_6();
}

void Init_Ports_1(void){
    P1OUT = 0x00; // P2 set Low
    P1DIR = 0x00; // Set P2 direction to output

    P1SEL0 &= ~RED_LED; // RED_LED GPIO operation
    P1SEL1 &= ~RED_LED; // RED_LED GPIO operation
    P1OUT &= ~RED_LED; // Initial Value = Low / Off
    P1DIR |= RED_LED; // Direction = output

    //Check this

    P1SEL0 &= ~A1_SEEED; // A1_SEEED Operation
    P1SEL1 &= ~A1_SEEED; // A1_SEEED Operation
    P1OUT &= ~A1_SEEED; // Configure pullup resistor
    P1DIR |= A1_SEEED; // Direction = output

    P1SELC |= V_DETECT_L;
    //P1SEL0 &= ~V_DETECT_L; // V_DETECT_L GPIO operation
    //P1SEL1 &= ~V_DETECT_L; // V_DETECT_L GPIO operation
    //P1OUT &= ~V_DETECT_L; // Initial Value = Low / Off
    //P1DIR |= V_DETECT_L; // Direction = output

    P1SELC |= V_DETECT_R;
    /*P1SEL0 &= ~V_DETECT_R; // V_DETECT_R GPIO operation
    P1SEL1 &= ~V_DETECT_R; // V_DETECT_R GPIO operation
    P1OUT &= ~V_DETECT_R; // Initial Value = Low / Off
    P1DIR |= V_DETECT_R; // Direction = output*/

    P1SEL0 &= ~A4_SEEED; // A4_SEEED GPIO operation
    P1SEL1 &= ~A4_SEEED; // A4_SEEED GPIO operation
    P1OUT &= ~A4_SEEED; // Initial Value = Low / Off
    P1DIR |= A4_SEEED; // Direction = output

    P1SELC |= V_THUMB;
    /*P1SEL0 &= ~V_THUMB; // V_THUMB GPIO operation
    P1SEL1 &= ~V_THUMB; // V_THUMB GPIO operation
    P1OUT &= ~V_THUMB; // Initial Value = Low / Off
    P1DIR |= V_THUMB; // Direction = output*/


    P1SEL0 |= UCA0RXD; // UCA0RXD GPIO operation
    P1SEL1 &= ~UCA0RXD; // UCA0RXD GPIO operation

    P1SEL0 |= UCA0TXD; // UCA0TXD GPIO operation
    P1SEL1 &= ~UCA0TXD; // UCA0TXD GPIO operation

}
void Init_Ports_2(void){
     P2OUT = 0x00; // P2 set Low
     P2DIR = 0x00; // Set P2 direction to output
     P2SEL0 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
     P2SEL1 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
     P2OUT &= ~SLOW_CLK; // Initial Value = Low / Off
     P2DIR |= SLOW_CLK; // Direction = output

     P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
     P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
     P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
     P2DIR |= CHECK_BAT; // Direction = output

     P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
     P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
     P2OUT &= ~IR_LED; // Initial Value = Low / Off
     P2DIR |= IR_LED; // Direction = output

     P2SEL0 &= ~SW2; // SW2 Operation
     P2SEL1 &= ~SW2; // SW2 Operation
     P2OUT |= SW2; // Configure pullup resistor
     P2DIR &= ~SW2; // Direction = input
     P2REN |= SW2; // Enable pullup resistor

     P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
     P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
     P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off
     P2DIR |= IOT_RUN_RED; // Direction = output

     P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
     P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
     P2OUT &= ~DAC_ENB; // Initial Value = High -- Put this for DAC
     P2DIR |= DAC_ENB; // Direction = output


     P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
     P2SEL1 |= LFXOUT; // LFXOUT Clock operation
     P2SEL0 &= ~LFXIN; // LFXIN Clock operation
     P2SEL1 |= LFXIN; // LFXIN Clock operation
}

void Init_Ports_3(char smclk){
    P3OUT = 0x00; // P2 set Low
    P3DIR = 0x00; // Set P2 direction to output

    P3SEL0 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3SEL1 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3OUT &= ~TEST_PROBE; // Initial Value = Low / Off
    P3DIR |= TEST_PROBE; // Direction = output

    P3SEL0 &= ~DAC_CNTL_2; // DAC_CNTL_2 Operation
    P3SEL1 &= ~DAC_CNTL_2; // A1_SEEED Operation
    P3OUT &= ~DAC_CNTL_2; // Configure pullup resistor
    P3DIR |= DAC_CNTL_2; // Direction = output

    P3SEL0 &= ~OA2N; // OA2N GPIO operation
    P3SEL1 &= ~OA2N; // OA2N GPIO operation
    P3OUT &= ~OA2N; // Initial Value = Low / Off
    P3DIR |= OA2N; // Direction = output

    P3SEL0 &= ~OA2P; // OA2P GPIO operation
    P3SEL1 &= ~OA2P; // OA2P GPIO operation
    P3OUT &= ~OA2P; // Initial Value = Low / Off
    P3DIR |= OA2P; // Direction = output

    // ------------ SMCLK special handling ------------
        if(smclk == USE_SMCLK){
            // Configure pin to output SMCLK function
            P3DIR  |= SMCLK;   // Output direction
            P3SEL0 |= SMCLK;   // Select SMCLK peripheral
            P3SEL1 &= ~SMCLK;
        } else {
            // Default: configure as GPIO
            P3SEL0 &= ~SMCLK;
            P3SEL1 &= ~SMCLK;
            P3OUT  &= ~SMCLK;
            P3DIR  |= SMCLK;
        }
        // ------------------------------------------------
        P3SELC |= DAC_CNTL_3;
//    P3SEL0 &= ~DAC_CNTL_3; // DAC_CNTL_3 GPIO operation
//    P3SEL1 &= ~DAC_CNTL_3; // DAC_CNTL_3 GPIO operation
//    P3OUT |= DAC_CNTL_3;
//    P3DIR |= DAC_CNTL_3; // Direction = output

    P3SEL0 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
    P3SEL1 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
    P3OUT &= ~IOT_LINK_GRN; // Initial Value = Low / Off
    P3DIR |= IOT_LINK_GRN; // Direction = output

    P3SEL0 &= ~IOT_EN; // IOT_EN GPIO operation
    P3SEL1 &= ~IOT_EN; // IOT_EN GPIO operation
    P3OUT &= ~IOT_EN; // Initial Value = Low / Off
    P3DIR |= IOT_EN; // Direction = output


}

void Init_Ports_4(void){
// Configure PORT 4
//------------------------------------------------------------------------------
 P4OUT = 0x00; // P4 set Low
 P4DIR = 0x00; // Set P4 direction to output
 P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
 P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
 P4OUT &= ~RESET_LCD; // Initial Value = Low / Off
 P4DIR |= RESET_LCD; // Direction = output

 P4SEL0 &= ~SW1; // SW1 GPIO operation
 P4SEL1 &= ~SW1; // SW1 GPIO operation
 P4OUT |= SW1; // Configure pullup resistor
 P4DIR &= ~SW1; // Direction = input
 P4REN |= SW1; // Enable pullup resistor

 P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
 P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

 P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
 P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

 P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
 P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
 P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
 P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

 P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
 P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
 P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
 P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
 P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
 P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
 //------------------------------------------------------------------------------
}

void Init_Ports_5(void){
    P5OUT = 0x00; // P2 set Low
    P5DIR = 0x00; // Set P2 direction to output

    P5SEL0 &= ~V_BAT; // V_BAT GPIO operation
    P5SEL1 &= ~V_BAT; // V_BAT GPIO operation
    P5OUT &= ~V_BAT; // Initial Value = Low / Off
    P5DIR |= V_BAT; // Direction = output

    P5SEL0 &= ~V_5_0; // V_5_0 Operation
    P5SEL1 &= ~V_5_0; // A1_SEEED Operation
    P5OUT &= ~V_5_0; // Configure pullup resistor
    P5DIR |= V_5_0; // Direction = output

    P5SEL0 &= ~V_DAC; // V_DAC GPIO operation
    P5SEL1 &= ~V_DAC; // V_DAC GPIO operation
    P5OUT &= ~V_DAC; // Initial Value = Low / Off
    P5DIR |= V_DAC; // Direction = output

    P5SEL0 &= ~V_3_3; // V_3_3 GPIO operation
    P5SEL1 &= ~V_3_3; // V_3_3 GPIO operation
    P5OUT &= ~V_3_3; // Initial Value = Low / Off
    P5DIR |= V_3_3; // Direction = output

    P5SEL0 &= ~IOT_BOOT_CPU; // IOT_BOOT_CPU GPIO operation
    P5SEL1 &= ~IOT_BOOT_CPU; // IOT_BOOT_CPU GPIO operation
    P5OUT |= IOT_BOOT_CPU; // Initial Value = Low / Off
    P5DIR |= IOT_BOOT_CPU; // Direction = output
}

void Init_Ports_6(void){
    P6OUT = 0x00; // P2 set Low
    P6DIR = 0x00; // Set P2 direction to output

    P6SEL0 |= L_FORWARD; // L_FORWARD GPIO operation
    P6SEL1 &= ~L_FORWARD; // L_FORWARD GPIO operation
    //P6OUT &= ~L_FORWARD; // Initial Value = Low / Off
    P6DIR |= L_FORWARD; // Direction = output

    P6SEL0 |= R_FORWARD; // R_FORWARD Operation
    P6SEL1 &= ~R_FORWARD; // R_FORWARD Operation
    //P6OUT &= ~R_FORWARD; // Configure pullup resistor
    P6DIR |= R_FORWARD; // Direction = output

    P6SEL0 |= L_REVERSE; // L_REVERSE GPIO operation
    P6SEL1 &= ~L_REVERSE; // L_REVERSE GPIO operation
    //P6OUT &= ~L_REVERSE; // Initial Value = Low / Off
    P6DIR |= L_REVERSE; // Direction = output

    P6SEL0 |= R_REVERSE; // R_REVERSE GPIO operation
    P6SEL1 &= ~R_REVERSE; // R_REVERSE GPIO operation
    //P6OUT &= ~R_REVERSE; // Initial Value = Low / Off
    P6DIR |= R_REVERSE; // Direction = output

    P6SEL0 |= LCD_BACKLITE; // LCD_BACKLITE GPIO operation
    P6SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
    //P6OUT |= LCD_BACKLITE; // Initial Value = Low / Off
    P6DIR |= LCD_BACKLITE; // Direction = output

    P6SEL0 &= ~P6_5; // P6_5 GPIO operation
    P6SEL1 &= ~P6_5; // P6_5 GPIO operation
    P6OUT &= ~P6_5; // Initial Value = Low / Off
    P6DIR |= P6_5; // Direction = output

    P6SEL0 &= ~GRN_LED; // GRN_LED GPIO operation
    P6SEL1 &= ~GRN_LED; // GRN_LED GPIO operation
    P6OUT &= ~GRN_LED; // Initial Value = Low / Off
    P6DIR |= GRN_LED; // Direction = output
}
