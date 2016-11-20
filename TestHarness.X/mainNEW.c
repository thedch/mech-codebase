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
    //    RC_Init();
    AD_Init();

    AD_AddPins(BACK_TRACK_WIRE_SENSOR_PIN |
            FRONT_TRACK_WIRE_SENSOR_PIN |
            BEACON_DETECTOR_PIN |
            CENTER_TAPE_SENSOR_DATA_PIN |
            LEFT_TAPE_SENSOR_DATA_PIN |
            RIGHT_TAPE_SENSOR_DATA_PIN);

    PWM_AddPins(LEFT_MOTOR_PWM_PIN | RIGHT_MOTOR_PWM_PIN);
    PWM_SetFrequency(PWM_DEFAULT_FREQUENCY);

    // Tape Sensor Power High
    IO_PortsSetPortOutputs(PORTY, PIN8);
    IO_PortsSetPortBits(PORTY, PIN8);
    //        IO_PortsClearPortBits(PORTY, PIN8);

    //    RC_AddPins(RC_PORTZ08);
    printf("Hello World! This is a test harness for The Beast (tm)\r\n");

    //    PORTZ09_TRIS = 1; // Beacon detector input signal
    //    PORTY08_TRIS = 0; // Beacon detector input signal
    //    PORTY08_LAT = 1; // Beacon detector input signal

    //    int currentFrontTrackWire = 0;
    //    static int previousFrontTrackWire = 0;
    //    int tempVar = 5;
    //    float tempVar2 = (float) tempVar;
    //    printf("%d \r\n", tempVar);
    //    printf("%f \r\n", tempVar2);

    while (1) {
        //        checkTapeSensors();
        //        myDelay(LONG_DELAY);
        driveForward(MEDIUM_MOTOR_SPEED);
        //        checkTapeSensors();
        myDelay(LONG_DELAY);
        //        driveBackward(MEDIUM_MOTOR_SPEED);
    }
    return 0;
}

void checkTapeSensors(void) {
    printf("Tape Readings - Left: %d, Center: %d, Right: %d \r\n",
            AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN),
            AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN),
            AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN));
}

void printTankSensors(void) {
    printf("Front: %d, Back: %d, \r\n",
            AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN),
            AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN));
}