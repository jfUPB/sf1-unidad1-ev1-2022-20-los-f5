#include <Arduino.h>
#include "task3.h"
#include "events.h"

/*static bool compareKeys(BUTTONS *pSecret, BUTTONS *pKey)
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
}*/

void task3()
{

    enum class TaskStates
    {
        INIT,
        WAIT_CONFIG,
        COUNTING
    };
    static TaskStates taskState = TaskStates::INIT;
    const uint8_t ledMode = 26;
   // const uint32_t intervalRAPIDO = 250U;
    const uint32_t intervalLENTO = 1000;
    const uint32_t intervalMEDIO = 500U;
    static uint8_t conter = 0;


    
   /*static BUTTONS secret[5] = {BUTTONS::ONE_BTN, BUTTONS::ONE_BTN,
                                BUTTONS::TWO_BTN, BUTTONS::TWO_BTN,
                                BUTTONS::ONE_BTN};

    static BUTTONS returnMode[5] = {BUTTONS::NONE};*/


    
    
   // static uint8_t keyCounter;

    switch (taskState)
    {
    case TaskStates::INIT:
    {
        pinMode(ledMode, OUTPUT);
        digitalWrite(ledMode,HIGH);
  
           if (buttonEvt.trigger == true)
    {
            buttonEvt.trigger = false;
            
         if(buttonEvt.whichButton==BUTTONS::ONE_BTN)
            {
                digitalWrite(ledMode,HIGH);
                delay(intervalLENTO); 
                digitalWrite(ledMode,LOW);
                delay(intervalLENTO);

                if(buttonEvt.whichButton==BUTTONS::ONE_BTN)
                {
                    digitalWrite(ledMode,LOW);
                    delay(2000);
                }
               
               
            }
        if (buttonEvt.whichButton==BUTTONS::TWO_BTN)
        {
               taskState = TaskStates::WAIT_CONFIG;
        }
            
        
        
       
        
    }
      break;
    }
    case TaskStates::WAIT_CONFIG:
     {
        pinMode(ledMode, OUTPUT);
        digitalWrite(ledMode,HIGH);
        delay(intervalMEDIO); 
        if (buttonEvt.trigger == true)
        {
            if(conter==0)
           {
            digitalWrite(ledMode,HIGH);
            delay(intervalMEDIO);
            digitalWrite(ledMode,LOW);
            delay(intervalMEDIO);

            if(buttonEvt.whichButton==BUTTONS::ONE_BTN){
               
                conter++;
            } 
            else if(conter==1)
          {
            digitalWrite(ledMode,HIGH);
            delay(intervalMEDIO);
            conter --;
          }

          }
        
       if(buttonEvt.whichButton==BUTTONS::TWO_BTN)
        {
           taskState = TaskStates::INIT;
                              
        }
        
        break;
    }

       
       
        
    default:
    {
        break;
    }
    } 
    
}
