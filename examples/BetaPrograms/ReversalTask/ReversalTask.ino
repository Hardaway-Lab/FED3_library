/*
  Feeding experimentation device 3 (FED3)
  FR1 reversal task
  Code by: alexxai@wustl.edu and meaghan.creed@wustl.edu
  December, 2020

  Starts with the left poke resulting in a pellet and the right poke not resulting in a pellet

  After a defined number of *pokes* the probabilities on the right and left pokes switch.  This is set
  by the variable "trialsToSwitch".  Code below can be edited to make this switch after set number of *pellets*

  This project is released under the terms of the Creative Commons - Attribution - ShareAlike 3.0 license:
  human readable: https://creativecommons.org/licenses/by-sa/3.0/
  legal wording: https://creativecommons.org/licenses/by-sa/3.0/legalcode
  Copyright (c) 2020 Lex Kravitz
*/

#include <FED3.h>                                       //Include the FED3 library 
String sketch = "RevTask";                              //Unique identifier text for each sketch, change string only
FED3 fed3 (sketch);                                     //Start the FED3 object - don't change

int trialsToSwitch = 10;
int counter = 0;

void setup() {
  fed3.begin();                                         //Setup the FED3 hardware, all pinmode screen etc, initialize SD card
}

void loop() {
  fed3.run();                                           //Call fed.run at least once per loop

  //Determine which poke is active based on the trial number
  if (counter == (trialsToSwitch * 2) - 1) counter = 0;
  if (counter < trialsToSwitch) fed3.activePoke = 1;
  if (counter >= trialsToSwitch) fed3.activePoke = 0;

  ////////////////////////////////////////////////
  // There are 4 cases we need to account for:
  ////////////////////////////////////////////////

  // Case 1: The *left* poke is active and animal pokes *left*
  if (fed3.activePoke == 1 and fed3.Left) {
    fed3.logLeftPoke();                                 //Log left poke
    fed3.ConditionedStimulus();                         //Deliver conditioned stimulus (tone and lights)
    fed3.Feed();                                        //Deliver pellet
    counter ++;
  }

  // Case 2: The *left* poke is active and animal pokes *right*
  if (fed3.activePoke == 1 and fed3.Right) {
    fed3.logRightPoke();                                 //Log left poke
    fed3.Click();
    counter ++;
  }

  // Case 3: The *right* poke is active and animal pokes *left*
  if (fed3.activePoke == 0 and fed3.Left) {
    fed3.logLeftPoke();                                //Log right poke
    fed3.Click();
    counter ++;
  }

  // Case 4: The *right* poke is active and animal pokes *right*
  if (fed3.activePoke == 0 and fed3.Right) {
    fed3.logRightPoke();                                //Log right poke
    fed3.ConditionedStimulus();                         //Deliver conditioned stimulus (tone and lights)
    fed3.Feed();                                        //Deliver pellet
    counter ++;
  }
}