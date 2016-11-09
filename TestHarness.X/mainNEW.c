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
#include "RC_Servo.h"

// Track Wire Sensor Port: Z3

int main(void) {

    BOARD_Init();

    PWM_Init();
    RC_Init();
    LED_Init();
    LED_AddBanks(LED_BANK1); // init all the LEDs
    LED_AddBanks(LED_BANK2);
    LED_AddBanks(LED_BANK3);

    LED_SetBank(LED_BANK1, 0b1010);
    LED_SetBank(LED_BANK2, 0x00);
    LED_SetBank(LED_BANK3, 0x00);

    //    PORTZ03_TRIS = 1; // set Z3 to be input

    //    PORTY11_TRIS = 0;
    //    PORTY09_TRIS = 0;
    //
    //    PORTY11_BIT = 1; // how is this possibly correct
    //    PORTY09_BIT = 0;


    PWM_AddPins(LEFT_MOTOR_PWM_PIN | RIGHT_MOTOR_PWM_PIN);
    PWM_SetFrequency(PWM_DEFAULT_FREQUENCY);

    //    PWM_AddPins(RIGHT_MOTOR_PWM_PIN);


    //    printf("Current PWM pins %d\r\n", PWM_ListPins());
    //    printf("Current PWM freq %d\r\n", PWM_GetFrequency());

    //    driveBackward(1000);
    //    PORTV03_TRIS = 1; // Set V3 (light sensor pin) to be input
    //    PORTW04_TRIS = 0; // Set W4 (light sensor LED pwr pin) to be output

    //    PORTW04_LAT = 1; // Set the light sensor power pin to be high

    RC_AddPins(RC_PORTX03);
    printf("Hello, Daniel!\r\n");
    //    printf("Hello, Daniel!\r\n");
    //    printf("Hello, Daniel!\r\n");
    //    printf("Hello, Daniel!\r\n");

    //    printf("Current duty cycle for Left Motor is %d\r\n", PWM_GetDutyCycle(LEFT_MOTOR_PWM_PIN));
    //    printf("Current duty cycle for Right Motor is %d\r\n", PWM_GetDutyCycle(RIGHT_MOTOR_PWM_PIN));


    int tempVar = 1;

    while (1) {
        switch (tempVar) {
            case 1:
                //                driveForward(800);
                RC_SetPulseTime(RC_PORTX03, 1000);
                tempVar = 2;
                break;
            case 2:
                //                leftTankTurn(800);
                RC_SetPulseTime(RC_PORTX03, 1500);
                tempVar = 1;
                break;
        }
        myDelay(LONG_DELAY);
        LED_InvertBank(LED_BANK1, 0b1010);

    }
    return 0;
}
