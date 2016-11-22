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

// At 11/15/16 2:46PM, William started messing with this file. Blame him if is is now broken
/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Events.h"
#include "BOARD.h"
#include "TopLevelHSM.h"
#include "FirstBeaconSubHSM.h"
#include "MyHelperFunctions.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    DroppingAmmoAtFirstBeacon,
    ScanningForSecondBeacon,
    GoAroundFirstBeacon,
    DroppingAmmoAtSecondBeacon,
    GetCloserToBeacon,
    StartCentering,
    BeaconFound,
    TargetFound,
    //    RelocateBehindFirstBeacon,
    //    RelocateBesideFirstBeacon,
    //    StartRelocating,


} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"DroppingAmmoAtFirstBeacon",
	"ScanningForSecondBeacon",
	"GoAroundFirstBeacon",
	"DroppingAmmoAtSecondBeacon",
	"GetCloserToBeacon",
	"StartCentering",
	"BeaconFound",
	"TargetFound",
};


#define PATROL_TIMER 3
#define PATROL_DURATION 1000
#define BEACONTIMER_CENTERED ((5*beaconTimerDelta)/10)

static int beaconTimerStart = 0;
static int beaconTimerStop = 0;
static int beaconTimerDelta = 0;
static int beaconTurningFlag = 0;
static int beaconLookingFlag = 0;

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
static int BallDropFlag;
static int FirstBeaconLostFlag;
static int FinishedBackingAwayFromFirstBeaconFlag;


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
uint8_t InitFirstBeaconSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFirstBeaconSubHSM(INIT_EVENT);
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
ES_Event RunFirstBeaconSubHSM(ES_Event ThisEvent) {
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
                nextState = DroppingAmmoAtFirstBeacon;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

            // Intermediate state between init and secure perimeter
        case DroppingAmmoAtFirstBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motorsOff();
                    ES_Timer_InitTimer(9, 450);
                    break;
                case ES_TIMEOUT:
                    ES_Timer_InitTimer(3, 550);
                    if (BallDropFlag < 4) {
                        toggleServo();
                    } else if (BallDropFlag > 7) {
                        // done dropping balls, go find a new beacon
                        nextState = ScanningForSecondBeacon;
                        makeTransition = TRUE;
                        BallDropFlag = 0;
                    }
                    BallDropFlag++;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

            //            
            //        case StartRelocating:
            //                    switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    driveBackward(MEDIUM_MOTOR_SPEED);
            //                    ES_Timer_InitTimer(7, 700);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                
            //                case ES_TIMEOUT:
            //                    // when timer expires, start turning and try to lose beacon
            //                    nextState = RelocateBesideFirstBeacon;
            //                        makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                default:
            //                    break;
            //            }
            //            break;
            //            case RelocateBesideFirstBeacon:
            //                    switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    fiftyPercentRightTurn(SLOW_MOTOR_SPEED);
            //                    ES_Timer_InitTimer(7, 2500);
            //                    
            //                    break;
            //                
            //                case ES_TIMEOUT:
            //                    // when timer expires, start turning and try to lose beacon
            //                    
            //                    nextState = RelocateBehindFirstBeacon;
            //                        makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                default:
            //                    break;
            //            }
            //            break;
            //            
            //            case RelocateBehindFirstBeacon:
            //                    switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    fiftyPercentLeftTurn(SLOW_MOTOR_SPEED);
            //                    ES_Timer_InitTimer(7, 2500);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                
            //                case ES_TIMEOUT:
            //                    // when timer expires, start turning and try to lose beacon
            //
            //                     nextState = ScanningForSecondBeacon;
            //                        makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                
            //                
            //                default:
            //                    break;
            //            }
            //            break;

        case ScanningForSecondBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    FirstBeaconLostFlag = 0;
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(7, 500); 
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 7) {
                        // when timer expires, start turning and try to lose beacon
                        rightTankTurn(SLOW_MOTOR_SPEED);
                        FinishedBackingAwayFromFirstBeaconFlag = 1;
                    } else if (ThisEvent.EventParam == 9) {
                        // just finished first 180, turn back until you lose a beacon
                        leftTankTurn(MEDIUM_MOTOR_SPEED);
                        FirstBeaconLostFlag = 0; // reset flag so you don't trip on the original beacon
                        beaconTurningFlag = 1;
                    } else if (ThisEvent.EventParam == 10) {
                        // just finished your 2nd 180, keep going until you see original beacon
                        beaconTurningFlag = 2;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    // TODO: Add in code to make sure we didn't turn too far
                    if (beaconTurningFlag == 2) {
                        // go to a state to drive around the beacon
                        nextState = GoAroundFirstBeacon;
                        makeTransition = TRUE;
                    } else if (FirstBeaconLostFlag == 1) {
                        nextState = StartCentering;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_LOST:
                    if (FinishedBackingAwayFromFirstBeaconFlag == 1) {
                        FirstBeaconLostFlag = 1;
                        ES_Timer_InitTimer(9, 1700); // Set a turn for 180 degrees
                        FinishedBackingAwayFromFirstBeaconFlag = 0;
                    } else if (beaconTurningFlag == 1) {
                        // you just passed the beacon after the first 180
                        FirstBeaconLostFlag = 1;
                        ES_Timer_InitTimer(10, 1700); // Set a turn for another 180 degrees
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;

        case GoAroundFirstBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    rightTankTurn(MEDIUM_MOTOR_SPEED);
                    ES_Timer_StopTimer(9);
                    ES_Timer_InitTimer(9, 9.7 * 45); // Set a turn for 80 degrees
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 9) {
                        variablePercentLeftTurn(75, MEDIUM_MOTOR_SPEED);
                        ES_Timer_StopTimer(10);
                        ES_Timer_InitTimer(10, 3000); // timer to start long turn around beacon
                    } else if (ThisEvent.EventParam == 10) {
                        // just finished long left turn
                        leftTankTurn(SLOW_MOTOR_SPEED);
                        beaconLookingFlag = 1;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    if (beaconLookingFlag == 1) {
                        nextState = StartCentering;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_LOST:
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
                    //                case BEACON_LOST:
                    //                    nextState = BeaconScanning;
                    //                    makeTransition = TRUE;
                    //                    break;
                case ES_TIMEOUT:
                    nextState = StartCentering;
                    makeTransition = TRUE;
                    break;
                case TAPE_ON:
                    if (ThisEvent.EventParam & 0x02) {
                        nextState = DroppingAmmoAtSecondBeacon;
                        makeTransition = TRUE;
                    } else { // treat this like center on white
                        ;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
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
                default:
                    break;
            }
            break;

        case DroppingAmmoAtSecondBeacon:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motorsOff();
                    ES_Timer_InitTimer(3, 450);
                    break;
                case ES_TIMEOUT:
                    if (BallDropFlag < 3) {
                        ES_Timer_InitTimer(3, 750);
                        toggleServo();
                        BallDropFlag++;
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                default:
                    break;
            }
            break;

        default:
            break;

    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFirstBeaconSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFirstBeaconSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

