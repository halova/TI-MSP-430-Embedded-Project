//===========================================================================
// File Name : switch.c
//
// Description: This file contains the Initialization for all switch 
// 
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>

extern unsigned int count;
extern char display_line[4][11];
extern volatile unsigned char display_changed;
char switch_1;
char default_command_status;
extern char         transmit_buffer[LARGE_RING_SIZE];
#pragma vector = PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
      // Switch 1 
      if (P4IFG & SW1) {
        //P4IE |= SW1;   // P4.1 SW1 interrupt Enabled 
        count = 0;
        P4IE  &= ~SW1;    // Disable SW1
        P4IFG &= ~SW1;    // IFG SW1 flag cleared
        
        // Do something 
        //P2OUT |=  IR_LED;
        // Clear CC1 and enable //
        TB0CCTL1 &= ~CCIFG;
        TB0CCTL1 |= CCIE;
  
      }            
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
// Switch 2 
     if (P2IFG & SW2) { 
        //P2IE |= SW2;   // P2 SW2 interrupt Enabled   
        count =0;
        P2IE  &= ~SW2;        // Disable SW2
        P2IFG &= ~SW2;        // IFG SW2 cleared
        
        // DO something 
        //strcpy(transmit_buffer,"AT+CWJAP?\r\n");
        //USCI_A0_transmit();

        // Clear CC2 and enable //
        TB0CCTL2 &= ~CCIFG;
        TB0CCTL2 |= CCIE;
      }
}
























