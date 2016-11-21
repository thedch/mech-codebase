/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
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
#include "TapeTrackingSubHSM.h"
#include "MyHelperFunctions.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    ScanningForBeacon,
    TapeTracking,
    ReverseLineTracking,
    DrivingToFindTrackWire,
    CheckForBeaconTape,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"ScanningForBeacon",
	"TapeTracking",
	"ReverseLineTracking",
	"DrivingToFindTrackWire",
	"CheckForBeaconTape",
};



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
static int pastTapeFlag;
static int initTapeSensorStartupFlag;
static int bumpedVar;
static int bumpedTurnVar;
static int lastTapeOnParam;
static int checkForBeaconTapeTurnVar;

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
uint8_t InitTapeTrackingSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunTapeTrackingSubHSM(INIT_EVENT);
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
ES_Event RunTapeTrackingSubHSM(ES_Event ThisEvent) {
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
                nextState = ScanningForBeacon;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ScanningForBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    ES_Timer_InitTimer(4, 1000); // rotate to avoid beacon
                    leftTankTurn(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    ES_Timer_InitTimer(4, 1000); // rotate to avoid beacon
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                    // You've been bumped, back up
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(BUMPED_TIMER, 400);
                    ThisEvent.EventType = ES_NO_EVENT;
                    bumpedTurnVar = 1; // 1 = LEFT
                    bumpedVar = 0;
                    break;
                case FRONT_RIGHT_BUMPER_HIT:
                    // You've been bumped, back up
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(BUMPED_TIMER, 500);
                    ThisEvent.EventType = ES_NO_EVENT;
                    bumpedTurnVar = 2; // 2 = RIGHT
                    bumpedVar = 0;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 4) {
                        // You're turned away from the beacon, drive to find tape
                        driveForward(MAX_MOTOR_SPEED);
                    } else if (ThisEvent.EventParam == BUMPED_TIMER) {
                        // You're finished backing up from a bumped event, turn the 
                        // appropriate direction 
                        if (bumpedTurnVar == 1) {
                            leftTankTurn(MEDIUM_MOTOR_SPEED);
                        } else if (bumpedTurnVar == 2) {
                            rightTankTurn(MEDIUM_MOTOR_SPEED);
                        }
                        //                        ES_Timer_InitTimer(BUMPED_TIMER, 400);
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    if (ThisEvent.EventParam & 0x02) {
                        printf("\r\nJust saw center tape, leaving beaconScanning \r\n");
                        motorsOff();
                        nextState = TapeTracking;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case TapeTracking:
            // This state handles the actual tracking of the tape and bump events while tracking    
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    rightMotor(REVERSE, MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ALL_TAPE_WHITE:
                    motorsOff();
                    ES_Timer_InitTimer(7, 250);
                    //                    ninetyPercentLeftTurn(SLOW_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    if (ThisEvent.EventParam & 0x02) {
                        rightMotor(REVERSE, MEDIUM_MOTOR_SPEED);
                    } else { // treat this like center on white
                        motorsOff();
                        ES_Timer_InitTimer(7, 350);
                        //                        ninetyPercentLeftTurn(MEDIUM_MOTOR_SPEED);
                        break;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 7) {
                        ninetyPercentLeftTurn(MEDIUM_MOTOR_SPEED);
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    break;
                case ES_NO_EVENT:
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                case BACK_TRACK_WIRE_DETECTED:
                    // TODO: Should we eat this?
                    // ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                    printf("Just got bumped (LEFT) \r\n");
                    nextState = ReverseLineTracking;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_RIGHT_BUMPER_HIT:
                    printf("Just got bumped (RIGHT) \r\n");
                    nextState = ReverseLineTracking;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case ReverseLineTracking:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // TODO: Add actual reverse line tracking
                    rightMotor(REVERSE, SLOW_MOTOR_SPEED);
                    ES_Timer_InitTimer(2, 1150); // rotate to turn past the ball tower
                    printf("Entering reverseLineTracking, backing up \r\n");
                    break;
                case ES_NO_EVENT:
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    //ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    printf("Timer expired in reverseLineTracking \r\n");
                    motorsOff();
                    nextState = DrivingToFindTrackWire;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                case BACK_TRACK_WIRE_DETECTED:
                    // ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_LOW:
                case FRONT_RIGHT_BUMPER_LOW:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    printf("LEAVING REVERSE LINE TRACKING \r\n");
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case DrivingToFindTrackWire:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveForward(SLOW_MOTOR_SPEED);
                    // this is a timer to allow the robot to clear the tape
                    ES_Timer_InitTimer(2, 150);
                case TAPE_ON:
                    if (ThisEvent.EventParam & 0x02) {
                        if (pastTapeFlag) {
                            pastTapeFlag = 0;
                            nextState = CheckForBeaconTape;
                            // TODO: Make sure you didn't run into a beacon (beacon detector range finding would be cool here)
                            // go to new state to avoid beacon
                            makeTransition = TRUE;
                        }
                    } else // treat this like center on white
                    {
                        ;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BACK_TRACK_WIRE_DETECTED:
                    // pass this up to the top level
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 2) {
                        pastTapeFlag = 1; // set the flag to allow the robot to 
                        // re-find the tape    
                    } else if (ThisEvent.EventParam == BUMPED_TIMER) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                    }
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    fiftyPercentReverseLeftTurn(MEDIUM_MOTOR_SPEED);
                    //                    bumpedVar = 0;
                    ES_Timer_InitTimer(BUMPED_TIMER, 500);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case CheckForBeaconTape:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    leftTankTurn(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(4, 250);
                    ThisEvent.EventType = ES_NO_EVENT;
                    checkForBeaconTapeTurnVar = 1;
                    break;
                case BEACON_LOST:
                case BEACON_DETECTED:
                    // You're at a beacon, get out
                    // reset timers
                    motorsOff(); // for now, TODO: change this
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 4 && checkForBeaconTapeTurnVar == 1) {
                        // finished turning left, now turn right
                        rightTankTurn(MEDIUM_MOTOR_SPEED);
                        ES_Timer_InitTimer(4, 500);
                        checkForBeaconTapeTurnVar = 2;
                    } else if (ThisEvent.EventParam == 4 && checkForBeaconTapeTurnVar == 2) {
                        // finished turning right, go back to tape tracking
                        nextState = TapeTracking;
                        makeTransition = TRUE;
                        checkForBeaconTapeTurnVar = 0; // reset the beacon var
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    //                    if (ThisEvent.EventParam & 0x02) {
                    //                        nextState = TapeTracking;
                    //                        makeTransition = TRUE;
                    //                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State



    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTapeTrackingSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTapeTrackingSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

