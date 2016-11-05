/*
 * File:   AD.h
 * Author: mdunne
 *
 * Software module to enable the Analog to Digital converter of the Uno32 boards.
 * All analog pins are are Port V and Port W, with an additional analog input for
 * the battery voltage (through a 10:1 divider).
 *
 * NOTE: Analog pins automatically take over digital I/O regardless of which TRIS
 *       state it is in. There remains an error in the ADC code such that if all 12
 *       pins are enabled, one of them does not respond.
 *
 * AD_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * Make sure it is commented out for module useage.
 *
 * Created on November 22, 2011, 8:57 AM
 */


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define SHORT_DELAY 10000
#define MED_DELAY 100000
#define LONG_DELAY 1000000

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function myDelay
 * @param delayLength, sets the length of the delay in clock cycles
 * @return None
 * @brief  Extremely simple function to 'pause' the chip for testing purposes.
 * @author Daniel Hunter, 4 Nov 2016 */
void myDelay(int delayLength);



