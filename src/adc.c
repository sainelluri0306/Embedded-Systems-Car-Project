#include  "msp430.h"
#include  "macros.h"
#include "functions.h"

/*
 * description: includes functions that initializes ADC values, HextoBCD conversion function, and display adc values function
 * adc.c
 * Created on: Sep 2025
 * Author: Sai Nelluri
 */

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
char adc_char[4];

void Init_ADC(void){
    //------------------------------------------------------------------------------
    // V_DETECT_L (0x04) // Pin 2 A2
    // V_DETECT_R (0x08) // Pin 3 A3
    // V_THUMB (0x20) // Pin 5 A5
    //------------------------------------------------------------------------------
    // ADCCTL0 Register
     ADCCTL0 = 0; // Reset
     ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
     ADCCTL0 |= ADCMSC; // MSC
     ADCCTL0 |= ADCON; // ADC ON
    // ADCCTL1 Register
     ADCCTL1 = 0; // Reset
     ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
     ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
     ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
     ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
     ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
     ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
    // ADCCTL1 & ADCBUSY identifies a conversion is in process
    // ADCCTL2 Register
     ADCCTL2 = 0; // Reset
     ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
     ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
     ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
     ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
    // ADCMCTL0 Register
     ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
     ADCMCTL0 |= ADCINCH_2; // V_THUMB (0x20) Pin 5 A5
     ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
     ADCCTL0 |= ADCENC; // ADC enable conversion.
     ADCCTL0 |= ADCSC; // ADC start conversion.

}

void HEXtoBCD(int hex_value) {
      int i;
      int value = 0;

      // Initialize all 4 characters to '0'
      for (i = 0; i < 4; i++) {
        adc_char[i] = '0';
      }

      // Thousands place
      value = 0;
      while (hex_value >= 1000) {
        hex_value -= 1000;
        value++;
      }
      adc_char[0] = 0x30 + value;

      // Hundreds place
      value = 0;
      while (hex_value >= 100) {
        hex_value -= 100;
        value++;
      }
      adc_char[1] = 0x30 + value;

      // Tens place
      value = 0;
      while (hex_value >= 10) {
        hex_value -= 10;
        value++;
      }
      adc_char[2] = 0x30 + value;

      // Ones place
      adc_char[3] = 0x30 + hex_value;
}

void adc_line(char line, char location){
    int i;
    unsigned int real_line;
    real_line = line - 1;
    for(i=0; i < 4; i++) {
        display_line[real_line][i+location] = adc_char[i]; //displays the values from HEXtoBCD onto the display
    }
}


