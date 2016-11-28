/*
 * File: TrackWireSubHSM.c
 * Author: Daniel Hunter
 *
 * Sub HSM used to follow the track wire, load ammo, and navigate to the first beacon
 */

//At 11/15/16 2:46PM, William started messing with this file. Blame him if is is now brokend
/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Events.h"
#include "BOARD.h"
#include "TopLevelHSM.h"
#include "TrackWireSubHSM.h"
#include "MyHelperFunctions.h"
#include "RC_Servo.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    RotateToFindTrackWire,
    FoundTrackWire,
    LoadingAmmo,
    AntiJamPhaseOne,
    AntiJamPhaseTwo,
    BeaconScanning,
    BeaconFound,
    TargetFound,
    GetCloserToBeacon,
    StartCentering,
    RepositionOffTape,
    DriveToGetWithinRangeOfBeacon,
    Bumped_Forward,
    Bumped_Turning,

} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"RotateToFindTrackWire",
	"FoundTrackWire",
	"LoadingAmmo",
	"AntiJamPhaseOne",
	"AntiJamPhaseTwo",
	"BeaconScanning",
	"BeaconFound",
	"TargetFound",
	"GetCloserToBeacon",
	"StartCentering",
	"RepositionOffTape",
	"DriveToGetWithinRangeOfBeacon",
	"Bumped_Forward",
	"Bumped_Turning",
};

