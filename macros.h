//===========================================================================
// File Name : macros.h
//
// Description: This file contains the global value of somes
//
// Author: Phan Nguyen
// Date: January 2023
// Compiler: Built with IAR Embedded Workbench Version: 8.10.2
//===========================================================================

//LED define
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TRUE                 (0x01) //
#define FALSE                (0x00) //
#define TEST_PROBE           (0x01) // 3.0 TEST PROBE

// Port 1 Pins
#define RED_LED (0x01) 		        // 0 RED LED 0
#define V_A1_SEEED (0x02) 	        // 1 A1_SEEED
#define V_DETECT_L (0x04) 	        // 2 V_DETECT_L
#define V_DETECT_R (0x08) 	        // 3 V_DETECT_R
#define V_A4_SEEED (0x10) 	        // 4 A4_SEEED
#define V_THUMB (0x20) 		        // 5 V_THUMB
#define UCA0RXD (0x40) 		        // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) 		        // 7 Back Channel UCA0TXD

// Port 2 Pins
#define RESET_LCD (0x01) 		// 0 RESET LCD
#define CHECK_BAT (0x02) 		// 1 Check ADC Voltages
#define IR_LED (0x04) 			// 2 IR_LED
#define SW2 (0x08) 		        // 3 SW2
#define IOT_RUN_RED (0x10) 		// 4 IOT_RUN_RED
#define DAC_ENB (0x20)			// 5 DAC_ENB
#define LFXOUT (0x40) 			// 6 XOUTR
#define LFXIN (0x80) 			// 7 XINR

// Port 3 Pins
#define TEST_PROBE (0x01) 		// 0 TEST PROBE
#define OA2O (0x02) 			// 1 OA2O
#define OA2N (0x04) 			// 2 OA2N
#define OA2P (0x08) 			// 3 OA2P
#define SMCLK (0x10) 			// 4 SMCLK
#define DAC_CNTL (0x20) 		// 5 DAC signal from Processor
#define IOT_LINK_GRN (0x40)		// 6 IOT_LINK_GRN
#define IOT_EN (0x80) 			// 7 IOT_EN

// Port 4 Pins
#define DAC_CNTL1 (0x01) 		// 0 DAC_CNTL1
#define SW1 (0x02) 			// 1 SW1
#define UCA1RXD (0x04) 		        // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) 			// 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) 		// 4 Chip Select
#define UCB1CLK (0x20) 			// 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) 		// 6 UCB1SIMO
#define UCB1SOMI (0x80) 		// 7 UCB1SOMI

// PORT 5 PINS
#define V_BAT (0x01) 			// 0 V_BAT GP I/O
#define V_5_0 (0x02) 			// 1 V_5_0 GP I/O
#define V_DAC (0x04) 			// 2 V_DAC GP I/O
#define V_3_3 (0x08) 			// 3 V_3_3 GP I/O
#define IOT_BOOT (0x10) 	        // 4 IOT_BOOT_CPU GP I/O
#define IOT_PROG_MODE (0x10)           // 4 IOT_PROGRAM_MODE
// PORT 6 PINS
#define LCD_BACKLITE (0x01) 		// 0 LCD_BACKLITE
#define R_FORWARD (0x02) 		// 1 R_FORWARD
#define R_REVERSE (0x04)		// 2 R_REVERSE
#define L_FORWARD (0x08) 		// 3 L_FORWARD
#define L_REVERSE (0x10) 		// 4 L_REVERSE
#define P6_5 (0x20) 			// 5 P6_5
#define GRN_LED (0x40)			// 6 GRN_LED

// EVENT
#define STRAIGHT  ('S')
#define RESERVE   ('B')
#define LEFT      ('L')
#define RIGHT     ('R')
#define LAST      ('G')
#define FIND_LINE ('F')
#define IR        ('I')
#define COUNTER   ('U')
#define EXIT      ('Y')
#define NONE      ('N')
// Event for auto find line
#define FIND_ARC         ('Z')
#define FIND_TURN        ('X')
#define FOLLOW_LINE      ('M')
#define FIND_CIRCLE      ('C')
#define FIND_CIRCLE_2    ('T')
// STATES

// 

//For SMCLK
#define USE_GPIO                       (0x00)
#define USE_SMCLK                      (0x01)

// Define for interupt, timer
#define P4PUD (P4OUT)
#define P2PUD (P2OUT)

#define TB0CCR0_INTERVAL                (5000)      // 10 ms
#define TB0CCR1_INTERVAL                (50000)     // 100 ms
#define TB0CCR2_INTERVAL                (50000)     // 
#define DISPLAY_POLL                    (20)        // Poll at 200 ms
#define DEBOUNCE_TIMER                  (10)        // Switch debounce = 10 * 100 ms = 1 s

// Define for CLOCK
#define TBIDEX__1 (0x0000) /* Divide by 1 */
#define TBIDEX__2 (0x0001) /* Divide by 2 */
#define TBIDEX__3 (0x0002) /* Divide by 3 */
#define TBIDEX__4 (0x0003) /* Divide by 4 */
#define TBIDEX__5 (0x0004) /* Divide by 5 */
#define TBIDEX__6 (0x0005) /* Divide by 6 */
#define TBIDEX__7 (0x0006) /* Divide by 7 */
#define TBIDEX__8 (0x0007) /* Divide by 8 */

#define RESET_REGISTER                   (0)
#define TIMER_B0_0_VECTOR                (TIMER0_B0_VECTOR)
#define TIMER_B0_1_OVFL_VECTOR           (TIMER0_B1_VECTOR)

// Define for PWM
#define PWM_PERIOD (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_FORWARD_SPEED (TB3CCR4)
#define LEFT_REVERSE_SPEED (TB3CCR5)

#define WHEEL_PERIOD   (50005)
#define WHEEL_OFF      (0)

#define L_SLOW         (17000)
#define R_SLOW         (15000)

#define L_LAST         (18000)
#define R_LAST         (15000)

#define L_SSLOW         (10000)
#define R_SSLOW         (10000)

#define L_TURN_SLOW       (7000)
#define R_TURN_SLOW       (7000)
//
#define L_ARC             (14000)
#define R_ARC             (10500)
//

#define L_LINE            (8000)
#define R_LINE            (4000)

#define L_LINE_SLOW       (6500)
#define R_LINE_SLOW       (6500)

#define L_LINE_SSLOW      (3500)
#define R_LINE_SSLOW      (3500)
/////////////////////////////////

#define L_CIRCLE          (4000)
#define R_CIRCLE          (8000)

#define L_CIRCLE_SLOW     (6500)
#define R_CIRCLE_SLOW     (6500)

#define L_CIRCLE_SSLOW    (3500)
#define R_CIRCLE_SSLOW    (3500)

#define CIRCLE_FAST      (14000)
#define FAST             (50000)
#define PERCENT_100      (50000)
#define PERCENT_80       (45000)

#define BL_VALUE         (400)
#define CR_VALUE         (500)

#define WAITINGBETWEEN   (500)  
#define WAITING_ARC      (500)
#define WAITING_LINE     (700)
#define WAITING_CIRCLE   (800)

// Define for Serial 
#define BEGINNING               (0)
#define SMALL_RING_SIZE         (16)
#define LARGE_RING_SIZE         (48)

// Timer
#define St_timer               (300)

