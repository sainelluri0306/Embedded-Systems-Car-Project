/*
 * description: includes function headers for use globally
 * functions.h
 * Created on: Aug 2025
 * Author: Sai Nelluri
 */

// Main
void main(void);
void Straight_BLD_case(void);
void movement_statemachine(void);

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter
void Init_ADC(void);
void HEXtoBCD(int hex_value);
void adc_line(char line, char location);
void wait1_BLD_case(void);
void Straight_BLD_case(void);
void wait2_BLD_case(void);
void Clockwise_BLD_case(void);
void wait3_BLD_case(void);
void LineFollowing_BLD_case(void);
void wait4_BLD_case(void);
void Clockwise1_BLD_case(void);
void wait5_BLD_case(void);
void end_BLD_case(void);

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
void Display_Elapsed_Time(void);

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
void Init_Ports_1(void);
void Init_Ports_2(void);
void Init_Ports_3(char smclk);
void Init_Ports_4(void);
void Init_Ports_5(void);
void Init_Ports_6(void);

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
void Run_Straight(void);
void run_case(void);
void Run_Circle(void);
void Run_FIG8(void);
void Run_Triangle(void);

// Function Prototypes
void Carlson_StateMachine(void);
void calibrate_BoW(void);

void Init_Serial_UCA1 (char speed);
void Init_Serial_UCA0 (void);
void uart0_puts(char *s);
void startup_cmds(void);
int wait_for_ok(void);
int wait_for_ip(void);
void read_esp_ip(void);

//wheels.h
void stop_all (void);
void Forward_Move(void);
void Forward_Off(void);
void Reverse_Off(void);
void Forward_On(void);
void Right_Forward (void);
void Right_Reverse (void);
void Left_Forward (void);
void Left_Reverse (void);
void Right_Off (void);
void Left_Off (void);
void checking (void);
void clockwiser_left (void);
void clockwiser_right (void);
void Left_Forward_BLD (void);
void Right_Forward_BLD (void);
void Forward_Move_ARC(void);

//movement_Statemachine.c
void forward_moving(void);
void reverse_moving(void);
void fifteen_deg_left_turning(void);
void fifteen_deg_right_turning(void);
void fifteen_deg_turning_R(void);
void fifteen_deg_turning_L(void);
void ninty_deg_turning_R(void);
void ninty_deg_turning_L(void);
void black_line_detection(void);
void Right_Forward_Slow (void);
void bld_setup(void);
void Forward_Move_BLD(void);
static void handle_cmd(char cmd, const char *msg);
void ping_google(void);

//commands.c
int queue_empty(void);
int queue_full(void);
void enqueue_command(const char *cmd);
int dequeue_command(char *cmd_out);
void cmd_parsing(void);
void Reverse_Move(void);
void Init_DAC(void);
