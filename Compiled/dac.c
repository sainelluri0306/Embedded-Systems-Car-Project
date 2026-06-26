#include  "msp430.h"
#include  "macros.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "wheels.h"

unsigned int DAC_data;

void Init_DAC(void){

  DAC_data = 4000;
  SAC3DAT  = DAC_data;                  // Initial DAC data
  SAC3DAC  = DACSREF_0;                 // Select AVCC as DAC reference
  SAC3DAC |= DACLSEL_0;                 // DAC latch loads when DACDAT written

  SAC3OA   = NMUXEN;                    // SAC Negative input MUX controL
  SAC3OA  |= PMUXEN;                    // SAC Positive input MUX control
  SAC3OA  |= PSEL_1;                    // 12-bit reference DAC source selected
  SAC3OA  |= NSEL_1;                    // Select negative pin input
  SAC3OA  |= OAPM;                      // Select low speed and low power mode
  SAC3PGA  = MSEL_1;                    // Set OA as buffer mode
  SAC3OA  |= SACEN;                     // Enable SAC
  SAC3OA  |= OAEN;                      // Enable OA

  P3OUT   &= ~DAC_CNTL_3;                 // Set output to Low
  P3DIR   &= ~DAC_CNTL_3;                 // Set direction to input
  P3SELC  |=  DAC_CNTL_3;                 // DAC_CNTL DAC operation
  SAC3DAC |=  DACEN;                    // Enable DAC

  DAC_data = DAC_Begin;
  TB0CTL |= TBIE;
  TB0CTL &= ~TBIFG;

}

// The interrupt is not used
#pragma vector = SAC1_SAC3_VECTOR
__interrupt void SAC3_ISR(void){
  switch(__even_in_range(SAC0IV,SACIV_4)){
  case SACIV_0: break;
  case SACIV_2: break;
  case SACIV_4:
//   DAC_data++;
//   DAC_data &= 0xFFF;
//   SAC3DAT = DAC_data;                 // DAC12 output positive ramp
    break;
  default: break;
  }
}
