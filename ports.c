//===========================================================================
// File Name : ports.c
//
// Description: This file contains the Initialization for all port pins
//
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

//===========================================================================
// Function name: Init_Port1
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================

void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3(USE_SMCLK);
  Init_Port4();
  Init_Port5();
  Init_Port6();
}


// Port 1 Pins
void Init_Port1(void){
    P1DIR = 0x00; // Set P1 direction to input
    P1OUT = 0x00; // P1 set Low

    P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
    P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
    P1OUT |= RED_LED; // Set Red LED On
    P1DIR |= RED_LED; // Set Red LED direction to output

    P1SELC |= V_A1_SEEED; // ADC input for A1_SEEED

    P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L

    P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R

    P1SELC |= V_A4_SEEED; // ADC input for V_A4_SEEED

    P1SELC |= V_THUMB; // ADC input for V_THUMB

    P1SEL0 |= UCA0TXD;          // UCA0TXD pin
    P1SEL1 &= ~UCA0TXD;         // UCA0TXD pin

    P1SEL0 |= UCA0RXD;          // UCA0RXD pin
    P1SEL1 &= ~UCA0RXD;         // UCA0RXD pin

}

//===========================================================================
// Function name: Init_Port2
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================

void Init_Port2(void){ // Configure Port 2
//------------------------------------------------------------------------------
    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to input

    P2SEL0 &= ~RESET_LCD;        // RESET_LCD GPIO operation
    P2SEL1 &= ~RESET_LCD;        // RESET_LCD GPIO operation
    P2OUT &= ~RESET_LCD;          // Initial Value = High / On
    P2DIR |= RESET_LCD;          // Direction = output

    P2SEL0 &= ~CHECK_BAT;        // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT;        // CHECK_BAT GPIO operation
    P2OUT &= ~CHECK_BAT;         // Initial Value = Low / Off
    P2DIR |= CHECK_BAT;          // Direction = output

    P2SEL0 &= ~IR_LED;           // P2_2 GPIO operation
    P2SEL1 &= ~IR_LED;           // P2_2 GPIO operation
    P2OUT &=  ~IR_LED;            // Initial Value = Low / Off
    P2DIR |= IR_LED;             // Direction = output
     
     // Pin 3 
     P2SEL0 &= ~SW2; // SW2 Operation 
     P2SEL1 &= ~SW2; // SW2 Operation 
     P2OUT |= SW2; // Configure pullup resistor 
     P2DIR &= ~SW2; // Direction = input 
     P2REN |= SW2; // Enable pullup resistor 
     P2IES |= SW2; // HI/LO EDGE INTERRUPT 
     P2IFG &= ~SW2; // ifg sw1 cleared 
     P2IE |= SW2; // sw1 interrupt enable

     // Pin 4 
    P2SEL0 &= ~IOT_RUN_RED;      // IOT_RUN_CPU GPIO operation
    P2SEL1 &= ~IOT_RUN_RED;      // IOT_RUN_CPU GPIO operation
    P2OUT  &= ~IOT_RUN_RED;      // Initial Value = Low / Off
    P2DIR |= IOT_RUN_RED;        // Direction = output

    P2SEL0 &= ~DAC_ENB;          // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB;          // DAC_ENB GPIO operation
    P2OUT  &= ~DAC_ENB;            // Initial Value = High
    P2DIR  |= DAC_ENB;            // Direction = output

    P2SEL0 &= ~LFXOUT;           // LFXOUT Clock operation
    P2SEL1 |= LFXOUT;            // LFXOUT Clock operation

    P2SEL0 &= ~LFXIN;            // LFXIN Clock operation
    P2SEL1 |= LFXIN;             // LFXIN Clock operation

//------------------------------------------------------------------------------
}

//===========================================================================
// Function name: Init_Port3
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================


