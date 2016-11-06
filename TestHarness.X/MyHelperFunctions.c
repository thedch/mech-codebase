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

void driveForward(int dutyCycle) {
    // this function currently has no error checking, as assume PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 0;

    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}
