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
#include "RC_Servo.h"
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
    AlignWithTape,
    BeaconInWayAbort,

} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"ScanningForBeacon",
	"TapeTracking",
	"ReverseLineTracking",
	"DrivingToFindTrackWire",
	"CheckForBeaconTape",
	"AlignWithTape",
	"BeaconInWayAbort",
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
static int bumpedTurnVar;
static int lastTapeOnParam;
static int checkForBeaconTapeTurnVar;
static int BeaconFlag = 0;
static int BeaconFlagTwo = 0;
static uint32_t firstBeaconTimer;
static uint32_t secondBeaconTimer;
static BeaconOnLineFlag = 0;
static BeaconInWayFlag = 0;

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
                    ES_Timer_InitTimer(1, 3400); // frustration timer, set to exactly 360 deg
                    leftTankTurn(MEDIUM_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    if (BeaconFlag >= 0 && BeaconFlag < 3) {
                        // full rotation NOT done
                        BeaconFlag++;
                        printf("\r\n JUST SAW A BEACON ON FIRST ROTATION \r\n");
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_LOST:
                    printf("\r\n ENTERING BEACON LOST, BEACONFLAG IS CURRENTLY %d \r\n", BeaconFlag);
                    if (BeaconFlag == -2) {
                        printf("\r\n ROBOT IS FINDING TWO BEACONS TO GO BETWEEN \r\n");
                        // full rotation complete, start finding two beacons to go between
                        if (firstBeaconTimer == 0) {
                            printf("\r\n ROBOT FOUND 1ST BEACON \r\n");
                            firstBeaconTimer = ES_Timer_GetTime();
                        } else if (firstBeaconTimer != 0 && secondBeaconTimer == 0) {
                            printf("\r\n ROBOT FOUND 2ND BEACON AND SET TIMER to %d \r\n",
                                    (firstBeaconTimer - secondBeaconTimer) / 2);
                            secondBeaconTimer = ES_Timer_GetTime();
                            // you've seen two beacons and gotten the appropriate timers
                            rightTankTurn(MEDIUM_MOTOR_SPEED);
                            // I'm using the same timer a terrifying amount of times
                            ES_Timer_InitTimer(1, (secondBeaconTimer - firstBeaconTimer) / 2);
                        }
                    } else if (BeaconFlag == -1) {
                        printf("\r\n SETTING TIMER TO END TANK TURN (1 beacon scenario) \r\n");
                        // you just lost the ONLY beacon you can see, keep rotation and then gtfo
                        ES_Timer_InitTimer(1, 1500); // set a timer to avoid beacon
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        printf("\r\n Frustration timer just expired, beaconFlag is %d \r\n", BeaconFlag);
                        // Frustration timer expired
                        if (BeaconFlag == 1) {
                            // you saw ONE beacon, rotate accordingly
                            BeaconFlag = -1;
                            printf("\r\n ROBOT SAW ONE BEACON, beaconFlag is now %d \r\n", BeaconFlag);
                        } else if (BeaconFlag == 2 || BeaconFlag == 3) {
                            printf("\r\n ROBOT SAW TWO OR THREE BEACONS \r\n");
                            // you saw multiple beacons, average the difference
                            BeaconFlag = -2; // -2 indicates a full rotation has been completed AND 2+ beacons seen
                        } else if (BeaconFlag == 0) {
                            printf("\r\n ROBOT SAW NO BEACONS \r\n");
                            // no beacons were seen, go ahead and drive randomly
                            driveForward(MEDIUM_MOTOR_SPEED);
                        } else if (BeaconFlag == -1) {
                            // you're done turning after seeing only one beacon
                            // drive forward
                            printf("\r\n ROBOT FINISHED TURNING AFTER SEEING ONE BEACON \r\n");
                            driveForward(MEDIUM_MOTOR_SPEED);
                        } else if (BeaconFlag == -2) {
                            printf("\r\n ROBOT JUST FINISHED A TANK TURN (TIMING THE SPACE BETWEEN TWO BEACONS) \r\n");
                            // you've finished up a right tank turn after timing 
                            // the space between two beacons
                            driveForward(MEDIUM_MOTOR_SPEED);
                        }
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
                case FRONT_LEFT_BUMPER_HIT:
                    // You've been bumped, back up
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(BUMPED_TIMER, 400);
                    ThisEvent.EventType = ES_NO_EVENT;
                    bumpedTurnVar = 1; // 1 = LEFT
                    break;
                case FRONT_RIGHT_BUMPER_HIT:
                    // You've been bumped, back up
                    // TODO: This is probably a bad thing, you might back up off the field
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(BUMPED_TIMER, 500);
                    ThisEvent.EventType = ES_NO_EVENT;
                    bumpedTurnVar = 2; // 2 = RIGHT
                    break;
                case TAPE_ON:
                    if (ThisEvent.EventParam & 0x02) {
                        printf("\r\n Just saw center tape, leaving beaconScanning \r\n");
                        motorsOff();
                        nextState = TapeTracking;
                        makeTransition = TRUE;
                    }
                    // TODO: Grab side tape events as well?
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                case BACK_TRACK_WIRE_DETECTED:
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
                    ES_Timer_InitTimer(7, 100);
                    //                    ninetyPercentLeftTurn(SLOW_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_ON:
                    if ((ThisEvent.EventParam & 0x02) == 0x02) {
                        rightMotor(REVERSE, MEDIUM_MOTOR_SPEED);
                    } else if ((ThisEvent.EventParam & 0x04) == 0x04) {
                        // your right tape sensor is on. this is bad.


                        /////////////////////CHANGES MADE HERE


                        nextState = BeaconInWayAbort;
                        makeTransition = TRUE;
                        //There is a beacon in path
                        //go to abort state
                        //////////////////////////////

                    } else { // treat this like center on white
                        motorsOff();
                        ES_Timer_InitTimer(7, 100);
                    }
                    // TODO: If right sensor on, you're at a beacon (or just starting out at an odd angle)
                    // we may be able to respond the same way (back up, tank turn, drive fwd)
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 5) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                    }
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
                    ThisEvent.EventType = ES_NO_EVENT;
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



            /////////////////////////////////////////////////////CHANGES MADE HERE
            //Back up
            //rotate until beacon lost + 500ms
            //try to find border tape again

            //if second beacon in path, keep rotating


        case BeaconInWayAbort:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(5, 800);
                    driveBackward(SLOW_MOTOR_SPEED);
                    break;
                case TAPE_ON:
                    nextState = TapeTracking;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    rightTankTurn(SLOW_MOTOR_SPEED);
                    ES_Timer_StopTimer(5);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_LOST:
                    ES_Timer_InitTimer(7, 500);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 5) {
                        rightTankTurn(SLOW_MOTOR_SPEED);
                        ES_Timer_InitTimer(6, 800);
                    }

                    if (ThisEvent.EventParam == 6) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                    }
                    if (ThisEvent.EventParam == 7) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                case BACK_TRACK_WIRE_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    fiftyPercentReverseLeftTurn(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(BUMPED_TIMER, 700);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            /////////////////////////////////////////////////////////

        case ReverseLineTracking:
            // Backs up to align with tower
            //If dead bot instead of tower, continue forward and tape track
            //If beacon in path, keep turning until beacon lost
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    BeaconFlag = 0; // reset var
                    // TODO: Add actual reverse line tracking
                    rightMotor(REVERSE, SLOW_MOTOR_SPEED);
                    ES_Timer_InitTimer(2, 1150); // rotate to turn past the ball tower
                    printf("Entering reverseLineTracking, backing up \r\n");
                    break;
                case ES_NO_EVENT:
                    break;
                case TAPE_ON:
                    if (ThisEvent.EventParam & 0x02) {
                        if (BeaconFlag == 1) {
                            nextState = TapeTracking;
                            makeTransition = TRUE;
                        }
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_DETECTED:
                    fiftyPercentRightTurn(SLOW_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    BeaconFlag = 1;
                    break;
                case BEACON_LOST:
                    ES_Timer_InitTimer(4, 1200);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 2 && BeaconFlag == 0) {
                        printf("Timer expired in reverseLineTracking \r\n");
                        motorsOff();
                        nextState = DrivingToFindTrackWire;
                        makeTransition = TRUE;
                    } else if (ThisEvent.EventParam == 4 ||
                            ThisEvent.EventParam == BUMPED_TIMER) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_TRACK_WIRE_DETECTED:
                case BACK_TRACK_WIRE_DETECTED:
                    // ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    fiftyPercentReverseLeftTurn(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(BUMPED_TIMER, 700);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;


            //If bump hit while looking for trackwire, then dead bot in the way
            //continue forward and return to tape track
            //If beacon in path, keep turning until beacon lost
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
                            // reset flag for next use
                            nextState = TapeTracking;
                            // TODO: Make sure you didn't run into a beacon (beacon detector range finding would be cool here)
                            // go to new state to avoid beacon
                            makeTransition = TRUE;
                        }
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
                    fiftyPercentRightTurn(SLOW_MOTOR_SPEED); //beacon detected means we hit a box and there is a beacon when we try to find track wire
                    ThisEvent.EventType = ES_NO_EVENT; //keep turning until out of beacon range
                    BeaconFlagTwo = 1; //go find another ammo station
                    break;
                case BEACON_LOST:
                    ES_Timer_InitTimer(4, 1200);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 2) {
                        pastTapeFlag = 1; // set the flag to allow the robot to 
                        // re-find the tape    
                    } else if (ThisEvent.EventParam == BUMPED_TIMER && BeaconFlagTwo == 0) {
                        driveForward(MEDIUM_MOTOR_SPEED);
                    } else if (ThisEvent.EventParam == 4) {
                        driveForward(MEDIUM_MOTOR_SPEED);

                    }
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                case FRONT_RIGHT_BUMPER_HIT:
                    fiftyPercentReverseLeftTurn(MEDIUM_MOTOR_SPEED); //we hit a box while trying to find track wire
                    ES_Timer_InitTimer(BUMPED_TIMER, 700); // turn and go somewhere else
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

            //        case CheckForBeaconTape:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    rightTankTurn(MEDIUM_MOTOR_SPEED);
            //                    ES_Timer_InitTimer(4, 400);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    checkForBeaconTapeTurnVar = 1;
            //                    break;
            //                case BEACON_LOST:
            //                case BEACON_DETECTED:
            //                    // You're at a beacon, get out
            //                    // reset timers
            //                    motorsOff();
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_TIMEOUT:
            //                    if (ThisEvent.EventParam == 4 && checkForBeaconTapeTurnVar == 1) {
            //                        // finished turning left, now turn right
            //                        leftTankTurn(MEDIUM_MOTOR_SPEED);
            //                        ES_Timer_InitTimer(4, 800);
            //                        checkForBeaconTapeTurnVar = 2;
            //                    } else if (ThisEvent.EventParam == 4 && checkForBeaconTapeTurnVar == 2) {
            //                        // finished turning right, go back to tape tracking
            //                        nextState = TapeTracking;
            //                        makeTransition = TRUE;
            //                        checkForBeaconTapeTurnVar = 0; // reset the beacon var
            //                    }
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case TAPE_ON:
            //                    //                    if (ThisEvent.EventParam & 0x02) {
            //                    //                        nextState = TapeTracking;
            //                    //                        makeTransition = TRUE;
            //                    //                    }
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;

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

