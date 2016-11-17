/*
 * File:   TemplateEventChecker.c
 * Author: Gabriel Hugh Elkaim
 *
 * Template file to set up typical EventCheckers for the  Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the
 * names will have to be changed to match your code.
 *
 * This EventCheckers file will work with both FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This file includes a test harness that will run the event detectors listed in the
 * ES_Configure file in the project, and will conditionally compile main if the macro
 * EVENTCHECKER_TEST is defined (either in the project or in the file). This will allow
 * you to check you event detectors in their own project, and then leave them untouched
 * for your project unless you need to alter their post functions.
 *
 * Created on September 27, 2013, 8:37 AM
 */

//At 11/15/16 2:46PM, William started messing with this file. Blame him if is is now brokend
// As of 11/15/16 5:29PM, William Finished the forst track wire with debouncing.
// TODO: made adjustments to consider latency: maybe slow down driving?
// At 11/15/16, William started trying to make a better track wire debouncing
/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "TemplateEventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "IO_Ports.h"
#include "MyHelperFunctions.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175

// only define one of the following track wire macros
#define ORIGINAL_TRACK_WIRE
//#define WILLIAM_TRACK_VERSION_1
//#define WILLIAM_TRACK_VERSION_2

#define TRACK_WIRE_BUFFER 50 
#define FRONT_TRACK_THRESHOLD 700
#define BACK_TRACK_THRESHOLD 400

// enum for various track wire detection states. UNSTABLE refers to our unknown state on start-up

enum TrackStatus {
    UNSTABLE, OFF, ON
};
/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */

//These are the variables used to handle debouncing of the track wires.
//static int trackStateReady = 0; // this variable is used to ignore events the first 8 times the track wire event checker is run
static uint8_t backTrackRecord;
static uint8_t frontTrackRecord;
static enum TrackStatus backLastState = UNSTABLE;
static enum TrackStatus backCurrentState = UNSTABLE;
static enum TrackStatus frontLastState = UNSTABLE;
static enum TrackStatus frontCurrentState = UNSTABLE;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t TemplateCheckBattery(void) {
    return 0;
    
//    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
//    ES_EventTyp_t curEvent;
//    ES_Event thisEvent;
//    uint8_t returnVal = FALSE;
//    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage
//
//    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
//        curEvent = BATTERY_CONNECTED;
//    } else {
//        curEvent = BATTERY_DISCONNECTED;
//    }
//    
//    if (curEvent != lastEvent) { // check for change from last time
//        thisEvent.EventType = curEvent;
//        thisEvent.EventParam = batVoltage;
//        returnVal = TRUE;
//        lastEvent = curEvent; // update history
//#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
//        PostTemplateHSM(thisEvent);
//#else
//        SaveEvent(thisEvent);
//#endif   
//    }
//    return (returnVal);
}

