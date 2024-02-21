//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Phan Nguyen
//  01/2023
//  Built with IAR Embedded Workbench Version: 8.10.2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"

// Function Prototypes
void main(void);

// Global Variables
extern char display_line[4][11];
extern volatile unsigned char display_changed;
//
extern unsigned char first_command;
extern unsigned char event;
extern unsigned char state;
unsigned int location_counter = 0x30;
extern unsigned char Got_IP;
void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
  PM5CTL0 &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC
  Init_Serial();                      // Initialize Serial

  
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  for (int i =0 ;i <4 ;i++) 
    strcpy(display_line[i],"          ");
  display_changed = TRUE;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    Carlson_StateMachine();            // Run a Time Based State Machine
    Display_Process();                 // Update Display
    P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
    
    if (!Got_IP)
        Default_command(); 
    IOT_Process();
    
    //Check_queue();
    if (first_command ){ 
       strcpy(display_line[0]," NGUYEN    ");
       if ( event != FIND_LINE){
        display_line[1][0] = 'A';
        display_line[1][1] = 'R';
        display_line[1][2] = 'R';
        display_line[1][3] = 'I';
        display_line[1][4] = 'V';
        display_line[1][5] = 'E';
        display_line[1][6] = 'D';
        display_line[1][7] = ':';
        display_line[1][8] = '0';
        display_line[1][9] = location_counter;
        display_line[2][2] = ' ';
        display_line[2][3] = ' ';
        display_line[2][4] = ' ';
        lcd_BIG_mid();
        }
       else 
       {
        display_line[2][0] = 'A';
        display_line[2][1] = 'U';
        display_line[2][2] = 'T';
        display_line[2][3] = 'O';
       }
       display_changed = TRUE;
    }

    switch(event){
       case STRAIGHT:
        Run_Straight();
        break;
       case RESERVE:
        Run_Reserve();
        break;
       case LEFT:
        Run_Left();
        break;
       case RIGHT:
        Run_Right();
        break;
       case LAST:
        Run_Last();
        break;
       case IR:
        Turn_IR();
        break;
       case FIND_LINE:
        Run_Find();
        break;
       case EXIT:
        Run_Exit();
        break;
       case NONE:
        ALL_Off();
        break;
       default: 
        break;
     } 
    

     
  }
//------------------------------------------------------------------------------
}



