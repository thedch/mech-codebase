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