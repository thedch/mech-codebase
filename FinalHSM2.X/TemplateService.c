/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "IO_Ports.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TemplateService.h"
#include "ES_Events.h"
#include "MyHelperFunctions.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BATTERY_DISCONNECT_THRESHOLD 175

#define LIGHT_LOW_THRESHOLD 200
#define LIGHT_HIGH_THRESHOLD 550

#define NUM_TAPE_SENSORS 3

#define LEFT 0
#define CENTER 1
#define RIGHT 2

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

static void TapeSensorCompareHysteresis(void);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */
static int StartSampling;

static int LeftLEDOnReading;
static int CenterLEDOnReading;
static int RightLEDOnReading;

static int LeftLEDOffReading;
static int CenterLEDOffReading;
static int RightLEDOffReading;

static int LeftLEDDiffReading;
static int CenterLEDDiffReading;
static int RightLEDDiffReading;

static int PrevRightDiffReading = WHITE;
static int PrevCenterDiffReading = WHITE;
static int PrevLeftDiffReading = WHITE;

int PrevMeasuredValues[NUM_TAPE_SENSORS] = {};

int TapeValues[NUM_TAPE_SENSORS] = {}; // 0 = left, 1 = center, 2 = right

static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

uint8_t TapeSensorEventChecker(void) {

    // Either return true or false 
    if (StartSampling == 0) {
        //        printf("Entering TapeSensorEventChecker \r\n");
        // set LED high
        IO_PortsSetPortBits(PORTY, PIN8);
        // start timer 
        ES_Timer_InitTimer(15, 5);
        // set flag down
        StartSampling = 1;
        return TRUE;
    } else {
        return FALSE;
    }
}

uint8_t TapeSensorLEDOn(ES_Event ThisEvent) {
    if (ThisEvent.EventType == ES_TIMEOUT) {
        //        printf("Entering TapeSensorLEDOn \r\n");
        // take a reading of the LED on reading 
        LeftLEDOnReading = AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN);
        CenterLEDOnReading = AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN);
        RightLEDOnReading = AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN);
        // clear the LED power
        IO_PortsClearPortBits(PORTY, PIN8);
        // set a timer to call LED off
        ES_Timer_InitTimer(14, 5);
    }
}

uint8_t TapeSensorLEDOff(ES_Event ThisEvent) {
    if (ThisEvent.EventType == ES_TIMEOUT) {
        //        printf("Entering TapeSensorLEDOff \r\n");
        // get readings for the LED off
        LeftLEDOffReading = AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN);
        CenterLEDOffReading = AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN);
        RightLEDOffReading = AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN);

        TapeSensorCompareHysteresis();
    }
}

static void TapeSensorCompareHysteresis(void) {
    int CompareValue = 0;
    int WhiteValues[NUM_TAPE_SENSORS] = {};
    ES_Event ThisEvent;
    // find the difference between the two readings
    LeftLEDDiffReading = LeftLEDOffReading - LeftLEDOnReading;
    CenterLEDDiffReading = CenterLEDOffReading - CenterLEDOnReading;
    RightLEDDiffReading = RightLEDOffReading - RightLEDOnReading;

    if (LeftLEDDiffReading < LIGHT_LOW_THRESHOLD && PrevMeasuredValues[0] == WHITE) {
        TapeValues[0] = BLACK;
    } else if (LeftLEDDiffReading > LIGHT_HIGH_THRESHOLD && PrevMeasuredValues[0] == BLACK) {
        TapeValues[0] = WHITE;
    }
    if (CenterLEDDiffReading < LIGHT_LOW_THRESHOLD && PrevMeasuredValues[1] == WHITE) {
        TapeValues[1] = BLACK;
    } else if (CenterLEDDiffReading > LIGHT_HIGH_THRESHOLD && PrevMeasuredValues[1] == BLACK) {
        TapeValues[1] = WHITE;
    }
    if (RightLEDDiffReading < LIGHT_LOW_THRESHOLD && PrevMeasuredValues[2] == WHITE) {
        TapeValues[2] = BLACK;
    } else if (RightLEDDiffReading > LIGHT_HIGH_THRESHOLD && PrevMeasuredValues[2] == BLACK) {
        TapeValues[2] = WHITE;
    }

    CompareValue = memcmp(TapeValues, PrevMeasuredValues, NUM_TAPE_SENSORS * sizeof (int));
    if (CompareValue != 0) {
        CompareValue = memcmp(TapeValues, WhiteValues, NUM_TAPE_SENSORS * sizeof (int));
        if (CompareValue == 0) {
            // you're entirely on white
            ThisEvent.EventType = ALL_TAPE_WHITE;
            ThisEvent.EventParam = 0;
        } else {
            ThisEvent.EventType = TAPE_ON;
            ThisEvent.EventParam = 0;
            // bitshifting to add param to the
            ThisEvent.EventParam = ThisEvent.EventParam | TapeValues[2];
            ThisEvent.EventParam = ThisEvent.EventParam << 1;
            ThisEvent.EventParam = ThisEvent.EventParam | TapeValues[1];
            ThisEvent.EventParam = ThisEvent.EventParam << 1;
            ThisEvent.EventParam = ThisEvent.EventParam | TapeValues[0];
        }
        PostTemplateHSM(ThisEvent);
        //        printf("\r\nLeft: %d, Center: %d, Right: %d \r\n",
        //        LeftLEDDiffReading,
        //                CenterLEDDiffReading,
        //                RightLEDDiffReading);
    }
    memcpy(PrevMeasuredValues, TapeValues, NUM_TAPE_SENSORS * sizeof (int));
    StartSampling = 0;
}

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTapeSensorSampling(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTemplateService(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */


/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

