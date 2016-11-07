/*
 * File:   MyHelperFunctions.c
 * Author: dchunter
 *
 * Created on November 4, 2016, 9:01 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <stdio.h>
#include <stdlib.h>
#include <AD.h>
#include <IO_Ports.h>
#include <LED.h>
#include <pwm.h>
#include "MyHelperFunctions.h"

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

void myDelay(int delayLength) {
    while (delayLength > 0) {
        delayLength--;
    }
}

void frontTrackWireInit(void) {
    // This assume Z3 is being used for the front track wire.
    // If this is not the case, this needs to be changed.
    PORTZ03_TRIS = 1; // set Z3 to be input
}

int frontTrackWireStatus(void) {
    // This assume Z3 is being used for the front track wire.
    // If this is not the case, this needs to be changed.
    if (PORTZ03_BIT == 1) {
        return 0; // Not in the presence of a track wire
    } else if (PORTZ03_BIT == 0) {
        return 1; // In the presence of a track wire
    }
}

void motorsOff() {
    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, 0);
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, 0);
}

void driveForward(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1; // how is this possibly correct
    PORTY09_BIT = 0;

    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void driveBackward(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 0;
    PORTY09_BIT = 1;

    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void fiftyPercentLeftTurn(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 0;

    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, (dutyCycle * 0.5));
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void fiftyPercentRightTurn(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 0;

    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle * 0.5);
}

void postLEDMessage(int LEDstring) {
    /* I'm planning on using X3,5,7,9 for the LED connections.
     * Those ports are usually used for onboard LEDs, so replacing them will
     * work nicely. 
     */
    
    // Set all the ports to be output
    // This will be done redundantly, but I think I'll leave it here as a
    // safety measure
    PORTX03_TRIS = 0;
    PORTX05_TRIS = 0;
    PORTX07_TRIS = 0;
    PORTX09_TRIS = 0;
    
    // reset all the LEDs to clear any previous string
    PORTX03_LAT = 0;
    PORTX05_LAT = 0;
    PORTX07_LAT = 0;
    PORTX09_LAT = 0;
    
    // set the LEDs to be high based on the string
    if (LEDstring & 0b0001) {
        PORTX03_LAT = 1;
    }
    if (LEDstring & 0b0010) {
        PORTX05_LAT = 1;
    }
    if (LEDstring & 0b0100) {
        PORTX07_LAT = 1;
    }
    if (LEDstring & 0b1000) {
        PORTX09_LAT = 1;
    }
}
