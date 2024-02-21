//===========================================================================
// File Name : interrupt_timer.c
//
// Description: This file contains the Initialization for Serial Interupt
// 
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>

// HOME WIFI IP address 
// 192.168.50.48
// NCSU IP
// 
// Port 1256
// MAC address
// c8:f0:9e:06:37:f8

// global variables
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern unsigned char is_ready;
unsigned char default_command;
unsigned char Got_IP;
// 2 Dimension array for IOT data
char IOT_Data[4][LARGE_RING_SIZE]; 

int  line;
int  nextline;
int  character;
int  read_index;
int  line_command;

// For IOT interupt
unsigned char done_recieve;
int          write_index;
char         received_buffer[LARGE_RING_SIZE];
int          trasmit_index;                                  // Index for reading_buffer
char         transmit_buffer[LARGE_RING_SIZE];              // Size for appropriate Command Length
                         
// Default IOT 
unsigned char first_command;
char         command[5][LARGE_RING_SIZE];
char         ip_address[LARGE_RING_SIZE] ="10.155.10.102";
// Variable for Project 9
unsigned char go_straight_signal;
unsigned char go_reverse_signal;
unsigned char go_left_signal;
unsigned char go_right_signal;
unsigned char event;

unsigned char command_queue[2];
unsigned int  command_queue_index;
unsigned int  waiting;
extern unsigned int location_counter;
extern unsigned int go_straight_timer;
//------------------------------------------------------------------------------
#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
        switch(__even_in_range(UCA0IV,0x08)){
        case 0: // Vector 0 - no interrupt
        break;
        case 2: // Vector 2 - RXIFG
         received_buffer[write_index++] = UCA0RXBUF; // RX -> USB_Char_Rx character
         if (write_index >= (sizeof(received_buffer)) ){
            write_index = BEGINNING; // Circular buffer back to beginning
         }

        break;
        case 4: // Vector 4 – TXIFG 
         UCA0TXBUF = transmit_buffer[trasmit_index];   // Transmit Current Indexed value
         transmit_buffer[trasmit_index++] = 0;         // Null Location of Transmitted value
         if(transmit_buffer[trasmit_index] == 0){   // Is the next pb_index location NULL - End of Command
              UCA0IE &= ~UCTXIE;                 // Disable TX interrupt
          }
        break;
        default: break; 
        }
}

void Default_command(){
  strcpy(command[0],"AT+SYSSTORE=0\r\n");
  strcpy(command[1],"AT+CIPMUX=1\r\n"  );
  strcpy(command[2],"AT+CIPSERVER=1,1256\r\n");
  strcpy(command[3],"AT+CIFSR\r\n");
  
  strcpy(display_line[0], "CONNECTING");
  display_changed = TRUE;
  
  if ( is_ready == TRUE && line_command < 4)
        {
          strcpy(transmit_buffer,command[line_command++]);
          is_ready = FALSE;
          USCI_A0_transmit();
          if ( line_command == 4)
                Got_IP = TRUE;
        }
}  
//------------------------------------------------------------------------------

void USCI_A0_transmit(void){ 
        // Transmit Function for USCI_A0
        // Contents must be in process_buffer
        // End of Transmission is identified by NULL character in process_buffer
        // process_buffer includes Carriage Return and Line Feed
        trasmit_index = 0;           // Set Array index to first location
        UCA0IE |= UCTXIE;       // Enable TX interrupt
}

void IOT_Process(void){ // Process IOT messages
     
        // For putting the recieve character into IOT_data array //
        if(write_index != read_index ){
          IOT_Data[line][character] = received_buffer[read_index++];
        // Loop back
        if(read_index >= sizeof(received_buffer)){
          read_index = BEGINNING;
          }
        
        // if we see a line feed and move to next array //
        if(IOT_Data[line][character] == '\n'){ 
          if(IOT_Data[line][9] == '^' || IOT_Data[line][10] == '^'){
            first_command = TRUE;
            if (IOT_Data[line][9] == '^'){
                event = IOT_Data[line][14];
                display_line[2][0] = event;
                display_line[2][1] = '1';
                display_changed = TRUE;                
                if (event == COUNTER || event == LAST)
                    location_counter++;
             }
            else{
             event = NONE;
             command_queue[0]   = IOT_Data[line][15];
             command_queue[1]   = IOT_Data[line][21];
             command_queue_index = 0;
             }  
          }
          
          // For displaying Ip address, and wifi ssid
          else if ( IOT_Data[line][10] == 'I'){
                strcpy(display_line[0], " WAITING  ");
                strcpy(display_line[1], "FOR INPUT ");
                    for ( int i = 0; i < 11; i++){
                      display_line[2][i] = ip_address[i];
                      //display_line[2][i] = IOT_Data[line][i+14];
                      }
                    for ( int i = 0; i < 3; i++){
                      //display_line[3][i] = IOT_Data[line][i+24];
                      display_line[3][i] = ip_address[i+10];
                      }
                display_changed = TRUE;
          }
          else if ( IOT_Data[line][4] == 'A'){
                strcpy(display_line[0], " GOT WIFI ");
                for (int i = 0; i< 6 ;i ++)
                    display_line[1][i+2] = IOT_Data[line][7+i];
                strcpy(display_line[2], "           ");
                display_changed = TRUE;
          }
          
        // Whatever command is, clear current line
        Clear_line(line);   
        }
        else
          character++;
   }
    

}

// Will clear the current line
void Clear_line(int cur_line){
  character = BEGINNING;
  for ( int i = 0; i< sizeof(IOT_Data[cur_line]) ;i ++)
       IOT_Data[cur_line][i] = 0 ;
  if(++line >= 4){
     line = 0;
   }
}

void Check_queue(void){
  if ( event == NONE && command_queue[command_queue_index] != 0 && waiting++ > WAITINGBETWEEN){
      //UCA0IE &= ~UCRXIE;    // Disable RX interrupt
      waiting = 0;
      event = command_queue[command_queue_index];
      if (event == STRAIGHT)
          go_straight_timer = 0;
      if (event == COUNTER)
          location_counter++;
      display_line[3][0] = event;
      display_changed = TRUE;
      command_queue[command_queue_index++] = 0;
      if ( command_queue_index == 2 )
           command_queue_index = 0;
  }
}















