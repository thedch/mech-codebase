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

void checkTapeSensors(void);

int main(void) {

    BOARD_Init();

    PWM_Init();
    RC_Init();
    LED_Init();
    LED_AddBanks(LED_BANK1); // init all the LEDs
    LED_AddBanks(LED_BANK2);
    LED_AddBanks(LED_BANK3);

    LED_SetBank(LED_BANK1, 0x00);
    LED_SetBank(LED_BANK2, 0x00);
    LED_SetBank(LED_BANK3, 0x00);

    AD_Init();
    AD_AddPins(AD_PORTV4 | AD_PORTV8 | AD_PORTV6);

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
    printf("Hello World\r\n");
    //    printf("Hello, Daniel!\r\n");
    //    printf("Hello, Daniel!\r\n");
    //    printf("Hello, Daniel!\r\n");

    //    printf("Current duty cycle for Left Motor is %d\r\n", PWM_GetDutyCycle(LEFT_MOTOR_PWM_PIN));
    //    printf("Current duty cycle for Right Motor is %d\r\n", PWM_GetDutyCycle(RIGHT_MOTOR_PWM_PIN));

    int tempVar = 1;
    //    tapeSensorInit();
    //    PORTZ11_TRIS = 0; // output
    //    PORTZ04_TRIS = 1; // input

    //    PORTZ11_TRIS = 1; // set output power to be high    
    //    IO_PortsSetPortOutputs(PORTX, PIN10);
    //    IO_PortsSetPortOutputs(PORTX, PIN5);
    //    IO_PortsSetPortOutputs(PORTX, PIN12);
    //    IO_PortsSetPortBits(PORTX, PIN10);
    //    IO_PortsSetPortBits(PORTX, PIN5);
    //    IO_PortsSetPortBits(PORTX, PIN12);
    //
    //    IO_PortsSetPortInputs(PORTX, PIN9);
    //    IO_PortsSetPortInputs(PORTX, PIN4);
    //    IO_PortsSetPortInputs(PORTX, PIN11);

    IO_PortsSetPortOutputs(PORTY, PIN8);
    IO_PortsSetPortBits(PORTY, PIN8);


    while (1) {
//        checkTapeSensors();
        leftTankTurn(750);
        //        if (IO_PortsReadPort(PORTX) & PIN10) {
        //            printf("%d\r\n", (IO_PortsReadPort(PORTX) & PIN9));
        //        if (PORTX09_BIT) {
        //            printf("LEFT BUMP \r\n");
        //        }
        //        if (IO_PortsReadPort(PORTX) & PIN4) {
        //            printf("RIGHT BUMP \r\n");
        //        }
        //        if (IO_PortsReadPort(PORTX) & PIN11) {
        //            printf("BACK BUMP \r\n");
        //        }
        //        }
        //        switch (tempVar) {
        //            case 1:
        //                RC_SetPulseTime(RC_PORTX03, 1000);
        //                tempVar = 2;
        //                myDelay(LONG_DELAY);
        //                myDelay(LONG_DELAY);
        //                myDelay(LONG_DELAY);
        //                break;
        //            case 2:
        //                RC_SetPulseTime(RC_PORTX03, 2000);
        //                tempVar = 1;
        //                myDelay(MED_DELAY);
        //                myDelay(MED_DELAY);
        //                break;
        //        }
        myDelay(LONG_DELAY);
    }
    return 0;
}

void checkTapeSensors(void) {
    printf("Tape Readings: %d, %d, %d \r\n", AD_ReadADPin(AD_PORTV4),
            AD_ReadADPin(AD_PORTV6), AD_ReadADPin(AD_PORTV8));
}