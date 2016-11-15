/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
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

#include "TapeTrackingSubHSM.h" // #include all sub state machines called
// #include "TrackWireSubHSM.h" // #include all sub state machines called
#include "TrackWireSubHSM.h" // #include all sub state machines called
#include "FirstBeaconSubHSM.h"

#include "MyHelperFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <AD.h>
#include <IO_Ports.h>
#include <LED.h>
#include <pwm.h>
//#include <RC_Servo.h>
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPState,
    TapeTracking,
    AvoidingCollision,
    FollowingTrackWire,
    BeaconHunting,
    FirstBeacon,
} TemplateHSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"TapeTracking",
	"AvoidingCollision",
	"FollowingTrackWire",
	"BeaconHunting",
	"FirstBeacon",
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine
   Example: char RunAway(uint_8 seconds);*/
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTemplateHSM(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTemplateHSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateHSM(ES_Event ThisEvent)
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
ES_Event RunTemplateHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Pseudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                // Initialize all sub-state machines

                // Init Code
                PWM_Init();
               
                PWM_SetFrequency(PWM_DEFAULT_FREQUENCY);
                PWM_AddPins(LEFT_MOTOR_PWM_PIN | RIGHT_MOTOR_PWM_PIN);

                LED_Init();
                LED_AddBanks(LED_BANK1); // init all the LEDs
                LED_AddBanks(LED_BANK2);
                LED_AddBanks(LED_BANK3);

                LED_SetBank(LED_BANK1, 0b0110);
                LED_SetBank(LED_BANK2, 0x00);
                LED_SetBank(LED_BANK3, 0x00);

                // Bumper Sensor Power Pins
                IO_PortsSetPortOutputs(PORTX, PIN12);
                IO_PortsSetPortOutputs(PORTX, PIN9);
                IO_PortsSetPortOutputs(PORTX, PIN5);
                IO_PortsSetPortBits(PORTX, PIN12);
                IO_PortsSetPortBits(PORTX, PIN9);
                IO_PortsSetPortBits(PORTX, PIN5);

                // Bumper Sensor Inputs
                IO_PortsSetPortInputs(PORTX, PIN11);
                IO_PortsSetPortInputs(PORTX, PIN10);
                IO_PortsSetPortInputs(PORTX, PIN6);

                // Tape Sensor Power
                IO_PortsSetPortOutputs(PORTY, PIN8);
                IO_PortsSetPortBits(PORTY, PIN8);

                // Tape Sensor Inputs
                IO_PortsSetPortInputs(PORTZ, PIN3);
                IO_PortsSetPortInputs(PORTZ, PIN5);
                IO_PortsSetPortInputs(PORTZ, PIN7);

                AD_Init();
                AD_AddPins(AD_PORTV4 |
                        AD_PORTV8 |
                        AD_PORTV6 |
                        BEACON_DETECTOR_PIN |
                        FRONT_TRACK_WIRE_SENSOR_PIN |
                        BACK_TRACK_WIRE_SENSOR_PIN);

                InitTapeTrackingSubHSM();
                InitTrackWireSubHSM();
                InitFirstBeaconSubHSM();
                
                
//                 RC_Init();
//                 RC_AddPins(BALL_DROP_SERVO_PIN);
                 // might want to set this to 1500 instead, not sure yet
                 // TODO: determine proper init freq
//                 RC_SetPulseTime(BALL_DROP_SERVO_PIN, 2000); // set the gate to the init position
                 
                
                
                // now put the machine into the actual initial state
                nextState = TapeTracking;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case TapeTracking:
            // run sub-state machine for this state
            // NOTE: the SubState Machine runs and responds to events 
            //before anything in the this state machine does
            ThisEvent = RunTapeTrackingSubHSM(ThisEvent);

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    break;
                case ES_TIMEOUT:
                    break;
                case ES_NO_EVENT:
                    break;
                case ES_TIMERACTIVE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FRONT_BUMPERS_HIT:
                    break;
                case FRONT_LEFT_BUMPER_HIT:
                    break;
                case FRONT_RIGHT_BUMPER_HIT:
                    break;
                case BACK_BUMPER_HIT:
                    //                    nextState = Bumped;
                    //                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BACK_TRACK_WIRE_DETECTED:
                    nextState = FollowingTrackWire;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    break;
            }
            break;
        case AvoidingCollision:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motorsOff();
                    break;
                case ES_NO_EVENT:
                    break;
                default:
                    break;
            }
            break;
            
            
        case FollowingTrackWire:
            // run sub-state machine for this state
            // NOTE: the SubState Machine runs and responds to events 
            //before anything in the this state machine does
            ThisEvent = RunTrackWireSubHSM(ThisEvent);

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    break;
                case ES_EXIT:
                    break;

                case ES_TIMEOUT:
                    break;
                case ES_NO_EVENT:
                    break;


                case TAPE_FOUND:
                    

                    nextState = FirstBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;



                default:
                    break;
            }
            break;

        

        case FirstBeacon:
            ThisEvent = RunFirstBeaconSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    
                    break;
                case ES_NO_EVENT:
                    break;
                default:
                    break;
            }
            break;



        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTemplateHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTemplateHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
