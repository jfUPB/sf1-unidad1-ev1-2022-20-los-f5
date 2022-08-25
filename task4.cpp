#include <Arduino.h>
#include "task4.h"


void task4(){


 /*if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            if (buttonEvt.whichButton == BUTTONS::UP_BTN)
            {
                if (bombCounter < 60)
                    bombCounter++;
            }
            else if (buttonEvt.whichButton == BUTTONS::DOWN_BTN)
            {
                if (bombCounter > 10)
                    bombCounter--;
            }
            else if (buttonEvt.whichButton == BUTTONS::ARM_BTN)
            {
                initLedCounterTimer = millis();
                initBombTimer = millis();
                keyCounter = 0;
                taskState = TaskStates::COUNTING;
            }
       
        }*/

       // break;
  //  }
    /*case TaskStates::COUNTING:
    {

        uint32_t timeNow = millis();

        if ((timeNow - initBombTimer) > BOMBINTERVAL)
        {
            initBombTimer = timeNow;
            bombCounter--;
     
            if (bombCounter == 0)
            {
                ledBombCountingState = HIGH;
              
               
                delay(2000);
              
                bombCounter = 20;
                taskState = TaskStates::WAIT_CONFIG;
            }
        }
        if ((timeNow - initLedCounterTimer) > LEDCOUNTERINTERVAL)
        {
            initLedCounterTimer = timeNow;
            ledBombCountingState = !ledBombCountingState;
            
        }

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            returnMode[keyCounter] = buttonEvt.whichButton;
            keyCounter++;
            if (keyCounter == 5)
            {
                keyCounter = 0;
                if (compareKeys(secret, returnMode) == true)
                {
                    ledBombCountingState = HIGH;
                   
                    bombCounter = 20;
                    taskState = TaskStates::WAIT_CONFIG;
                }
            }
        }*/

    
}
