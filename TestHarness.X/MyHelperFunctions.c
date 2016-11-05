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

void myDelay(int delayLength) {
    while (delayLength > 0) {
        delayLength--;
    }
}
