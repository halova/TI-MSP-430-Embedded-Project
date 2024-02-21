//===========================================================================
// File Name : wheels.c
//
// Description: This file contains the Initialization for all wheel control
// 
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>
///////////////////////
unsigned int delay_between;
unsigned int delay_between_slow;
extern volatile unsigned char one_time;
unsigned char BLACK_LINE;
unsigned char ready_find_line;
unsigned char Find_line_event;

extern unsigned int CIRCLE_COUNT;

extern unsigned char event;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;

extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern unsigned char done_counter;

void Run_Straight(void){
    if(one_time){
       ALL_Off();
       one_time = 0;
       Forward_Move();
     }
}

void Run_Reserve(void){
    if(one_time){
       ALL_Off();
       one_time = 0;
       Reverse_Move();
   }
}

void Run_Left(void){
   if(one_time){
       ALL_Off();
       one_time = 0;
       Turn_Left();
   }    
}
void Run_Right(void){
   if(one_time){
       ALL_Off();
       one_time = 0;
       Turn_Right();
   }    
}
void Run_Last(void){
  if(one_time){
       ALL_Off();
       one_time = 0;
       LEFT_FORWARD_SPEED   = L_LAST;
       RIGHT_FORWARD_SPEED  = R_LAST;
   }    
}
// End Normal Command //
////////////////////////////////////////////
// Begin Auto Command function //
void Run_Find(void){
       switch(Find_line_event){
       case FIND_ARC: // Begin
       if (!ready_find_line){
            strcpy(display_line[1], " BL START ");
            wait_case();
            display_changed = TRUE;
         }
       else
            run_Find_Arc();
       break; //
       
       case FIND_TURN: // Run
       if (!ready_find_line){
            strcpy(display_line[1], "INTERCEPT  ");
            wait_case();
            display_changed = TRUE;
         }
       else{
            strcpy(display_line[1], " BL TURN  ");
            run_Find_Turn();
            display_changed = TRUE;
          }
       break; //
       case FOLLOW_LINE: // Run
       if (!ready_find_line){
            wait_case();
         }
       else{
            strcpy(display_line[1], " BL TRAVEL ");
            display_changed = TRUE;
            run_Follow_line();
       }
       break; //
       case FIND_CIRCLE: // Run
       if (!ready_find_line){
            wait_case();
         }
       else{
            strcpy(display_line[1], " BL CIRCLE ");
            display_changed = TRUE;
            run_Find_Circle();
       }
       break; //
       case FIND_CIRCLE_2: // Run
       if (!ready_find_line){
            wait_case();
         }
       else{
            strcpy(display_line[1], " BL CIRCLE ");
            display_changed = TRUE;
            run_Find_Circle_2();
       }
       break; //
       default: break;
       }
}

void wait_case(void){
   if(one_time){
     ALL_Off();
     one_time = 0;
     // Wait 5 seconds here //
     if (delay_between++ >= WAITINGBETWEEN){
            delay_between = 0;
            ready_find_line = TRUE;
        }
   }
}

void run_Find_Arc(void){
    if(one_time){
       ALL_Off();
       one_time = 0;
        if (ADC_Left_Detect > BL_VALUE && ADC_Right_Detect > BL_VALUE ){
              ready_find_line = FALSE;
              Find_line_event = FIND_TURN;
              }
        else {
        if (delay_between_slow++ >= WAITING_ARC){
            Forward_Move_Slow();
            }
        else{
          // Go arc here //
             Arc_Move();
        }   
     }
  }
}  

void run_Find_Turn(void){
    if(one_time){
       ALL_Off();
       one_time = 0;
       if ( ADC_Left_Detect > BL_VALUE && ADC_Right_Detect > BL_VALUE ){
            ready_find_line = FALSE;
            Find_line_event = FOLLOW_LINE;
       }
       else{
          // Turn Right here
          RIGHT_FORWARD_SPEED  = R_TURN_SLOW;
          LEFT_REVERSE_SPEED   = L_TURN_SLOW;
       }
     
  }
}

void run_Follow_line(void){
   if(one_time){
       one_time = 0;
       ALL_Off();
       if (delay_between++ >= WAITING_LINE){
            ready_find_line = FALSE;
            delay_between = 0;
            Find_line_event = FIND_CIRCLE;
        }
       else {
       if ( ADC_Left_Detect < CR_VALUE || ADC_Right_Detect < CR_VALUE ){
         if ( ADC_Left_Detect < CR_VALUE)
         {
           // Right go fast
         LEFT_FORWARD_SPEED  = L_LINE_SSLOW;
         RIGHT_FORWARD_SPEED = R_LINE_SLOW;
         }
         else if (ADC_Right_Detect < CR_VALUE)
         {
           // Left go fast
         LEFT_FORWARD_SPEED  = L_LINE_SLOW;
         RIGHT_FORWARD_SPEED = R_LINE_SLOW;
         } 
        }
       else if (ADC_Left_Detect > CR_VALUE || ADC_Right_Detect > CR_VALUE )
          {
            LEFT_FORWARD_SPEED  = L_LINE;
            RIGHT_FORWARD_SPEED = R_LINE;
          }
      }
   }    
}