#define BEACONTIMER_CENTERED ((5*beaconTimerDelta)/10)

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static int AntiJamCounter = 0;
static int beaconTimerStart = 0;
static int beaconTimerStop = 0;
static int beaconTimerDelta = 0;
static int LoadAmmoFlag = 0;
static int BumpedTurnFlag = 0; // if 1, you were bumped while turning LEFT. if 2, RIGHT.

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTrackWireSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunTrackWireSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunTrackWireSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                // now put the machine into the actual initial state
                nextState = RotateToFindTrackWire;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case RotateToFindTrackWire:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // motorsOff();
                    rightTrackTurn(SLOW_MOTOR_SPEED);
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                    nextState = FoundTrackWire;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                    break;
                case TAPE_ON:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ALL_TAPE_WHITE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    // TODO: Bump detection
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case FoundTrackWire:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(4, 1000);
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    LoadAmmoFlag++;
                    break;
                case ES_TIMEOUT:
                    ThisEvent.EventType = ES_NO_EVENT;
                    nextState = LoadingAmmo;
                    makeTransition = TRUE;
                    motorsOff();
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                    break;
                case TAPE_ON:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ALL_TAPE_WHITE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case LoadingAmmo:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveForward(MAX_MOTOR_SPEED);
                    if (LoadAmmoFlag < 2) {
                        ES_Timer_InitTimer(1, 500);
                    } else {
                        ES_Timer_InitTimer(1, 1000);
                    }
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        if (LoadAmmoFlag < 2) {
                            ES_Timer_InitTimer(2, 5000);
                            motorsOff();
                        } else {
                            nextState = AntiJamPhaseOne;
                            makeTransition = TRUE;
                        }
                    } else if (ThisEvent.EventParam == 2) {
                        nextState = FoundTrackWire;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    if (LoadAmmoFlag < 2) {
                        driveBackward(MEDIUM_MOTOR_SPEED);
                    } else {
                        makeTransition = TRUE;
                        nextState = Bumped_Forward;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    ThisEvent.EventType = ES_NO_EVENT; // TODO: Should we have tape detection here?
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case AntiJamPhaseOne:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveBackward(MAX_MOTOR_SPEED);
                    ES_Timer_InitTimer(1, 200);
                    break;
                case ES_TIMEOUT:
                    AntiJamCounter++;
                    motorsOff();
                    ThisEvent.EventType = ES_NO_EVENT;
                    nextState = AntiJamPhaseTwo;
                    makeTransition = TRUE;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case AntiJamPhaseTwo:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(1, 150);
                    break;
                case ES_TIMEOUT:
                    if (AntiJamCounter < 2) {
                        nextState = AntiJamPhaseOne;
                        ThisEvent.EventType = ES_NO_EVENT;
                        makeTransition = TRUE;
                    } else {
                        nextState = BeaconScanning;
                        ThisEvent.EventType = ES_NO_EVENT;
                        makeTransition = TRUE;
                    }
                    break;
                case ES_NO_EVENT:
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case BeaconScanning:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    rightTankTurn(SLOW_MOTOR_SPEED);
                    ES_Timer_InitTimer(6, 5500);
                    break;
                case BEACON_DETECTED:
                    nextState = StartCentering;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                    break;
                case ES_TIMEOUT:
                    nextState = DriveToGetWithinRangeOfBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    nextState = Bumped_Turning;
                    BumpedTurnFlag = 2;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case DriveToGetWithinRangeOfBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveForward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(6, 3000);
                    break;
                case ES_TIMEOUT:
                    nextState = BeaconScanning;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    nextState = Bumped_Forward;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case GetCloserToBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(1, 1300);
                    driveForward(MEDIUM_MOTOR_SPEED);
                    break;
                case BEACON_LOST:
                    nextState = BeaconScanning;
                    makeTransition = TRUE;
                    break;
                case ES_TIMEOUT:
                    nextState = StartCentering;
                    makeTransition = TRUE;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    nextState = Bumped_Forward;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case StartCentering:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    leftTankTurn(SLOW_MOTOR_SPEED);
                    break;
                case BEACON_LOST:
                    rightTankTurn(SLOW_MOTOR_SPEED);
                    nextState = BeaconFound;
                    makeTransition = TRUE;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                    nextState = Bumped_Turning;
                    BumpedTurnFlag = 1;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_RIGHT_BUMPER_HIT:
                    nextState = Bumped_Turning;
                    BumpedTurnFlag = 2;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case BeaconFound:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    beaconTimerStart = ES_Timer_GetTime();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_LOST:
                    beaconTimerStop = ES_Timer_GetTime();
                    beaconTimerDelta = beaconTimerStop - beaconTimerStart;
                    nextState = TargetFound;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case TargetFound:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    leftTankTurn(SLOW_MOTOR_SPEED);
                    ES_Timer_InitTimer(1, BEACONTIMER_CENTERED);
                    break;
                case ES_TIMEOUT:
                    motorsOff();
                    nextState = GetCloserToBeacon;
                    makeTransition = TRUE;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case RepositionOffTape:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveBackward(SLOW_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ALL_TAPE_WHITE:
                    driveForward(SLOW_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    if ((ThisEvent.EventParam & 0x07) == 0x07) {
                        // don't do anything, pass this event up
                    } else if ((ThisEvent.EventParam & 0x01) == 0x01) {
                        // Left sensor on, pull right wheel fwd
                        rightMotor(FORWARD, MEDIUM_MOTOR_SPEED);
                        printf("\r\n LEFT SENSOR ON, Right motor FWD \r\n");
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if ((ThisEvent.EventParam & 0x04) == 0x04) {
                        // Right sensor on, pull left wheel fwd
                        leftMotor(FORWARD, MEDIUM_MOTOR_SPEED);
                        printf("\r\n RIGHT SENSOR ON, Left motor FWD \r\n");
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Bumped_Turning:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    if (BumpedTurnFlag == 1) { // you were turning LEFT
                        rightTankTurn(MEDIUM_MOTOR_SPEED);
                    } else if (BumpedTurnFlag == 2) { // you were turning RIGHT
                        leftTankTurn(MEDIUM_MOTOR_SPEED);
                    }
                    BumpedTurnFlag = 0;
                    ES_Timer_InitTimer(1, 500);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                        ES_Timer_InitTimer(2, 1000);
                    } else if (ThisEvent.EventParam == 2) {
                        nextState = BeaconScanning;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    nextState = Bumped_Forward;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    // let this event pass up to the top level
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Bumped_Forward:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    rightMotor(REVERSE, MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(1, 500);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                        ES_Timer_InitTimer(2, 1500);
                    } else if (ThisEvent.EventParam == 2) {
                        nextState = BeaconScanning;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    nextState = Bumped_Forward;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    nextState = RepositionOffTape;
                    makeTransition = TRUE;
                    // let this event pass up to the top level
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

            /////////////////////////////////////////////////////////////////////////////////////


        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTrackWireSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTrackWireSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