uint8_t CheckBumpers(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // TODO: Add the two new limit switches

    // Check the three limit switches
    if (FRONT_LEFT_LIMIT_SWITCH_PIN && FRONT_RIGHT_LIMIT_SWITCH_PIN) {
        curEvent = FRONT_BUMPERS_HIT;
    } else if (FRONT_LEFT_LIMIT_SWITCH_PIN) {
        curEvent = FRONT_LEFT_BUMPER_HIT;
    } else if (FRONT_RIGHT_LIMIT_SWITCH_PIN) {
        curEvent = FRONT_RIGHT_BUMPER_HIT;
    } else if (BACK_LIMIT_SWITCH_PIN) {
//        curEvent = BACK_BUMPER_HIT;
    } else {
        curEvent = ES_NO_EVENT;
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

#ifdef ORIGINAL_TRACK_WIRE

uint8_t CheckTrackWireSensors(void) {

    // To revert William's changes to this function, undefine WILLIAM_TRACK_WIRE_ALGORITHM at the top
    // DO NOT try to change this directly, might miss a start/endpoint

    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static int backTrackWireDebounceVar;
    static int frontTrackWireDebounceVar;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // Check the two track wire sensors
    //    if (((AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN)) < 700) && 
    //            ((AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN)) < 700)) {

    // TODO: Fix the simultaneous track wire sensor event

//    if ((AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN)) < 400) {
//        frontTrackWireDebounceVar++;
//    } else if ((AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN)) < 400) {
//        curEvent = BACK_TRACK_WIRE_DETECTED;
//    } else {
//        curEvent = ES_NO_EVENT;
//    }


    if ((AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN)) < 400) {
        curEvent = FRONT_TRACK_WIRE_DETECTED;
    } else if ((AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN)) < 400) {
        curEvent = BACK_TRACK_WIRE_DETECTED;
    } else {
        curEvent = ES_NO_EVENT;
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        //        thisEvent.EventParam = bumped;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}
#endif

#ifdef WILLIAM_TRACK_VERSION_1

uint8_t CheckTrackWireSensors(void) {
    // init code
    //static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    // shift some values over to make room for the new value
    frontTrackRecord = frontTrackRecord << 1;
    backTrackRecord = backTrackRecord << 1;
    // update each Track wire record with a 1 in the rightmost bit if we detect the track wire
    if ((AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN)) < FRONT_TRACK_THRESHOLD) {
        frontTrackRecord = frontTrackRecord + 1;
    }
    if ((AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN)) < BACK_TRACK_THRESHOLD) {
        backTrackRecord = backTrackRecord + 1;
    }
    // update the current status if necessary
    // update the front 
    if (frontTrackRecord == 0xFF) {
        frontCurrentState = ON;
        //printf("FRONT ON\r\n");
    } else if (frontTrackRecord == 0x00) {
        frontCurrentState = OFF;
        //printf("FRONT OFF\r\n");
    }
    if (backTrackRecord == 0xFF) {
        backCurrentState = ON;
        //printf("BACK ON\r\n");
    } else if (backTrackRecord == 0x00) {
        backCurrentState = OFF;
        //printf("BACK OFF\r\n");
    }
    // check for state changes and post events accordingly
    curEvent = ES_NO_EVENT;
    if (frontCurrentState == ON && frontLastState == OFF) {
        curEvent = FRONT_TRACK_WIRE_DETECTED;
        returnVal = TRUE;
    } else {
        // room to add lost track wire event if needed
    }
    if (backCurrentState == ON && backLastState == OFF) {
        curEvent = BACK_TRACK_WIRE_DETECTED;
        returnVal = TRUE;
    } else {
        // room to add lost track wire event
    }
    // update the last states of each track wire
    frontLastState = frontCurrentState;
    backLastState = backCurrentState;

    //prepare thisEvent for posting if there was an event 

    if (returnVal) {
        thisEvent.EventType = curEvent;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}
#endif
#ifdef WILLIAM_TRACK_VERSION_2

uint8_t CheckTrackWireSensors(void) {
    // Init Code
    static ES_EventTyp_t lastFrontEvent = ES_NO_EVENT;
    static ES_EventTyp_t lastBackEvent = ES_NO_EVENT;
    static int frontTrackDebounceVar = 0;
    static int backTrackDebounceVar = 0;
    ES_EventTyp_t curFrontEvent = ES_NO_EVENT;
    ES_EventTyp_t curBackEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // check if the front track wire is detecting a beacon
    if ((AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN)) < FRONT_TRACK_THRESHOLD) {
        // increment the counter
        frontTrackDebounceVar = frontTrackDebounceVar + 1;
    } else {
        //reset the counter if it bounced low
        frontTrackDebounceVar = 0;
    }
    //repeat for the back track wire
    if ((AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN)) < BACK_TRACK_THRESHOLD) {
        backTrackDebounceVar = backTrackDebounceVar + 1;
    } else {
        backTrackDebounceVar = 0;
    }

    //alternative to storing previous state is using == instead of >= to avoid flooding
    if (frontTrackDebounceVar >= TRACK_WIRE_BUFFER) {
        curFrontEvent = FRONT_TRACK_WIRE_DETECTED;
    } else {
        curFrontEvent = FRONT_TRACK_WIRE_LOST;
    }
    if (backTrackDebounceVar >= TRACK_WIRE_BUFFER) {
        curBackEvent = BACK_TRACK_WIRE_DETECTED;
    } else {
        curBackEvent = BACK_TRACK_WIRE_LOST;
    }

    if (curFrontEvent != lastFrontEvent) {
        // check for change from last time
        //        printf("\r\ncurEvent != lastEvent\r\n");
        thisEvent.EventType = curFrontEvent;
        returnVal = TRUE;
        lastFrontEvent = curFrontEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    if (curBackEvent != lastBackEvent) {
        // check for change from last time
        //        printf("\r\ncurEvent != lastEvent\r\n");
        thisEvent.EventType = curBackEvent;
        //        thisEvent.EventParam = bumped;
        returnVal = TRUE;
        lastBackEvent = curBackEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }

    return (returnVal);
}
#endif

