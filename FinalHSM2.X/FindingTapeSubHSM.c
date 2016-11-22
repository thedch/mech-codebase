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


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopLevelHSM.h"
#include "FindingTapeSubHSM.h"
#include "MyHelperFunctions.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Rotate360,
    OneBeaconFound,
    TwoBeaconsFound,
    ThreeBeaconsFound,
    DriveToFindTape,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Rotate360",
	"OneBeaconFound",
	"TwoBeaconsFound",
	"ThreeBeaconsFound",
	"DriveToFindTape",
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

static int BeaconFlag;
static uint32_t firstBeaconTimer;
static uint32_t secondBeaconTimer;
static uint32_t thirdBeaconTimer;

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
uint8_t InitFindingTapeSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFindingTapeSubHSM(INIT_EVENT);
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
ES_Event RunFindingTapeSubHSM(ES_Event ThisEvent) {
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
                nextState = Rotate360;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Rotate360: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    BeaconFlag = 0;
                    ES_Timer_InitTimer(1, 360 * 9.7); // frustration timer, set to exactly 360 deg
                    leftTankTurn(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        // Initial 360 turn has stopped, pause for a moment
                        motorsOff();
                        ES_Timer_InitTimer(2, 500);
                    } else if (ThisEvent.EventParam == 2) {
                        if (BeaconFlag == 1) {
                            nextState = OneBeaconFound;
                        } else if (BeaconFlag == 2) {
                            nextState = TwoBeaconsFound;
                        } else if (BeaconFlag == 3) {
                            nextState = ThreeBeaconsFound;
                        }
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    BeaconFlag++;
                    if (BeaconFlag == 3) {
                        ES_Timer_InitTimer(1, 1); // set timer to be 1 ms to overwrite the older timer
                    }
                    printf("\r\n JUST SAW A BEACON ON FIRST ROTATION \r\n");
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case OneBeaconFound:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    rightTankTurn(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        nextState = DriveToFindTape;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    // TODO: Drive to beacon, then drive away
                    ES_Timer_InitTimer(1, 1700); // approx 180 degrees
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case TwoBeaconsFound:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    firstBeaconTimer = 0;
                    secondBeaconTimer = 0;
                    rightTankTurn(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        nextState = DriveToFindTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case BEACON_DETECTED:
                    // find first beacon 
                    // grab current time
                    // scan for second beacon 
                    // grab current time
                    // if time diff is less than 1500, then take 3700 - time diff
                    // and turn that amount
                    // else, turn timediff
                    // then, drive forward
                    if (firstBeaconTimer == 0) {
                        firstBeaconTimer = ES_Timer_GetTime();
                        printf("Just saw the first beacon at time %d", firstBeaconTimer);
                    } else if (firstBeaconTimer != 0 && secondBeaconTimer == 0) {
                        secondBeaconTimer = ES_Timer_GetTime();
                        printf("Just saw the second beacon at time %d", secondBeaconTimer);
                    }

                    if (secondBeaconTimer != 0 && firstBeaconTimer != 0) {
                        if (((firstBeaconTimer - secondBeaconTimer) / 2) < 1500) {
                            ES_Timer_InitTimer(1,
                                    (3700 - ((firstBeaconTimer - secondBeaconTimer) / 2)));
                            printf("CASE ONE: Set the timer to be %d", 
                                    (3700 - ((firstBeaconTimer - secondBeaconTimer) / 2)));
                        } else {
                            ES_Timer_InitTimer(1, ((firstBeaconTimer - secondBeaconTimer) / 2));
                            printf("CASE TWO: Set the timer to be %d", 
                                    ((firstBeaconTimer - secondBeaconTimer) / 2));
                        }
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case ThreeBeaconsFound:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    firstBeaconTimer = 0;
                    secondBeaconTimer = 0;
                    thirdBeaconTimer = 0;
                    rightTankTurn(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        nextState = DriveToFindTape;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    printf("\r\n Just detected a beacon \r\n");
                    if (firstBeaconTimer > (ES_Timer_GetTime() - (3700 / 3))) {
                        // you've turned far enough, stop
                        leftTankTurn(MEDIUM_MOTOR_SPEED);
                        ES_Timer_InitTimer(1, 3700 / 6);
                    } else {
                        printf("\r\n first beacon timer wasn't big enough \r\n");
                        printf("\r\n first beacon timer is %d, ES_get_time is %d \r\n",
                                firstBeaconTimer, ES_Timer_GetTime());
                    }
                    firstBeaconTimer = ES_Timer_GetTime();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case DriveToFindTape:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveForward(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    // let this event pass up to the top level
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFindingTapeSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFindingTapeSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

