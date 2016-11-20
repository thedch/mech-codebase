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
#include "MyHelperFunctions.h"
#include "RC_Servo.h"

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

void motorsOff() {
    PWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, 0);
    PWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, 0);
}

void driveForward(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_LAT = 0;
    PORTY09_LAT = 0;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void driveBackward(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_LAT = 1;
    PORTY09_LAT = 1;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void fiftyPercentLeftTurn(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 0;
    PORTY09_BIT = 0;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, (dutyCycle * 0.5));
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void fiftyPercentRightTurn(int dutyCycle) {
    // this function currently has no error checking, and assumes PWM pins have
    // been correctly set up. I will probably fix this.
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 0;
    PORTY09_BIT = 0;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle * 0.5);
}

void tapeSensorInit() {
    // Set power port to be output (Y4)
    PORTY08_TRIS = 0;
    // Set data ports to be input
    PORTZ03_TRIS = 1;
    PORTZ05_TRIS = 1;
    PORTZ07_TRIS = 1;
    // Set power port to high
    PORTY08_LAT = 1;
}

void leftTankTurn(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 0;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void rightTankTurn(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 0;
    PORTY09_BIT = 1;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void fiftyPercentReverseLeftTurn(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 1;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, (dutyCycle * 0.5));
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void fiftyPercentReverseRightTurn(int dutyCycle) {

    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 1;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle * 0.5);
}

void leftMotor(int direction, int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = direction;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, 0);
}

void rightMotor(int direction, int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY09_BIT = direction;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, 0);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

void leftTrackTurn(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 1;
    PORTY09_BIT = 0;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle * 0.9);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle * 1.1);
}

void rightTrackTurn(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 0;
    PORTY09_BIT = 1;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, dutyCycle * 0.9);
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle * 1.1);
}

void toggleServo() {
    if (RC_GetPulseTime(BALL_DROP_SERVO_PIN) == SERVO_POSITION_ONE) {
        // if servo is in position one, set to position two
        RC_SetPulseTime(BALL_DROP_SERVO_PIN, SERVO_POSITION_TWO);
    } else {
        // else set to position one
        RC_SetPulseTime(BALL_DROP_SERVO_PIN, SERVO_POSITION_ONE);
    }
}

void ninetyPercentLeftTurn(int dutyCycle) {
    PORTY11_TRIS = 0;
    PORTY09_TRIS = 0;

    PORTY11_BIT = 0;
    PORTY09_BIT = 0;

    CustomPWM_SetDutyCycle(LEFT_MOTOR_PWM_PIN, (dutyCycle * 0.9));
    CustomPWM_SetDutyCycle(RIGHT_MOTOR_PWM_PIN, dutyCycle);
}

char CustomPWM_SetDutyCycle(unsigned char Channel, unsigned int Duty) {

    // Lookup Table (accounting for diode loss):
    // MAX_MOTOR_SPEED = 1000 = 9.3 V  
    // MED_MOTOR_SPEED = 750 = 6.82V
    // SLOW_MOTOR_SPEED = 500 = 4.35V

    unsigned int newDuty = 0;
    unsigned int batVoltage = 0;
    double newBatVoltage = 0;
    batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage
    newBatVoltage = (double) batVoltage;
    if (newBatVoltage != 0) {
        newBatVoltage = newBatVoltage / 1023 * 33; // = current actual battery voltage
        //        printf("Current Actual Battery Voltage: %fV \r\n", newBatVoltage);
        newBatVoltage = newBatVoltage - 0.6; // account for diode loss
        newDuty = Duty / newBatVoltage * 9.9; // Modify the duty cycle as needed to account for a lower bat voltage   
    }
    if (newDuty > 1000) {
        newDuty = 1000; // if the duty cycle has exceeded the limits, trim it
    }
    //    printf("You just set the PWM to be %d \r\n", newDuty);
    return (PWM_SetDutyCycle(Channel, newDuty));
//    return 0;
}