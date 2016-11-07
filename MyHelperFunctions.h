/*
 * File:   AD.h
 * Author: mdunne
 *
 * Software module to enable the Analog to Digital converter of the Uno32 boards.
 * All analog pins are are Port V and Port W, with an additional analog input for
 * the battery voltage (through a 10:1 divider).
 *
 * NOTE: Analog pins automatically take over digital I/O regardless of which TRIS
 *       state it is in. There remains an error in the ADC code such that if all 12
 *       pins are enabled, one of them does not respond.
 *
 * AD_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * Make sure it is commented out for module useage.
 *
 * Created on November 22, 2011, 8:57 AM
 */


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define SHORT_DELAY 10000
#define MED_DELAY 100000
#define LONG_DELAY 1000000

#define LEFT_MOTOR_PWM_PIN PWM_PORTY12
#define RIGHT_MOTOR_PWM_PIN PWM_PORTY10
#define FRONT_LEFT_LIMIT_SWITCH_PIN 0
#define FRONT_RIGHT_LIMIT_SWITCH_PIN 0
#define BACK_LIMIT_SWITCH_PIN 0

#define BACK_TRACK_WIRE_SENSOR_PIN 0
#define FRONT_TRACK_WIRE_SENSOR_PIN 0

#define BEACON_DETECTOR_PIN 0

// Left Motor Directional Pin: Y11
// Right Motor Directional Pin: Y9
// Light Sensor 1 Pin: V3

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function myDelay
 * @param delayLength - sets the length of the delay in clock cycles
 * @return None
 * @brief  Extremely simple function to 'pause' the chip for testing purposes.
 * @author Daniel Hunter, 4 Nov 2016 */
void myDelay(int delayLength);

/**
 * @Function frontTrackWireInit
 * @param None
 * @return None
 * @brief Inits the pin for the front track wire sensor
 * @author Daniel Hunter, 4 Nov 2016 */
void frontTrackWireInit(void);

/**
 * @Function frontTrackWireStatus
 * @param None
 * @return Returns 1 if the front track wire sensor is in the presence of a 
 * wire, 0 otherwise
 * @brief Function to get the status of the front track wire sensor
 * @author Daniel Hunter, 4 Nov 2016 */
int frontTrackWireStatus(void);

/**
 * @Function motorsOff
 * @param None
 * @return None
 * @brief Helper function used to turn all drive motors off
 * @author Daniel Hunter, 6 Nov 2016 */
void motorsOff();

/**
 * @Function driveForward
 * @param dutyCycle - the desired PWM duty cycle
 * @return None
 * @brief Helper function used to drive the robot forward at various speeds
 * @author Daniel Hunter, 5 Nov 2016 */
void driveForward(int dutyCycle);

/**
 * @Function driveBackward
 * @param dutyCycle - the desired PWM duty cycle
 * @return None
 * @brief Helper function used to drive the robot backward at various speeds
 * @author Daniel Hunter, 5 Nov 2016 */
void driveBackward(int dutyCycle);

/**
 * @Function fiftyPercentLeftTurn
 * @param dutyCycle - the desired PWM duty cycle of the full speed wheel
 * @return None
 * @brief Helper function used turn the robot gradually
 * @author Daniel Hunter, 5 Nov 2016 */
void fiftyPercentLeftTurn(int dutyCycle);

/**
 * @Function fiftyPercentRightTurn
 * @param dutyCycle - the desired PWM duty cycle of the full speed wheel
 * @return None
 * @brief Helper function used turn the robot gradually
 * @author Daniel Hunter, 5 Nov 2016 */
void fiftyPercentRightTurn(int dutyCycle);

/**
 * @Function postLEDMessage
 * @param LEDstring - the desired 4 bit message to post
 * @return None
 * @brief Displays a 4 bit string using 4 LEDs mounted on the roof. Good for
 * diagnostics
 * @author Daniel Hunter, 6 Nov 2016 */
void postLEDMessage(int LEDstring);