void Init_Port3(char smclk){
    P3OUT = 0x00; // P3 set Low
    P3DIR = 0x00; // Set P3 direction to output
// P3 PIN 0
    P3SEL0 &= ~TEST_PROBE;      // TEST_PROBE operation
    P3SEL1 &= ~TEST_PROBE;      // TEST_PROBE operation
    P3OUT  &= ~TEST_PROBE;
    P3DIR  &= ~TEST_PROBE;      // TEST_PROBE set to Input
// P3 PIN 1
    P3SEL0 &= ~OA2O; // OA2O GPIO operation 
    P3SEL1 &= ~OA2O; // OA2O GPIO operation 
    P3OUT  &= ~OA2O; // Set OA2O OFF [Low] 
    P3DIR  |= OA2O; // Set direction to output
// P3 PIN 2
    P3SEL0 &= ~OA2N; // OA2N GPIO operation 
    P3SEL1 &= ~OA2N; // OA2N GPIO operation 
    P3OUT  &= ~OA2N; // Set OA2N OFF [Low] 
    P3DIR  |= OA2N; // Set direction to output 
// P3 PIN 3
    P3SEL0 &= ~OA2P; // OA2P GPIO operation 
    P3SEL1 &= ~OA2P; // OA2P GPIO operation 
    P3OUT  &= ~OA2P; // Set OA2P OFF [Low] 
    P3DIR  |= OA2P; // Set direction to output 
// P3 PIN 4
    P3SEL1 &= ~SMCLK; // SMCLK GPIO operation 
    P3SEL0 &= ~SMCLK; // SMCLK GPIO operation 
    P3OUT  &= ~SMCLK; // Set SMCLK OFF [Low] 
    P3DIR  |= SMCLK; // Set direction to output
// P3 PIN 5
     P3SEL0 &= ~DAC_CNTL; // DAC_CNTL GPIO operation 
     P3SEL1 &= ~DAC_CNTL; // DAC_CNTL DAC/GPIO operation 
     P3OUT  &= ~DAC_CNTL; // Set DAC_CNTL On [High] 
     P3DIR  &= ~DAC_CNTL; // Set direction to output 
// Pin 6 
     P3SEL0 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation 
     P3SEL1 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation 
     P3OUT  &= ~IOT_LINK_GRN; // IOT_LINK_GRN LED is off 
     P3DIR  |= IOT_LINK_GRN; // Set direction to output 
// Pin 7 
     P3SEL0 &= ~IOT_EN;  // IOT_EN GPIO operation 
     P3SEL1 &= ~IOT_EN;  // IOT_EN GPIO operation 
     P3OUT  |= IOT_EN;   // Set IOT_EN On [High] 
     P3DIR  |= IOT_EN;   // Set direction to output 

}

//===========================================================================
// Function name: Init_Port4
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================

void Init_Port4(void){
    P4OUT = 0x00; // P4 set Low
    P4DIR = 0x00; // Set P4 direction to output
// P4 PIN 0
    P4SEL0 &= ~DAC_CNTL1; 			// DAC_CNTL1 GPIO operation
    P4SEL1 &= ~DAC_CNTL1; 			// DAC_CNTL1 GPIO operation
    P4DIR  &= ~DAC_CNTL1; 			// Direction to input
// P4 PIN 1
    P4SEL0 &= ~SW1; // SW1 set as I/0
    P4SEL1 &= ~SW1; // SW1 set as I/0
    P4DIR &= ~SW1; // SW1 Direction = input
    P4OUT |= SW1; // Configure pull-up resistor SW1
    P4REN |= SW1; // Enable pull-up resistor SW1
    P4IES |= SW1; // SW1 Hi/Lo edge interrupt
    P4IFG &= ~SW1; // IFG SW1 cleared
    P4IE |= SW1; // SW1 interrupt Enabled
// P4 PIN 2
    P4SEL0 |= UCA1TXD; 				// USCI_A1 UART operation
    P4SEL1 &= ~UCA1TXD; 			// USCI_A1 UART operation
// P4 PIN 3
    P4SEL0 |= UCA1RXD; 				// USCI_A1 UART operation
    P4SEL1 &= ~UCA1RXD; 			// USCI_A1 UART operation
// P4 PIN 4
    P4SEL0 &= ~UCB1_CS_LCD; 		        // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD; 		        // UCB1_CS_LCD GPIO operation
    P4OUT |= UCB1_CS_LCD; 			// Set SPI_CS_LCD On       [High]
    P4DIR |= UCB1_CS_LCD; 			// Set SPI_CS_LCD direction to output
// P4 PIN 5
    P4SEL0 |= UCB1CLK; 				// UCB1CLK SPI BUS operation
    P4SEL1 &= ~UCB1CLK; 			// UCB1CLK SPI BUS operation
// P4 PIN 6
    P4SEL0 |= UCB1SIMO; 			// UCB1SIMO SPI BUS operation
    P4SEL1 &= ~UCB1SIMO; 			// UCB1SIMO SPI BUS operation
// P4 PIN 7
    P4SEL0 |= UCB1SOMI; 			// UCB1SOMI SPI BUS operation
    P4SEL1 &= ~UCB1SOMI; 			// UCB1SOMI SPI BUS operation

}
//===========================================================================
// Function name: Init_Port5
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================


