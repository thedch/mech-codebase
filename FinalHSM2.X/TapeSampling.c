/*
 * File: TapeSampling.c
 * Author: Daniel Hunter
 * Special thanks to: Arun Suresh
 *
 * File used to sample the tape sensors regularly (every 5 ms) while toggling
 * the tape sensor LED. Using experimentally determined hysteresis bounds and 
 * some math, this allows for noise reduction from external sources such as
 * ceiling lights.
 * 
 * The code here was written by me, but the algorithm and design is almost a 
 * direct copy of my mentor, Arun Suresh. Many thanks to him for taking the time
 * to help me set this up.
 * 
 * Created on Nov 18 2016
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "IO_Ports.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeSampling.h"
#include "ES_Events.h"
#include "MyHelperFunctions.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BATTERY_DISCONNECT_THRESHOLD 175

#define CENTER_LIGHT_LOW_THRESHOLD 350
#define CENTER_LIGHT_HIGH_THRESHOLD 400

#define CORNER_LIGHT_LOW_THRESHOLD 450
#define CORNER_LIGHT_HIGH_THRESHOLD 650

#define NUM_TAPE_SENSORS 3
#define SAMPLE_RATE_IN_MS 10

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
static int StartSampling = 0;

static int LeftLEDOnReading;
static int CenterLEDOnReading;
static int RightLEDOnReading;

static int LeftLEDOffReading;
static int CenterLEDOffReading;
static int RightLEDOffReading;

static int LeftLEDDiffReading;
static int CenterLEDDiffReading;
static int RightLEDDiffReading;

static int GarbageLEDOFFCounter;
static int GarbageLEDONCounter;

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
        ES_Timer_InitTimer(15, SAMPLE_RATE_IN_MS);
        // set flag down
        StartSampling = 1;
        return TRUE;
    } else {
        return FALSE;
    }
}

uint8_t TapeSensorLEDOn(ES_Event ThisEvent) {

    // TODO: Add isNewDataReady functionality to prevent garbage data input
    if (ThisEvent.EventType == ES_TIMEOUT) {
        //        printf("Entering TapeSensorLEDOn \r\n");
        // take a reading of the LED on reading 
        LeftLEDOnReading = AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN);
        CenterLEDOnReading = AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN);
        RightLEDOnReading = AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN);
        // clear the LED power
        IO_PortsClearPortBits(PORTY, PIN8);
        // set a timer to call LED off
        ES_Timer_InitTimer(14, SAMPLE_RATE_IN_MS);

        //        printf("\r\n IN LED ON \r\n");

        if (LeftLEDOnReading == 0 ||
                CenterLEDOnReading == 0 ||
                RightLEDOnReading == 0) {
            GarbageLEDONCounter++;
            //            printf("GARBAGE DATA FOUND IN LED ON: %d \r\n", GarbageLEDONCounter);
        }
    }
}

uint8_t TapeSensorLEDOff(ES_Event ThisEvent) {
    if (ThisEvent.EventType == ES_TIMEOUT) {
        //        printf("Entering TapeSensorLEDOff \r\n");
        // get readings for the LED off
        LeftLEDOffReading = AD_ReadADPin(LEFT_TAPE_SENSOR_DATA_PIN);
        CenterLEDOffReading = AD_ReadADPin(CENTER_TAPE_SENSOR_DATA_PIN);
        RightLEDOffReading = AD_ReadADPin(RIGHT_TAPE_SENSOR_DATA_PIN);

        if (LeftLEDOffReading == 0 ||
                CenterLEDOffReading == 0 ||
                RightLEDOffReading == 0) {
            GarbageLEDOFFCounter++;
            //            printf("GARBAGE DATA FOUND IN LED OFF: %d \r\n", GarbageLEDOFFCounter);
        }

        if ((CenterLEDOffReading > 300) &&
                (CenterLEDOnReading > 0)&&
                ((CenterLEDOffReading - CenterLEDOnReading) > 0)) {
            TapeSensorCompareHysteresis();

        }
        StartSampling = 0;
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

    if (LeftLEDDiffReading < CORNER_LIGHT_LOW_THRESHOLD && PrevMeasuredValues[0] == WHITE) {
        TapeValues[0] = BLACK;
        //        printf("\r\n Just saw LEFT on black, diff was %d \r\n", LeftLEDDiffReading);
        //        printf("\r\n Just saw LEFT on black, LEDON was %d \r\n", LeftLEDOnReading);
        //        printf("\r\n Just saw LEFT on black, LEDOFF was %d \r\n", LeftLEDOffReading);
    } else if (LeftLEDDiffReading > CORNER_LIGHT_HIGH_THRESHOLD && PrevMeasuredValues[0] == BLACK) {
        TapeValues[0] = WHITE;
        //        printf("\r\n Just saw LEFT on white, diff was %d \r\n", LeftLEDDiffReading);
        //        printf("\r\n Just saw LEFT on white, LEDON was %d \r\n", LeftLEDOnReading);
        //        printf("\r\n Just saw LEFT on white, LEDOFF was %d \r\n", LeftLEDOffReading);
    }

    if (CenterLEDDiffReading < CENTER_LIGHT_LOW_THRESHOLD && PrevMeasuredValues[1] == WHITE) {
        TapeValues[1] = BLACK;
        //        printf("\r\n Just saw center on black, diff was %d \r\n", CenterLEDDiffReading);
        //        printf("\r\n Just saw center on black, LEDON was %d \r\n", CenterLEDOnReading);
        //        printf("\r\n Just saw center on black, LEDOFF was %d \r\n", CenterLEDOffReading);
    } else if (CenterLEDDiffReading > CENTER_LIGHT_HIGH_THRESHOLD && PrevMeasuredValues[1] == BLACK) {
        TapeValues[1] = WHITE;
        //        printf("\r\n Just saw center on white, diff was %d \r\n", CenterLEDDiffReading);
        //        printf("\r\n Just saw center on white, LEDON was %d \r\n", CenterLEDOnReading);
        //        printf("\r\n Just saw center on white, LEDOFF was %d \r\n", CenterLEDOffReading);
    }

    if (RightLEDDiffReading < CORNER_LIGHT_LOW_THRESHOLD && PrevMeasuredValues[2] == WHITE) {
        TapeValues[2] = BLACK;
        //        printf("\r\n Just saw RIGHT on black, diff was %d \r\n", RightLEDDiffReading);
        //        printf("\r\n Just saw RIGHT on black, LEDON was %d \r\n", RightLEDOnReading);
        //        printf("\r\n Just saw RIGHT on black, LEDOFF was %d \r\n", RightLEDOffReading);
    } else if (RightLEDDiffReading > CORNER_LIGHT_HIGH_THRESHOLD && PrevMeasuredValues[2] == BLACK) {
        TapeValues[2] = WHITE;
        //        printf("\r\n Just saw RIGHT on white, diff was %d \r\n", RightLEDDiffReading);
        //        printf("\r\n Just saw RIGHT on white, LEDON was %d \r\n", RightLEDOnReading);
        //        printf("\r\n Just saw RIGHT on white, LEDOFF was %d \r\n", RightLEDOffReading);
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

