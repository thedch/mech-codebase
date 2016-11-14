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
#include "ES_Events.h"
#include "BOARD.h"
#include "TopLevelHSM.h"
#include "TrackWireSubHSM.h"
#include "MyHelperFunctions.h"

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
            GETCLOSER,
            StartCentering
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
	"GETCLOSER",
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
static int AntiJamCounter = 0;
static int BEACONTIMER_START = 0;
static int BEACONTIMER_STOP = 0;
static int BEACONTIMER_DIFF = 0;
#define BEACONTIMER_CENTERED ((4*BEACONTIMER_DIFF)/10)

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

    // TODO: Confirm track wires will not be changed during the match
    // Possibly a beer challenge thing?

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
                    //motorsOff();
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
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case FoundTrackWire:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveBackward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(1, 1200);
                    break;
                case ES_TIMEOUT:
                    //motorsOff();
                    ThisEvent.EventType = ES_NO_EVENT;
                    nextState = LoadingAmmo;
                    makeTransition = TRUE;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case LoadingAmmo:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    driveForward(MEDIUM_MOTOR_SPEED);
                    ES_Timer_InitTimer(1, 1700);
                    break;
                case ES_TIMEOUT:
                    motorsOff();
                    ThisEvent.EventType = ES_NO_EVENT;
                    nextState = AntiJamPhaseOne;
                    makeTransition = TRUE;
                    break;
                case BEACON_DETECTED:
                case BEACON_LOST:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
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
                default: // all unhandled events pass the event back up to the next level
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
                //case BEACON_DETECTED:
                //    leftTankTurn(MEDIUM_MOTOR_SPEED);
                //    ThisEvent.EventType = ES_NO_EVENT;
                //    break;
                //case BEACON_LOST:
                //    ThisEvent.EventType = ES_NO_EVENT;
                //    break;
                case ES_NO_EVENT:
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            
            
 /////////////////////MOVE TO BEACON DETECT SUBHMS//////////////////////           
        case BeaconScanning:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    rightTankTurn(SLOW_MOTOR_SPEED);
                    break;
                    
                case BEACON_DETECTED:
                    nextState = StartCentering;
                    makeTransition = TRUE;
                    break;

                case ES_NO_EVENT:
                    break;

                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            
        case GETCLOSER:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(1, 1500);
                    driveForward(SLOW_MOTOR_SPEED);
                break;
                
                case BEACON_LOST:
                    rightTankTurn(SLOW_MOTOR_SPEED);
                    nextState = BeaconScanning;
                    makeTransition = TRUE;
                    break;
                
                case ES_TIMEOUT:
            nextState = StartCentering;
                    makeTransition = TRUE;
                    break;
                
//                case TAPE_FOUND:
//                    motorsOff();
//                    break;
                
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
                    
                    
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            
            
        case BeaconFound:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    BEACONTIMER_START = ES_Timer_GetTime();
                    //driveForward(SLOW_MOTOR_SPEED);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    
                case BEACON_LOST:
                    
                    BEACONTIMER_STOP = ES_Timer_GetTime();
                    BEACONTIMER_DIFF = BEACONTIMER_STOP - BEACONTIMER_START;

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
                    nextState = GETCLOSER;
                    makeTransition = TRUE;
                    break;
                    
                


                default: // all unhandled events pass the event back up to the next level
                    break;
            }

            break;
///////////////////////////////////////////////////////////////////////////////////////


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