void Init_Port5(void){
    P5DIR = 0x00; // Set P1 direction to input
    P5OUT = 0x00; // P1 set Low

    P5SELC |= V_BAT; // ADC input for V_BAT

    P5SELC |= V_5_0; // ADC input for V_BAT

    P5SELC |= V_DAC; // ADC input for V_DAC

    P5SELC |= V_3_3; // ADC input for V_3_3

    P5SEL0 &= ~IOT_BOOT;     // IOT_BOOT GPIO operation
    P5SEL1 &= ~IOT_BOOT;     // IOT_BOOT GPIO operation
    P5OUT |= IOT_BOOT;       // Set Output value active
    P5DIR |= IOT_BOOT;       // Set direction to output

}

//===========================================================================
// Function name: Init_Port6
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================

void Init_Port6(void){
    P6OUT = 0x00; // P6 set Low
    P6DIR = 0x00; // Set P6 direction to output
// P6 PIN 0
    P6SEL0 |=  LCD_BACKLITE;        // LCD_BACKLITE Operation
    P6SEL1 &= ~LCD_BACKLITE;        // LCD_BACKLITE 
    P6DIR  |=   LCD_BACKLITE;        // Direction = output
// P6 PIN 1
    P6SEL0 |= ~R_FORWARD;     	    // R_FORWARD Operation
    P6SEL1 &= ~R_FORWARD;    	    // R_FORWARD Operation
    P6DIR  |=  R_FORWARD;           // Direction = output
// P6 PIN 2.
    P6SEL0 |= ~R_REVERSE;           // R_REVERSE Operation
    P6SEL1 &= ~R_REVERSE;           // R_REVERSE Operation
    P6DIR  |=  R_REVERSE;           // Direction = output
// P6 PIN 3
    P6SEL0 |= ~L_FORWARD;     	    // L_FORWARD Operation
    P6SEL1 &= ~L_FORWARD;     	    // L_FORWARD Operation
    P6DIR  |=  L_FORWARD;           // Direction = output
// P6 PIN 4
    P6SEL0 |= ~L_REVERSE;           // L_REVERSE Operation
    P6SEL1 &= ~L_REVERSE;           // L_REVERSE Operation
    P6DIR  |=  L_REVERSE;           // Direction = output
// P6 PIN 5
    P6SEL0 &= ~P6_5;                // P6_5 Operation
    P6SEL1 &= ~P6_5;                // P6_5 Operation
    P6OUT  &= ~P6_5;		    // Initial Value = OFF
    P6DIR  |= P6_5;                 // Direction = output
// P6 PIN 6
    P6SEL0 &= ~GRN_LED;             // GRN_LED Operation
    P6SEL1 &= ~GRN_LED;             // GRN_LED Operation
    P6OUT  |= GRN_LED;              // Initial Value = ON
    P6DIR  |= GRN_LED;              // Direction = output
}

