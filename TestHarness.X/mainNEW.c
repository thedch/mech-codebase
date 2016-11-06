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

    LED_SetBank(LED_BANK1, 0b0110);
    LED_SetBank(LED_BANK2, 0x00);
    LED_SetBank(LED_BANK3, 0x00);

    //    PORTZ03_TRIS = 1; // set Z3 to be input

    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1; // how is this possibly correct
    PORTY09_BIT = 0;

    PWM_Init();
    PWM_AddPins(LEFT_MOTOR_PWM_PIN | RIGHT_MOTOR_PWM_PIN);

    //    PWM_AddPins(RIGHT_MOTOR_PWM_PIN);
    PWM_SetFrequency(PWM_DEFAULT_FREQUENCY);

    printf("Current PWM pins %d\r\n", PWM_ListPins());
    printf("Current PWM freq %d\r\n", PWM_GetFrequency());

    //    driveBackward(1000);
    PORTV03_TRIS = 1; // Set V3 (light sensor pin) to be input

    printf("Current duty cycle for Left Motor is %d\r\n", PWM_GetDutyCycle(LEFT_MOTOR_PWM_PIN));
    printf("Current duty cycle for Right Motor is %d\r\n", PWM_GetDutyCycle(RIGHT_MOTOR_PWM_PIN));

    while (1) {
        if (PORTV03_BIT == 1) { // light sensor reads HIGH
            PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, 1000);
            PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, 500);
        } else {
            PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, 500);
            PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, 1000);
        }
        myDelay(SHORT_DELAY);
        LED_InvertBank(LED_BANK1, 0b1010);
    }
    return 0;
}
