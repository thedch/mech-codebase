/*
 * File:   mainNEW.c
 * Author: dchunter
 *
 * Created on November 4, 2016, 7:36 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <stdio.h>
#include <stdlib.h>
#include <AD.h>
#include <LED.h>
#include <pwm.h>

int main(void) {
    
    BOARD_Init();
    
    printf("Hello World!");
    while (1) {
        ;
    }
    return 0;
}
