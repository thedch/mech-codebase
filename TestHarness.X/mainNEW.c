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

int main(void) {

    BOARD_Init();

    LED_Init();
    LED_AddBanks(LED_BANK1); // init all the LEDs
    LED_AddBanks(LED_BANK2);
    LED_AddBanks(LED_BANK3);

    LED_SetBank(LED_BANK1, 0x00);
    LED_SetBank(LED_BANK2, 0x00);
    LED_SetBank(LED_BANK3, 0x00);

    PORTZ03_TRIS = 1; // set Z3 to be input

    printf("Hello World! I'm Daniel...\r\n");

    while (1) {
//        if (PORTZ03_BIT == 1) {
//            printf("Track Wire High: %d\r\n", PORTZ03_BIT);
//        } else if (PORTZ03_BIT == 0) {
//            printf("Track Wire Low: %d\r\n", PORTZ03_BIT);
//        }
        myDelay(MED_DELAY);
//        LED_InvertBank(LED_BANK1, 0xF);
    }
    return 0;
}
