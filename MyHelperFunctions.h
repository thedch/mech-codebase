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
static int GetOutFlag = 0;

// Delay 
#define SHORT_DELAY 10000
#define MED_DELAY 100000
#define LONG_DELAY 1000000

// Motors
#define MAX_MOTOR_SPEED 900
#define MEDIUM_MOTOR_SPEED 700
#define SLOW_MOTOR_SPEED 450

#define FORWARD 0
#define REVERSE 1

#define LEFT_MOTOR_PWM_PIN PWM_PORTY12
#define RIGHT_MOTOR_PWM_PIN PWM_PORTY10

// Tape 
#define BLACK_TAPE_THRESHOLD 450
#define WHITE_THRESHOLD 300

#define LEFT_TAPE_SENSOR_DATA_PIN AD_PORTV4
#define CENTER_TAPE_SENSOR_DATA_PIN AD_PORTV6
#define RIGHT_TAPE_SENSOR_DATA_PIN AD_PORTV8

#define LEFT_TAPE_SENSOR 0x01
#define CENTER_TAPE_SENSOR 0x02
#define RIGHT_TAPE_SENSOR 0x04

// Beacon Detector
#define BEACON_DETECTOR_PIN AD_PORTV3
#define BEACON_DETECTOR_THRESHOLD 550
#define BEACON_DEBOUNCE_THRESHOLD 200

// Bumpers
#define FRONT_RIGHT_OUTER_LIMIT_SWITCH_PIN PORTX09_BIT 
#define FRONT_RIGHT_INNER_LIMIT_SWITCH_PIN PORTX10_BIT

#define FRONT_LEFT_INNER_LIMIT_SWITCH_PIN PORTZ05_BIT
#define FRONT_LEFT_OUTER_LIMIT_SWITCH_PIN PORTZ06_BIT

// Track Wire
#define BACK_TRACK_WIRE_SENSOR_PIN AD_PORTV7
#define FRONT_TRACK_WIRE_SENSOR_PIN AD_PORTV5
#define BACK_TRACK_WIRE_DATA_THRESHOLD 450
#define FRONT_TRACK_WIRE_DATA_THRESHOLD 450
#define BACK_TRACK_WIRE_DEBOUNCE_THRESHOLD 10
#define FRONT_TRACK_WIRE_DEBOUNCE_THRESHOLD 10

// Ball Drop Servo
#define BALL_DROP_SERVO_PIN RC_PORTZ08
#define SERVO_POSITION_ONE 1500
#define SERVO_POSITION_TWO 2000

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

/**
 * @Function tapeSensorInit
 * @param None
 * @return None
 * @brief Sets the correct ports to read data from the tape sensors.
 * Use the given #defines.
 * @author Daniel Hunter, 9 Nov 2016 */
void tapeSensorInit();

/**
 * @Function leftTankTurn
 * @param None
 * @return None
 * @brief Sets left wheel reverse, right wheel forward
 * @author Daniel Hunter, 10 Nov 2016 */
void leftTankTurn(int dutyCycle);

/**
 * @Function rightTankTurn
 * @param None
 * @return None
 * @brief Sets right wheel reverse, left wheel forward
 * @author Daniel Hunter, 10 Nov 2016 */
void rightTankTurn(int dutyCycle);

/**
 * @Function fiftyPercentReverseRightTurn
 * @param dutyCycle - the desired PWM duty cycle of the full speed wheel
 * @return None
 * @brief Helper function used turn the robot gradually in the reverse direction
 * @author Daniel Hunter, 11 Nov 2016 */
void fiftyPercentReverseRightTurn(int dutyCycle);

/**
 * @Function fiftyPercentReverseLeftTurn
 * @param dutyCycle - the desired PWM duty cycle of the full speed wheel
 * @return None
 * @brief Helper function used turn the robot gradually in the reverse direction
 * @author Daniel Hunter, 11 Nov 2016 */
void fiftyPercentReverseLeftTurn(int dutyCycle);

// TODO: Write PWM_SetDutyCycle wrapper that incorporates battery voltage

/**
 * @Function leftMotor
 * @param direction - the direction of the left motor
 * dutyCycle - the desired PWM duty cycle of the left wheel
 * @return None
 * @brief Turns the left motor as desired, and SHUTS THE RIGHT MOTOR OFF
 * @author Daniel Hunter, 11 Nov 2016 */
void leftMotor(int direction, int dutyCycle);

/**
 * @Function rightMotor
 * @param direction - the direction of the right motor
 * dutyCycle - the desired PWM duty cycle of the right wheel
 * @return None
 * @brief Turns the right motor as desired, and SHUTS THE LEFT MOTOR OFF
 * @author Daniel Hunter, 11 Nov 2016 */
void rightMotor(int direction, int dutyCycle);

/**
 * @Function leftTankTurn
 * @param None
 * @return None
 * @brief Sets left wheel reverse, right wheel forward, pivots around the back 
 * track sensor
 * @author Kenny He, 13 Nov 2016 */
void leftTrackTurn(int dutyCycle);

/**
 * @Function rightTankTurn
 * @param None
 * @return None
 * @brief Sets right wheel reverse, left wheel forward, pivots around the back 
 * track sensor
 * @author Kenny He, 13 Nov 2016 */
void rightTrackTurn(int dutyCycle);

/**
 * @Function toggleServo
 * @param None
 * @return None
 * @brief Toggles the servo gate between positions. Calling this function twice 
 * with ~500 ms between calls should release a ball
 * @author Daniel Hunter, 15 Nov 2016 */
void toggleServo();

/**
 * @Function ninetyPercentReverseLeftTurn
 * @param None
 * @return None
 * @brief Sets left wheel to be 90% power, right wheel to be 100% power
 * @author Daniel Hunter, 18 Nov 2016 */
void ninetyPercentLeftTurn(int dutyCycle);

/**
 * @Function CustomPWM_SetDutyCycle
 * @param dutyCycle - the duty cycle to be set to the appropriate motor
 * @return None
 * @brief Sets left wheel to be 90% power, right wheel to be 100% power
 * @author Daniel Hunter, 19 Nov 2016 */
char CustomPWM_SetDutyCycle(unsigned char Channel, unsigned int Duty);