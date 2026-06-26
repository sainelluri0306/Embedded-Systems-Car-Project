/*
 * description: includes macros/variables for global access
 * macros.h
 * Created on: Aug 30, 2025
 * Author: Sai Nelluri
 */

// macros.h
// General constants, pin definitions, motor speeds, PWM, and state machine

// General
#define ALWAYS               (1)        // Always true
#define TRUE                 (1)        // Boolean true
#define FALSE                (0)        // Boolean false
#define RESET_STATE          (0)        // Default reset state
#define P4PUD                (P4OUT)    // Pull-up/down register alias

// LEDs
#define RED_LED              (0x01)     // RED LED pin 0
#define GRN_LED              (0x40)     // GREEN LED pin 1
#define TEST_PROBE           (0x01)     // Test output probe pin

// Switches
#define SW1                  (0x02)     // Switch 1 input pin
#define SW2                  (0x08)     // Switch 2 input pin

// Switch states
#define PRESSED              (0)        // Switch pressed logic level
#define RELEASED             (1)        // Switch released logic level

// Switch checking
#define OKAY                 (1)        // Check passed
#define NOT_OKAY             (0)        // Check failed

// Debounce timing
#define DEBOUNCE_TIME        (10000)    // Debounce delay
#define DEBOUNCE_RESTART     (0)        // Reset debounce counter

// Clock Pins
#define USE_GPIO             (0x00)     // Use GPIO clock
#define USE_SMCLK            (0x01)     // Use SMCLK

// Motor/State machine constants
#define WHEEL_COUNT_TIME     (20)       // General wheel count time
#define RIGHT_COUNT_TIME     (8)        // Right wheel count
#define LEFT_COUNT_TIME      (8)        // Left wheel count
#define TRAVEL_DISTANCE      (80)       // Straight line travel distance

#define RIGHT_COUNT_TIME_CIRCLE     (12)  // Right wheel time for circle
#define LEFT_COUNT_TIME_CIRCLE      (2)   // Left wheel time for circle
#define TRAVEL_DISTANCE_CIRCLE      (30)  // Distance for circle
#define WAITING2START        (50)       // Waiting ticks before start

#define F_RIGHT_COUNT_TIME_CIRCLE     (12)  // Forward circle right wheel
#define F_LEFT_COUNT_TIME_CIRCLE      (2)   // Forward circle left wheel
#define F_TRAVEL_DISTANCE_CIRCLE      (20)  // Forward circle distance
#define RIGHT_COUNT_TIME_REV_CIRCLE   (2)   // Reverse circle right wheel
#define LEFT_COUNT_TIME_REV_CIRCLE    (12)  // Reverse circle left wheel
#define TRAVEL_DISTANCE_FIG8           (20)  // Travel distance for figure 8

#define T_SIDE_TRAVEL_DISTANCE (9)           // Triangle side travel distance
#define T_WHEEL_COUNT_TIME     (15)          // Triangle wheel count time
#define T_RIGHT_COUNT_TIME     (8)           // Triangle right wheel
#define T_LEFT_COUNT_TIME      (8)           // Triangle left wheel
#define T_TURN_TRAVEL_DISTANCE (8)           // Triangle turn travel distance
#define T_TURN_RIGHT_COUNT_TIME (3)          // Triangle turn right wheel
#define T_TURN_LEFT_COUNT_TIME (17)          // Triangle turn left wheel
#define T_TURN_WHEEL_COUNT_TIME (20)        // Triangle turn wheel total

// PWM aliases
#define PWM_PERIOD (TB3CCR0)                 // PWM period register
#define LEFT_FORWARD_SPEED (TB3CCR1)         // Left forward PWM duty
#define RIGHT_FORWARD_SPEED (TB3CCR2)        // Right forward PWM duty
#define LEFT_REVERSE_SPEED (TB3CCR3)         // Left reverse PWM duty
#define RIGHT_REVERSE_SPEED (TB3CCR4)        // Right reverse PWM duty
#define LCD_BACKLITE_DIMING (TB3CCR5)        // LCD backlight PWM

// Motor speeds
#define WHEEL_OFF (0)             // Wheel stopped
#define SLOW (12000)              // Slow speed PWM
#define FAST (13000)              // Fast speed PWM
#define Forward_R_BLD (9000)      // Forward right BLD speed
#define Forward_L_BLD (10500)     // Forward left BLD speed
#define Forward_R_ARC (12000)     // Forward right arc speed
#define Forward_L_ARC (21500)     // Forward left arc speed
#define Forward_R (12000)         // Forward right speed
#define Forward_L (15000)         // Forward left speed
#define Reverse_R (10000)         // Reverse right speed
#define Reverse_L (13250)         // Reverse left speed

// PWM Backlight percentages
#define PERCENT_100 (50000)       // Full brightness
#define PERCENT_80 (45000)        // 80% brightness
#define PERCENT_0   (0)           // Backlight off
#define WHEEL_PERIOD (50005)      // Total wheel PWM period

// Timing constants
#define WAITING5START (10)        // Waiting ticks before start
#define Two_Circles_Time (120)    // Time for two circles

// Ring buffer
#define BEGINNING (0)             // Starting index
#define SMALL_RING_SIZE (11)      // Ring buffer size

// DAC limits
#define DAC_Begin (2750)          // 2V initial DAC output
#define DAC_Limit (850)           // DAC lower limit
#define DAC_Adjust (875)          // DAC adjustment step

// State machine events and states
#define NONE                 ('N')   // No event
#define STRAIGHT             ('L')   // Straight line event
#define CIRCLE               ('C')   // Circle event
#define FIG8                 ('F')   // Figure 8 event
#define TRIANGLE             ('T')   // Triangle event
#define WAIT                 ('W')   // Wait state
#define START                ('S')   // Start state
#define RUN                  ('R')   // Running state
#define END                  ('E')   // End state
