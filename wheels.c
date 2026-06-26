/*
 * description: includes motor configurations in functions for use globally
 * wheels.c
 * Sai Nelluri
 * September 2025
 */

#include "msp430.h"
#include "macros.h"
#include "ports.h"
#include "functions.h"
#include "LCD.h"
#include "wheels.h"


// Stop both wheels (no forward or reverse motion)
void stop_all (){
    LEFT_FORWARD_SPEED = WHEEL_OFF;     // Disable left wheel forward
    RIGHT_FORWARD_SPEED = WHEEL_OFF;    // Disable right wheel forward
    LEFT_REVERSE_SPEED = WHEEL_OFF;     // Disable left wheel reverse
    RIGHT_REVERSE_SPEED = WHEEL_OFF;    // Disable right wheel reverse
}

// Move robot forward using normal speeds
void Forward_Move (){
    Left_Forward();
    Right_Forward();
}

// Forward movement for BLD mode (special duty cycles)
void Forward_Move_BLD (){
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = Forward_R_BLD;   // Right wheel BLD forward duty
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = Forward_L_BLD;    // Left wheel BLD forward duty
}

// Forward movement for ARC mode (special tuned speeds)
void Forward_Move_ARC(){
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = Forward_R_ARC;   // ARC forward speed right
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = Forward_L_ARC;    // ARC forward speed left
}

// Reverse both wheels
void Reverse_Move(){
    Right_Reverse();
    Left_Reverse();
}

// Right wheel forward (normal speed)
void Right_Forward (){
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = Forward_R;
}

// Right wheel forward for BLD mode
void Right_Forward_BLD (){
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = Forward_R_BLD;
}

// Left wheel forward for BLD mode
void Left_Forward_BLD (){
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = Forward_L_BLD;
}

// Right wheel reverse (normal speed)
void Right_Reverse (){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = Reverse_R;
}

// Left wheel forward (normal speed)
void Left_Forward (){
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = Forward_L;
}

// Left wheel reverse (normal speed)
void Left_Reverse (){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = Reverse_L;
}

// Turn off both directions of left wheel
void Left_Off(){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
}

// Turn off both directions of right wheel
void Right_Off(){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

// Turn off forward movement for both wheels
void Forward_Off (){
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

// Turn off reverse movement for both wheels
void Reverse_Off (){
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

// Rotate clockwise using left reverse + right forward
void clockwiser_left (){
    LEFT_REVERSE_SPEED = Reverse_L;     // Left in reverse
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = Forward_R;    // Right forward for clockwise turn
}

// Rotate clockwise using right reverse + left forward
void clockwiser_right(){
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = Forward_L;     // Left forward
    RIGHT_REVERSE_SPEED = Reverse_R;    // Right reverse for clockwise turn
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

// Safety check: ensures no wheel receives both forward and reverse at once
void checking (){
    // Left wheel both directions active (illegal)
    if (LEFT_REVERSE_SPEED != WHEEL_OFF && LEFT_FORWARD_SPEED != WHEEL_OFF){
        stop_all();
    }
    // Right wheel both directions active (illegal)
    else if (RIGHT_REVERSE_SPEED != WHEEL_OFF && RIGHT_FORWARD_SPEED != WHEEL_OFF){
        stop_all();
    }
    // Left wheel receives contradictory FAST settings
    else if (LEFT_REVERSE_SPEED == FAST && LEFT_FORWARD_SPEED == FAST){
        stop_all();
    }
    // Right wheel receives contradictory FAST settings
    else if (RIGHT_REVERSE_SPEED == FAST && RIGHT_FORWARD_SPEED == FAST){
        stop_all();
    }
}
