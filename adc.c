//===========================================================================
// File Name : adc.c
//
// Description: This file contains the Initialization for ADC and ADC interrupt
// 
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

unsigned int ADC_Channel;
unsigned int ADC_Left_Detect;
unsigned int ADC_Right_Detect;
unsigned int ADC_Thumb;

extern unsigned char event;
extern unsigned char state;
extern unsigned char Find_line_event;


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
      ADCMCTL0 |= ADCINCH_2; // 
      //
      ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
      ADCCTL0 |= ADCENC; // ADC enable conversion.
      ADCCTL0 |= ADCSC; // ADC start conversion.
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
      switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
      case ADCIV_NONE:
      break;
      case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
      // before its previous conversion result was read.
      break;
      case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
      break;
      case ADCIV_ADCHIIFG: // Window comparator interrupt flags
      break;
      case ADCIV_ADCLOIFG: // Window comparator interrupt flag
      break;
      case ADCIV_ADCINIFG: // Window comparator interrupt flag
      break;
      
      case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC; // Disable ENC bit.
      switch (ADC_Channel++){
      ////////
      case 0x00: // Channel A2 Interrupt
      ADC_Left_Detect = ADCMEM0; // Move result into Global Values
      ADC_Left_Detect = ADC_Left_Detect >> 2;
      //HEXtoBCD(ADC_Left_Detect); // Convert result to String
      //adc_line(1,6); // Place String in Display 
      //
      ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
      break;
      ////////
      case 0x01: // Channel A3 Interrupt
      ADC_Right_Detect = ADCMEM0; // Move result into Global Values
      ADC_Right_Detect = ADC_Right_Detect >> 2;
      //HEXtoBCD(ADC_Right_Detect); // Convert result to String
      //adc_line(2,6); // Place String in Display 
      //
      ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
      break;
      ////////
      case 0x02:
      ADC_Thumb = ADCMEM0; // Move result into Global Values
      ADC_Thumb = ADC_Thumb  >>2;
      //HEXtoBCD(ADC_Thumb); // Convert result to String
      //adc_line(3,6); // Place String in Display 
      //
      ADCMCTL0    &= ~ADCINCH_5; // Disable Last channel A5
      ADCMCTL0    |= ADCINCH_2; // Enable First channel A2 
      ADC_Channel = 0;
      break; 
      default:
      break;
      }
      ADCCTL0 |= ADCENC; // Enable Conversions
      ADCCTL0 |= ADCSC; // Start next sample
      
      break;
      default:
      break;
      }
}
