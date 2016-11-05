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
#include <IO_Ports.h>
#include <LED.h>
#include <pwm.h>
#include "MyHelperFunctions.h"

// Track Wire Sensor Port: Z3
// #define 

int main(void) {

    BOARD_Init();

    LED_Init();
    LED_AddBanks(LED_BANK1); // init all the LEDs
    LED_AddBanks(LED_BANK2);
    LED_AddBanks(LED_BANK3);

    LED_SetBank(LED_BANK1, 0xFF);
    LED_SetBank(LED_BANK2, 0xFF);
    LED_SetBank(LED_BANK3, 0xFF);

    PORTZ03_TRIS = 1; // set Z3 to be input

    printf("Hello World! I'm Daniel...\r\n");

    while (1) {
//        if (PORTZ03_BIT == 1) {
//            printf("Track Wire High\r\n");
//        }
        myDelay(MED_DELAY);
        LED_SetBank(LED_BANK1, 0b0001);
        myDelay(MED_DELAY);
        LED_SetBank(LED_BANK1, 0b0010);
        myDelay(MED_DELAY);
        LED_SetBank(LED_BANK1, 0b0100);
        myDelay(MED_DELAY);
        LED_SetBank(LED_BANK1, 0b1000);
    }
    return 0;
}