uint8_t CheckBeaconDetector(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static int beaconDebounceVar = 0;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    //       printf("%d\r\n", AD_ReadADPin(BEACON_DETECTOR_PIN));

    // Check the beacon detector
    if (AD_ReadADPin(BEACON_DETECTOR_PIN) < BEACON_DETECTOR_THRESHOLD) {
        beaconDebounceVar++;
        //printf("%d\r\n", AD_ReadADPin(BEACON_DETECTOR_PIN));
    } else if (AD_ReadADPin(BEACON_DETECTOR_PIN) > BEACON_DETECTOR_THRESHOLD) {
        //printf("\r\ndebounce = 0\r\n");
        beaconDebounceVar = 0;
    }

    if (beaconDebounceVar > BEACON_DEBOUNCE_THRESHOLD) {
        curEvent = BEACON_DETECTED;
    } else {
        curEvent = BEACON_LOST;
    }

    if (curEvent != lastEvent) { // check for change from last time
        //        printf("\r\ncurEvent != lastEvent\r\n");
        thisEvent.EventType = curEvent;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

uint8_t CheckTapeSensors(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // Set the current event to be no event, this is only changed if one of the 
    // if statements triggers
    //    curEvent = ES_NO_EVENT;
    thisEvent.EventParam = 0;
    // Check the tape sensors

    // TODO: LEFT TAPE SENSOR CURRENTLY BROKEN, FIX THIS
    //    if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
    //        curEvent = TAPE_FOUND;
    //        thisEvent.EventParam = thisEvent.EventParam | 0b0100;
    //    } 

    if (AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
        curEvent = TAPE_FOUND;
        thisEvent.EventParam = thisEvent.EventParam | 0b0010;
    } else if (AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN) < WHITE_THRESHOLD) {
        curEvent = ON_WHITE;
    }

    // TODO: For now, I'm just going to use the front tape sensor for tracking
    //        if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
    //            curEvent = TAPE_FOUND;
    //            thisEvent.EventParam = thisEvent.EventParam | 0b0001;
    //        }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return (returnVal);
}

uint8_t LCheckTapeSensors(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // Set the current event to be no event, this is only changed if one of the 
    // if statements triggers
    //    curEvent = ES_NO_EVENT;
    thisEvent.EventParam = 0;
    // Check the tape sensors

    // TODO: LEFT TAPE SENSOR CURRENTLY BROKEN, FIX THIS
    //    if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
    //        curEvent = TAPE_FOUND;
    //        thisEvent.EventParam = thisEvent.EventParam | 0b0100;
    //    } 



    if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
        curEvent = LEFT_TAPE_FOUND;
        thisEvent.EventParam = thisEvent.EventParam | 0b0010;
    } else if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) < WHITE_THRESHOLD) {
        curEvent = LEFT_ON_WHITE;
    }


    // TODO: For now, I'm just going to use the front tape sensor for tracking
    //        if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
    //            curEvent = TAPE_FOUND;
    //            thisEvent.EventParam = thisEvent.EventParam | 0b0001;
    //        }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return (returnVal);
}

uint8_t RCheckTapeSensors(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // Set the current event to be no event, this is only changed if one of the 
    // if statements triggers
    //    curEvent = ES_NO_EVENT;
    thisEvent.EventParam = 0;
    // Check the tape sensors

    // TODO: LEFT TAPE SENSOR CURRENTLY BROKEN, FIX THIS
    //    if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
    //        curEvent = TAPE_FOUND;
    //        thisEvent.EventParam = thisEvent.EventParam | 0b0100;
    //    } 


    if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
        curEvent = RIGHT_TAPE_FOUND;
        thisEvent.EventParam = thisEvent.EventParam | 0b0010;
    } else if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) < WHITE_THRESHOLD) {
        curEvent = RIGHT_ON_WHITE;
    }
    // TODO: For now, I'm just going to use the front tape sensor for tracking
    //        if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
    //            curEvent = TAPE_FOUND;
    //            thisEvent.EventParam = thisEvent.EventParam | 0b0001;
    //        }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return (returnVal);
}

//uint8_t GetOutTrack(void) {
//    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
//    ES_EventTyp_t curEvent;
//    ES_Event thisEvent;
//    uint8_t returnVal = FALSE;
//    if (GetOutFlag) {
//        curEvent = GET_OUT_TRACK;
//    }
//
//    if (curEvent != lastEvent) { // check for change from last time
//        thisEvent.EventType = curEvent;
//        returnVal = TRUE;
//        lastEvent = curEvent; // update history
//#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
//        PostTemplateHSM(thisEvent);
//#else
//        SaveEvent(thisEvent);
//#endif   
//    }
//    return (returnVal);
//}






/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST macro is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */
    AD_Init();
    AD_AddPins(AD_PORTV4 | AD_PORTV8 | AD_PORTV6 | AD_PORTV3);
    printf("Just added the AD pins \r\n");
    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                }
                break;
            }
        }
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif