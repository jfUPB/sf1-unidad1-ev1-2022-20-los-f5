#include <Arduino.h>
#include "task3.h"
#include "events.h"

static bool compareKeys(BUTTONS *pSecret, BUTTONS *pKey)
{
    bool correct = true;
    for (uint8_t i = 0; i < 5; i++)
    {
        if (pSecret[i] != pKey[i]){
            correct = false;
            break;
        }
    }

    return correct;
}

void task3()
{

    enum class TaskStates
    {
        INIT,
        WAIT_CONFIG,
        COUNTING
    };
    static TaskStates taskState = TaskStates::INIT;
    static constexpr uint8_t ledMode = 26;
    const uint32_t intervalRAPIDO = 250U;
    const uint32_t intervalLENTO = 1000;
    const uint32_t intervalMEDIO = 500U;
    static uint8_t conter = 0;
   

    
    static BUTTONS secret[5] = {BUTTONS::ONE_BTN, BUTTONS::ONE_BTN,
                                BUTTONS::TWO_BTN, BUTTONS::TWO_BTN,
                                BUTTONS::ONE_BTN};

    static BUTTONS returnMode[5] = {BUTTONS::NONE};

    static uint8_t ledModeState;
    static uint32_t initBombTimer;
    static uint32_t initLedCounterTimer;
    static uint8_t keyCounter;

    switch (taskState)
    {
    case TaskStates::INIT:
    {
        digitalWrite(ledMode,HIGH);
        delay(500); // es un delay solo para inicial al entrar en un modo, verdad?
        if(conter==0)
        {
            digitalWrite(ledMode,HIGH);
            delay(intervalLENTO);
            digitalWrite(ledMode,LOW);
            delay(intervalLENTO);

            if(buttonEvt.whichButton==BUTTONS::ONE_BTN){
               
                conter++;
            }

        }
        else if(conter==1)
        {
            digitalWrite(ledMode,LOW);
            delay(intervalLENTO);
            conter --;
        }
       if(buttonEvt.whichButton==BUTTONS::TWO_BTN)
        {
           taskState = TaskStates::WAIT_CONFIG;
                              
        }
        
        break;
    }
    case TaskStates::WAIT_CONFIG:
     {
        digitalWrite(ledMode,HIGH);
        delay(500); // es un delay solo para inicial al entrar en un modo, verdad?
        if(conter==0)
        {
            digitalWrite(ledMode,HIGH);
            delay(intervalMEDIO);
            digitalWrite(ledMode,LOW);
            delay(intervalMEDIO);

            if(buttonEvt.whichButton==BUTTONS::ONE_BTN){
               
                conter++;
            }

        }
        else if(conter==1)
        {
            digitalWrite(ledMode,HIGH);
            delay(intervalMEDIO);
            conter --;
        }
       if(buttonEvt.whichButton==BUTTONS::TWO_BTN)
        {
           taskState = TaskStates::INIT;
                              
        }
        
        break;
    }

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

        break;
    }
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
        }

        break;
    }*/

}
 
  
  default:
    {
        break;
    }
    }
}
