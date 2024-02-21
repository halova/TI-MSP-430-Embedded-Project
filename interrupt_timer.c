//===========================================================================
// File Name : interrupt_timer.c
//
// Description: This file contains the Initialization for Timer interupt
// 
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

volatile unsigned int Time_Sequence;
volatile unsigned char one_time;
unsigned int count;
unsigned int display_count;
unsigned int timer;
unsigned int sec_count;
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
// Variable for project 9
unsigned int go_straight_timer;
unsigned int go_reverse_timer;
unsigned int go_left_timer;
unsigned int go_right_timer;
unsigned int go_last_timer;
unsigned int ready_timer;
extern unsigned char event;
unsigned char is_ready;
extern unsigned char first_command;
extern char display_line[4][11];
unsigned char done_counter = FALSE;

//////////////////////////////////
#pragma vector = TIMER0_B0_VECTOR // Timer B0 – 0 Capture compare
__interrupt void Timer0_B0_ISR(void){
//--------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//--------------------------------------------------------------------
      // LCD Backlight
     if(display_count++ > DISPLAY_POLL){
       display_count = 0;       // Reset for next count
       // Update display here
       update_display = 1;    // Update ar rate 200 ms
     }
     // Time Sequence
     one_time = 1;
     if (first_command && !done_counter){
     if ( timer++ >= 100 ){ 
       timer = 0;
       sec_count++; 
       HEXtoBCD(sec_count);
       display_line[2][9] = 's';
       adc_line(2,5);
       }
     }
     
     // Time sequence update at rate 10 ms
     if(Time_Sequence++ > 250){
        Time_Sequence = 0;
     }
     // Timer for default command
     if ( ready_timer ++ > 60){
          ready_timer = 0;
          is_ready    = TRUE;
     }

     // Timer for movement //
     if ( event == STRAIGHT) {
       if (go_straight_timer++ > St_timer){
            go_straight_timer = 0;
            event = NONE;
       }
     }
     if ( event == RESERVE) {
       if (go_reverse_timer++ > St_timer/5){
            go_reverse_timer = 0;
            event = NONE;
       }
     }
     
     if ( event == LEFT) {
       if (go_left_timer++ > St_timer/5){
            go_left_timer = 0;
            event = NONE;
       }
     }
     
     if ( event == RIGHT ) {
       if (go_right_timer++ > St_timer/5){
            go_right_timer = 0;
            event = NONE;
       }
     }
     if ( event == LAST) {
       if (go_last_timer++ > St_timer){
            go_last_timer = 0;
            event = NONE;
       }
     }

     TB0CCR0 += TB0CCR0_INTERVAL; // Add interval Offset to TACCR0
//--------------------------------------------------------------------
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
        case 0: break; // No interrupt
        
        case 2: // CCR1      
        if(count ++ > DEBOUNCE_TIMER ){
            count = 0; // Reset for next count
            TB0CCTL1 &= ~CCIE;
            P4IE |= SW1;
            // Do something here, will happend after debounce = 1 sec
         }
        else 
        TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
        break;
        
        case 4: // CCR2
        /*
         Disable Timer B0 CCR2
        2. Clear SW2 Interrupt Flag
        3. Enable SW2 Interrupt
        */
        if(count ++ > DEBOUNCE_TIMER ){
            count = 0; // Reset for next count
            TB0CCTL2 &= ~CCIE;
            P2IE |= SW2;
            // Do something here, will happend after debounce = 1 sec
            
           }
        else
        TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
        break;
        case 14: // overflow
        //
        break;
        default: break; 
}
//----------------------------------------------------------------------------
}
