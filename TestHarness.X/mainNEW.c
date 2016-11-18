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
void printTankSensors(void);

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
    AD_AddPins(BACK_TRACK_WIRE_SENSOR_PIN |
            FRONT_TRACK_WIRE_SENSOR_PIN |
            BEACON_DETECTOR_PIN |
            CENTER_TAPE_SENSOR_DATA_PIN);

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

    // Tape Sensor Power
    IO_PortsSetPortOutputs(PORTY, PIN8);
    IO_PortsSetPortBits(PORTY, PIN8);

    RC_AddPins(RC_PORTZ08);
    printf("Hello World! This is a test harness for The Beast (tm)\r\n");

    //    tapeSensorInit();
    //    PORTZ11_TRIS = 0; // output
    //    PORTZ04_TRIS = 1; // input

    //    PORTZ11_TRIS = 1; // set output power to be high

    //    IO_PortsSetPortOutputs(PORTY, PIN8);
    //    IO_PortsSetPortBits(PORTY, PIN8);

    //    PORTX03_TRIS = 1; // input

    //    driveBackward(750);

    //    myDelay(LONG_DELAY);
    //    myDelay(LONG_DELAY);
    //
    //    driveForward(750);
    //
    //    myDelay(LONG_DELAY);
    //
    //    motorsOff();

    //    PORTZ09_TRIS = 1; // Beacon detector input signal
    //    PORTY08_TRIS = 0; // Beacon detector input signal
    //    PORTY08_LAT = 1; // Beacon detector input signal

    int currentFrontTrackWire = 0;
    static int previousFrontTrackWire = 0;
    int tempVar = 0;

    while (1) {
        driveForward(SLOW_MOTOR_SPEED);
    }
    return 0;
}

void checkTapeSensors(void) {
    printf("Tape Readings: %d, %d, %d \r\n", AD_ReadADPin(AD_PORTV4),
            AD_ReadADPin(AD_PORTV6), AD_ReadADPin(AD_PORTV8));
}

void printTankSensors(void) {
    printf("Front: %d, Back: %d, \r\n",
            AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN),
            AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN));
}