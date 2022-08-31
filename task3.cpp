#include <Arduino.h>
#include "task3.h"
#include "events.h"

static bool compareKeys(BUTTONS *pSecret, BUTTONS *pKey)
{
    bool correct = true;
    for (uint8_t i = 0; i < 5; i++)
    {
        if (pSecret[i] != pKey[i])
        {
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
        OFF,
        ON,
        Lento,
        Media,
        Rapida,
        WaitLento,
        WaitMedio,

    };
    static TaskStates taskState = TaskStates::INIT;
    const uint8_t ledMode = 25;
    static uint32_t lasTime;
    static constexpr uint32_t intervalLENTO = 1000;
    static constexpr uint32_t intervalMEDIO = 500;
    static constexpr uint32_t intervalRAPIDO = 125;

    static BUTTONS SecretCodigoRapido[5] = {BUTTONS::ONE_BTN, BUTTONS::ONE_BTN,
                                            BUTTONS::TWO_BTN, BUTTONS::TWO_BTN,
                                            BUTTONS::ONE_BTN};

    static BUTTONS RapidoKey[5] = {BUTTONS::NONE};

    static bool ledState = false;
    static bool lastStateON = false;
    
    static uint8_t key = 0;

    switch (taskState)
    {
    case TaskStates::INIT:
    {
        pinMode(ledMode, OUTPUT);
        digitalWrite(ledMode, HIGH);

        taskState = TaskStates::Lento;

        break;
    }
    case TaskStates::Lento:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= intervalLENTO)
        {
            lasTime = currentTime;
            digitalWrite(ledMode, ledState);
            ledState = !ledState;
            if (buttonEvt.trigger == true)
            {
                buttonEvt.trigger = false;
                if (buttonEvt.whichButton == BUTTONS::ONE_BTN)
                {
                    ledState = false;
                    digitalWrite(ledMode, ledState);
                    taskState = TaskStates::WaitLento;
                }
                else if (buttonEvt.whichButton == BUTTONS::TWO_BTN)
                {

                    taskState = TaskStates::Media;
                }
            }
        }
        break;
    }

    case TaskStates::Media:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= intervalMEDIO)
        {

            lasTime = currentTime;
            digitalWrite(ledMode, ledState);
            ledState = !ledState;
            if (buttonEvt.trigger == true)
            {
                buttonEvt.trigger = false;
                if (buttonEvt.whichButton == BUTTONS::ONE_BTN)
                {
                    ledState = true;
                    digitalWrite(ledMode, ledState);
                    taskState = TaskStates::WaitMedio;
                }
                else if (buttonEvt.whichButton == BUTTONS::TWO_BTN)
                {
                    taskState = TaskStates::Lento;
                }
            }
        }
        break;
    }

    case TaskStates::Rapida:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= intervalRAPIDO)
        {

            lasTime = currentTime;
            digitalWrite(ledMode, ledState);
            ledState = !ledState;
        }

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            RapidoKey[key] = buttonEvt.whichButton;
            key++;

            if (key == 5)
            {
                key = 0;
                if (compareKeys(SecretCodigoRapido, RapidoKey) == true)
                {
                    if (lastStateON == true)
                    {
                        ledState = true;
                        digitalWrite(ledMode, ledState);
                        
                        taskState = TaskStates::Media;
                    }
                    else if (lastStateON == false)
                    {
                        digitalWrite(ledMode, ledState);

                        ledState = false;
                        taskState = TaskStates::Lento;
                    }
                    


                    
                }
               
            }
        }

        break;
    }

    case TaskStates::OFF:
    {

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            digitalWrite(ledMode, LOW);
            if (buttonEvt.whichButton == BUTTONS::ONE_BTN)
            {
                ledState = true;
                pinMode(ledMode, OUTPUT);
                digitalWrite(ledMode, LOW);
                digitalWrite(ledMode, ledState);
                taskState = TaskStates::Lento;
            }
            else if (buttonEvt.whichButton == BUTTONS::TWO_BTN)
            {
                taskState = TaskStates::Rapida;
                
                lastStateON = false;
            }
        }
        break;
    }

    case TaskStates::ON:
    {

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            if (buttonEvt.whichButton == BUTTONS::ONE_BTN)
            {
                taskState = TaskStates::Media;
            }
            else if (buttonEvt.whichButton == BUTTONS::TWO_BTN)
            {
                taskState = TaskStates::Rapida;
                lastStateON = true;
                
            }
        }
        break;
        case TaskStates::WaitLento:
        {
           uint32_t currentTime = millis();
          if ((currentTime - lasTime) >= intervalLENTO)
          {
           taskState = TaskStates::OFF;
          }
          break;
        }
         case TaskStates::WaitMedio:
        {
           uint32_t currentTime = millis();
          if ((currentTime - lasTime) >= intervalMEDIO)
          {
           taskState = TaskStates::ON;
          }
          break;
        }
    }

    default:
    {
        break;
    }
    }
}