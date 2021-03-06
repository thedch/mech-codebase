/*
 * File:   EventChecker.c
 * Author: Daniel Hunter
 *
 * Event checker for team 7 in the final project of CMPE 118 at UCSC, fall 2016. 
 * Used to detect various events and operate the robot with the ES framework provided. 
 *
 * Created on Nov 5 2016
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "EventChecker.h"
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
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
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

uint8_t CheckFrontLeftBumper(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = FRONT_LEFT_BUMPER_LOW;
    static int leftBumperDebounceVar;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    if ((IO_PortsReadPort(PORTZ) & PIN5) == PIN5) {
        leftBumperDebounceVar++;
    } else if ((IO_PortsReadPort(PORTZ) & PIN6) == PIN6) {
        leftBumperDebounceVar++;
    } else {
        leftBumperDebounceVar = 0;
    }

    if (leftBumperDebounceVar > 100) {
        curEvent = FRONT_LEFT_BUMPER_HIT;
    } else {
        curEvent = FRONT_LEFT_BUMPER_LOW;
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

uint8_t CheckFrontRightBumper(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = FRONT_RIGHT_BUMPER_LOW;
    static int rightBumperDebounceVar;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    // X10 or X09

    if ((IO_PortsReadPort(PORTX) & PIN9) == PIN9) {
        rightBumperDebounceVar++;
    } else if ((IO_PortsReadPort(PORTX) & PIN10) == PIN10) {
        rightBumperDebounceVar++;
    } else {
        rightBumperDebounceVar = 0;
    }

    if (rightBumperDebounceVar > 200) {
        curEvent = FRONT_RIGHT_BUMPER_HIT;
    } else {
        curEvent = FRONT_RIGHT_BUMPER_LOW;
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

uint8_t CheckBackTrackWireSensors(void) {

    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    int currentBackTrackWire = 0;
    static int previousBackTrackWire = 0;
    static int backTrackWireDebounceVar = 0;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    currentBackTrackWire = AD_ReadADPin(BACK_TRACK_WIRE_SENSOR_PIN);

    if (currentBackTrackWire > BACK_TRACK_WIRE_DATA_THRESHOLD) {
        if (currentBackTrackWire > previousBackTrackWire) {
            previousBackTrackWire = currentBackTrackWire;
            backTrackWireDebounceVar = 0;
        } else {
            backTrackWireDebounceVar++;
        }
    } else {
        previousBackTrackWire = 0;
    }

    if (backTrackWireDebounceVar > BACK_TRACK_WIRE_DEBOUNCE_THRESHOLD) {
        curEvent = BACK_TRACK_WIRE_DETECTED;
    } else {
        curEvent = BACK_TRACK_WIRE_LOW;
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        //        thisEvent.EventParam = 0x0F;
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

uint8_t CheckFrontTrackWireSensors(void) {

    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    int currentFrontTrackWire = 0;
    static int previousFrontTrackWire = 0;
    static int frontTrackWireDebounceVar = 0;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    currentFrontTrackWire = AD_ReadADPin(FRONT_TRACK_WIRE_SENSOR_PIN);

    if (currentFrontTrackWire > FRONT_TRACK_WIRE_DATA_THRESHOLD) {
        if (currentFrontTrackWire > previousFrontTrackWire) {
            previousFrontTrackWire = currentFrontTrackWire;
            frontTrackWireDebounceVar = 0;
        } else {
            // you appear to be leaving a peak
            frontTrackWireDebounceVar++;
        }
    } else {
        previousFrontTrackWire = 0;
    }

    if (frontTrackWireDebounceVar > FRONT_TRACK_WIRE_DEBOUNCE_THRESHOLD) {
        curEvent = FRONT_TRACK_WIRE_DETECTED;
    } else {
        curEvent = FRONT_TRACK_WIRE_LOW;
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

uint8_t CheckBeaconDetector(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static int beaconDebounceVar = 0;
    static ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    
//    int tempVar = AD_ReadADPin(BEACON_DETECTOR_PIN);

    if (AD_ReadADPin(BEACON_DETECTOR_PIN) > 20) {
//        printf("You're inside the beacon detector event checker for loop \r\n");
//        printf("\r\n current data is %d", tempVar);
        // Check the beacon detector
        if (AD_ReadADPin(BEACON_DETECTOR_PIN) < BEACON_DETECTOR_THRESHOLD) {
            beaconDebounceVar++;
        } else if (AD_ReadADPin(BEACON_DETECTOR_PIN) > BEACON_DETECTOR_THRESHOLD) {
            beaconDebounceVar = 0;
        }

        if (beaconDebounceVar > BEACON_DEBOUNCE_THRESHOLD) {
            curEvent = BEACON_DETECTED;
        } else {
            curEvent = BEACON_LOST;
        }
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
    static ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    if (AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
        curEvent = CENTER_TAPE_FOUND;
        //        thisEvent.EventParam = thisEvent.EventParam | 0b0010;
    } else if (AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN) < WHITE_THRESHOLD) {
        curEvent = CENTER_ON_WHITE;
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

uint8_t LCheckTapeSensors(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    // Set the current event to be no event, this is only changed if one of the 
    // if statements triggers
    //    curEvent = ES_NO_EVENT;
    thisEvent.EventParam = 0;
    // Check the tape sensors

    if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
        curEvent = LEFT_TAPE_FOUND;
        thisEvent.EventParam = thisEvent.EventParam | 0b0010;
    } else if (AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN) < WHITE_THRESHOLD) {
        curEvent = LEFT_ON_WHITE;
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

uint8_t RCheckTapeSensors(void) {
    // Init Code
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) > BLACK_TAPE_THRESHOLD) {
        curEvent = RIGHT_TAPE_FOUND;
        thisEvent.EventParam = thisEvent.EventParam | 0b0010;
    } else if (AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN) < WHITE_THRESHOLD) {
        curEvent = RIGHT_ON_WHITE;
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