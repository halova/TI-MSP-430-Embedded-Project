//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Phan Nguyen
//  Feb 2023
//  Built with IAR Embedded Workbench Version: 8.10.2
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);
void Carlson_StateMachine(void); 

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter
void Turn_IR(void);
// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
void lcd_120(void);

void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char smclk);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// State machine

void wait_case(void);
void  Clear_timer(void);

void Forward_Move(void);
void Forward_Move_Slow(void);
void Reverse_Move(void);
void Turn_Left(void);
void Turn_Right(void);
void ALL_Off(void);
void Arc_Move(void);
// Wheels control

void Run_Straight(void);
void Run_Reserve(void);
void Run_Left(void);
void Run_Right(void);
void Run_Find(void);
void Run_Exit(void);
void Run_Last(void);
// Run case for normal command
void run_case_Straight(void);
void run_case_Reverse(void);
void run_case_Left(void);
void run_case_Right(void);
void Run_case_Straight(void);

// Run case for Auto find Line
void run_Find_Arc(void);
void run_Find_Turn(void);
void run_Follow_line(void);
void run_Find_Circle(void);
void run_Find_Circle_2(void);
void run_Find_Exit(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// ADC function
void HEXtoBCD(int hex_value);
void adc_line(char line, char location);
void Init_ADC(void);

// Serial function
void Init_Serial(void); 
void Init_Serial_UCA0(void); 
void Init_Serial_UCA1(void); 
void Serial_Procces(void);
void IOT_Process(void);
void USCI_A0_transmit(void);
void USCI_A1_transmit(void);
void Default_command(void);
void Clear_line(int cur_line);
void Check_queue(void);










