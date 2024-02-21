//===========================================================================
// File Name : init.c
//
// Description: This file contains the Initialization for Init_Conditions
// and Init_LEDs
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned char update_display;


//===========================================================================
// Function name: Init_Conditions
//
// Description: This function set up initital condition for display_line
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;
  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;

  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}
//===========================================================================
// Function name: Init_Conditions
//
// Description: This function set up initital condition for both LED
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}

void Init_Serial(void){
  Init_Serial_UCA0();
}

void Init_Serial_UCA0(void){
        // Configure eUSCI_A0 for UART mode
        UCA0CTLW0 = 0;
        UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
        UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
        UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
        UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
        UCA0CTLW0 &= ~UCPEN; // No Parity
        UCA0CTLW0 &= ~UCSYNC;
        UCA0CTLW0 &= ~UC7BIT;
        UCA0CTLW0 |= UCMODE_0;

        // Configure UART 0
        UCA0CTLW0 = 0; // Use word register
        UCA0CTLW0 |= UCSWRST; // Set Software reset enable
        UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
        
        // Default Baurd rate = 115,200
        UCA0BRW    = 4;
        UCA0MCTLW  = 0x5551 ;
        UCA0CTLW0 &= ~UCSWRST;  // Set Software reset enable
        UCA0TXBUF  = 0x00;      // Prime the Pump of TX
        UCA0IE    |= UCRXIE;    // Enable RX interrupt
        
}




