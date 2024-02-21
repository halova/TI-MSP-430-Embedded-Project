//===========================================================================
// File Name : led.c
//
// Description: This file contains the Displays function
//
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

//Global varriables
extern char display_line[4][11];
unsigned char adc_char[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char one_time;
extern volatile unsigned int Time_Sequence;

void Display_Process(void);
//===========================================================================
// Function name: Display_Process
//
// Description: This function check if the update_display is TRUE, if so change
// the display
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}

void Carlson_StateMachine(void){
    switch(Time_Sequence){
      case 250:                        //
        if(one_time){
          Init_LEDs();
          //lcd_BIG_mid();
          display_changed = 1;
          one_time = 0;
        }
        Time_Sequence = 0;             //
        break;
      case 200:                        //
        if(one_time){
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 150:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = 0;
        }
        break;
      case 100:                         //
        if(one_time){
                                       //lcd_4line();
          //lcd_BIG_bot();
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = 1;
          one_time = 0;
        }
        break;
      case  50:                        //
        if(one_time){
          P1OUT &= ~RED_LED;           // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = 0;
        }
        break;                         //
      default: break;
    }
}


//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(int hex_value){
      int value = 0;
      for(int i = 0; i < 4; i++) {
      adc_char[i] = '0';
      }
      while (hex_value > 999){
      hex_value = hex_value - 1000;
      value = value + 1;
      adc_char[0] = 0x30 + value;
      } 
      value = 0;
      while (hex_value > 99){
      hex_value = hex_value - 100;
      value = value + 1;
      adc_char[1] = 0x30 + value;
      }
      value = 0;
      while (hex_value > 9){
      hex_value = hex_value - 10;
      value = value + 1;
      adc_char[2] = 0x30 + value;
      }
      adc_char[3] = 0x30 + hex_value;
}
//-----------------------------------------------------------------
//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it 
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){
//-------------------------------------------------------------
      int i = 0 ;
      for(i = 0; i < 4; i++) {
      display_line[line][i+location] = adc_char[i];
      }
      display_changed = TRUE;
}
//------------------------------------------------------------

