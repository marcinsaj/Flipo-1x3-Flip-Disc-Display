/*----------------------------------------------------------------------------------*
 * A simple example of controlling two 1x3 flip-disc displays                       *
 * Example connection diagram: https://bit.ly/2x1x3-ARD                             *
 *                                                                                  *
 * Project website: https://bit.ly/1x3-FD                                           *
 * Marcin Saj 30 Jan 2023                                                           *
 * https://www.Flipo.io                                                             *
 *                                                                                  *
 * Arduino board with a power module or dedicated controller is required to operate *
 * the displays:                                                                    *
 * 1. Arduino board + Pulse Shaper Power Supply - https://bit.ly/PSPS-FD            *
 * 2. Or dedicated controller - https://bit.ly/AC1-FD                               *
 *----------------------------------------------------------------------------------*/

/* The library <FlipDisc.h> uses SPI to control flip-disc displays. 
The user must remember to connect the display inputs marked: 
- DIN - data in - to the MOSI (SPI) output of the microcontroller, 
- CLK - clock - input of the display to the SCK (SPI).
The displays are connected in series through the built-in connectors, 
only the first display from the left is connected to the Arduino or a dedicated controller.
 
It is very important to connect and declare EN, CH, PL pins. 
The declaration of DIN (MOSI) and CLK (SCK) is not necessary, 
because the SPI.h library handles the SPI hardware pins. */

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc 

// Pin declaration for Arduino Uno and PSPS module
#define EN_PIN  10      // Start & End SPI transfer data
#define CH_PIN  8       // Charging PSPS module - turn ON/OFF
#define PL_PIN  9       // Release the current pulse - turn ON/OFF

/*
// Pin declaration for a dedicated controller
#define EN_PIN  A7
#define CH_PIN  A2 
#define PL_PIN  A3
*/

void setup() 
{
  /* FlipDisc.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
 
  FlipDisc.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* FlipDisc.Init(display1, display2, ... display8); it is the second most important function.
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function also prepares SPI. Correct initialization requires 
  code names of the serially connected displays:
  - SEG - 7-segment display
  - DOTS - 2x1 or 3x1 dot display
  - FLIP3 - 1x3 display
  - FLIP7 - 1x7 display 
  Example for four FLIP3 displays: FlipDisc.Init(FLIP3, FLIP3, FLIP3, FLIP3); */
 
  FlipDisc.Init(FLIP3, FLIP3);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  FlipDisc.Clear();
  delay(1000);
  
  /* The function is used to turn on (set) all discs of all displays */
  FlipDisc.All();
  delay(1000);

  FlipDisc.Clear();
  delay(1000);

  /* The function allows you to control up to three discs of the selected display. 
  FlipDisc.Flip3(moduleNumber, disc1,disc2,disc3);
  The first argument is the relative number "moduleNumber" of the display in the series 
  of all displays. For example, if we have a combination of FLIP3, SEG, FLIP3, 
  then the second FLIP3 display will have a relative number of 2 even though 
  there is a SEG display between the FLIP3 displays.
  - moduleNumber - relative number of the FLIP3 display
  - disc1, disc2, disc3 - counting from left to right 1-3 */
  
  FlipDisc.Flip3(1,1,1,1);    /* Set all discs of the first display counting from the left to right */
  delay(1000);

  FlipDisc.Flip3(2,1);        /* Set the first disc of the second display */
  delay(1000);

  FlipDisc.Flip3(2,0,1);      /* Reset the first disc and set the second disc of the second display */
  delay(1000);

  FlipDisc.Flip3(1,0,0,0);    /* Reset all discs of the second display */
  delay(3000);

  FlipDisc.All();
  delay(1000);

  /* Function allows you to control a selected disc in a selected FLIP3 display.
  You can control only one disc of the selected display at a time.
  FlipDisc.ToFlip3(moduleNumber, discNumber, discStatus);
  The first argument moduleNumber is the relative number of the display 
  in the series of all displays. For example, if we have a combination of 
  FLIP3, SEG, FLIP3, then the second FLIP3 display will have a relative number of 2 
  even though there is a SEG display between the FLIP3 displays.
  - moduleNumber - relative number of the FLIP3 display
  - discNumber - display disc number counting from left to right 1-3
  - discStatus - reset disc "0" or set disc "1" */
  
  /* Reset selected dots of the first FLIPO3 display counting from the left */
  FlipDisc.ToFlip3(1, 1, 0);
  delay(1000);
  FlipDisc.ToFlip3(1, 2, 0);
  delay(1000);
  FlipDisc.ToFlip3(1, 3, 0);
  delay(1000);

  /* Reset selected dots of the second FLIPO3 display counting from the left */
  FlipDisc.ToFlip3(2, 1, 0);
  delay(1000);
  FlipDisc.ToFlip3(2, 2, 0);
  delay(1000);
  FlipDisc.ToFlip3(2, 3, 0);
  delay(3000);
  
  /* Set selected dots */
  FlipDisc.ToFlip3(1, 2, 1);
  FlipDisc.ToFlip3(2, 2, 1);
  delay(3000);
  
  FlipDisc.Clear();
  delay(1000);
}