void run_Find_Circle(void){
   if(one_time){
       one_time = 0;
       ALL_Off();
       if (delay_between++ >= WAITING_CIRCLE){
            ready_find_line = FALSE;
            delay_between = 0;
            Find_line_event = FIND_CIRCLE_2;
        }
       else {
       if ( ADC_Left_Detect < CR_VALUE || ADC_Right_Detect < CR_VALUE ){
         if (ADC_Right_Detect < CR_VALUE)
         {
           // Left go fast
         LEFT_FORWARD_SPEED  = L_CIRCLE_SLOW;
         RIGHT_FORWARD_SPEED = R_CIRCLE_SLOW;
         }     
         else if ( ADC_Left_Detect < CR_VALUE)
         {
           // Right go fast
         LEFT_FORWARD_SPEED  = L_CIRCLE_SSLOW;
         RIGHT_FORWARD_SPEED = R_CIRCLE_SLOW;
         }
        }
       else if (ADC_Left_Detect > CR_VALUE || ADC_Right_Detect > CR_VALUE )
       {
         // Right go fast
        LEFT_FORWARD_SPEED  = L_CIRCLE;
        RIGHT_FORWARD_SPEED = R_CIRCLE;
       }
       }
   }    
}
void run_Find_Circle_2(void){
   if(one_time){
       one_time = 0;
       ALL_Off();
       if ( ADC_Left_Detect < CR_VALUE || ADC_Right_Detect < CR_VALUE ){
         if (ADC_Right_Detect < CR_VALUE)
         {
           // Left go fast
         LEFT_FORWARD_SPEED  = L_CIRCLE_SLOW;
         RIGHT_FORWARD_SPEED = R_CIRCLE_SLOW;
         }     
         else if ( ADC_Left_Detect < CR_VALUE)
         {
           // Right go fast
         LEFT_FORWARD_SPEED  = L_CIRCLE_SSLOW;
         RIGHT_FORWARD_SPEED = R_CIRCLE_SLOW;
         }
        }
       else if (ADC_Left_Detect > CR_VALUE || ADC_Right_Detect > CR_VALUE )
       {
         // Right go fast
        LEFT_FORWARD_SPEED  = L_CIRCLE;
        RIGHT_FORWARD_SPEED = R_CIRCLE;
       }
   }
}
void Run_Exit(void){
  if(one_time){
     ALL_Off();
     one_time = 0;
     // Wait 5 seconds here //
     if (delay_between++ >= WAITINGBETWEEN/1.5){
            //delay_between = 0;
            ALL_Off();
            strcpy(display_line[1], " BL STOP  ");
            display_line[2][0] = 'T';
            display_line[2][1] = 'I';
            display_line[2][2] = 'M';
            display_line[2][3] = 'E';
            display_line[2][4] = ':';
            display_changed = TRUE;
            done_counter = TRUE;
        }
     else 
     {
        display_line[2][0] = 'A';
        display_line[2][1] = 'U';
        display_line[2][2] = 'T';
        display_line[2][3] = 'O';
         strcpy(display_line[1], " BL EXIT  ");
         display_changed = TRUE;
         Forward_Move();
     }
   }
}
///////////////////////////////
void Forward_Move(void){
    LEFT_FORWARD_SPEED   = L_SLOW;
    RIGHT_FORWARD_SPEED  = R_SLOW;
}
void Forward_Move_Slow(void){
    LEFT_FORWARD_SPEED   = L_SSLOW;
    RIGHT_FORWARD_SPEED  = R_SSLOW;
}
void Reverse_Move(void){
    LEFT_REVERSE_SPEED   = R_SLOW;
    RIGHT_REVERSE_SPEED  = L_SLOW;
}
void Turn_Left(void){
    LEFT_FORWARD_SPEED   = L_SSLOW;
    RIGHT_REVERSE_SPEED  = R_SSLOW;
}
void Turn_Right(void){
    LEFT_REVERSE_SPEED   = L_SSLOW;
    RIGHT_FORWARD_SPEED  = R_SSLOW;
}
void ALL_Off(void){
    RIGHT_FORWARD_SPEED  = WHEEL_OFF;
    LEFT_FORWARD_SPEED   = WHEEL_OFF;
    RIGHT_REVERSE_SPEED  = WHEEL_OFF;
    LEFT_REVERSE_SPEED   = WHEEL_OFF;
}
/////////////////////
void Arc_Move(void){
    LEFT_FORWARD_SPEED  = L_ARC;
    RIGHT_FORWARD_SPEED = R_ARC;
}
//////////////////////////////////

void Turn_IR(void){
      P2OUT |=  IR_LED;       // Turn on IR 
      event = FIND_LINE;
      Find_line_event = FIND_ARC;
}

