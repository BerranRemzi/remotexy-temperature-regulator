#include "Tasks.h"
#include "Configuration.h"
#include "xOS.h"

typedef enum {
  STATE_STANDBY,
  STATE_BUSY,
  STATE_READY
} MainState_t;
bool regulatorStete = false;
MainState_t mainState = STATE_STANDBY;

uint8_t buttonMainSwitch = false;
uint8_t buttonPlus = false;
uint8_t buttonMinus = false;


static int16_t tempSetpoint = 0;
static int16_t tempMeasured = 0;

uint8_t ledBusy = 0;
uint8_t ledStandby = 0;
uint8_t ledReady = 0;

uint32_t timeHeatingSeconds = 0;
uint32_t timeProcessSeconds = 0;

Task_t TaskStruct[5];

void Task_Init(void) {
  xInit(TaskStruct);      //Struct with function parameters

  xTaskCreate(&Task_Button, 10);
  xTaskCreate(&Task_Timer, 1000);
  xTaskCreate(&Task_Regulator, 10);
  xTaskCreate(&Task_Dimmer, 10);
  xTaskCreate(&Task_Main, 10);

  pinMode(DIMMER_PIN, OUTPUT);
}
uint16_t pressCounter = 0;
void Task_Button(void) {
  if (pressCounter == 1 || pressCounter > 50) {
    if (buttonPlus) {
      if (tempSetpoint < 999) {
        tempSetpoint++;
      }
    }
    if (buttonMinus) {
      if (tempSetpoint > 0) {
        tempSetpoint--;
      }
    }
  }

  if (buttonPlus || buttonMinus) {
    pressCounter++;
  }
  if (!buttonPlus && !buttonMinus) {
    pressCounter = 0;
  }
}
void Task_Timer(void) {
  switch (mainState) {
    case STATE_BUSY:
      timeHeatingSeconds++;
      break;
    case STATE_READY:
      timeProcessSeconds++;
      break;
    default: break;
  }
}
void Task_Regulator(void) {

}
uint16_t Dimmer_counter = 0;
uint16_t Dimmer_value = 0;
void Task_Dimmer(void) {
  if (Dimmer_counter <= Dimmer_value) {
    digitalWrite(DIMMER_PIN, HIGH);
  } else {
    digitalWrite(DIMMER_PIN, LOW);
  }

  Dimmer_counter++;
  if (Dimmer_counter > 255) {
    Dimmer_counter = 0;
  }
}
void Task_Main(void) {
  switch (mainState) {
    case STATE_STANDBY:
      ledStandby = LED_ON;
      ledBusy = LED_OFF;
      ledReady = LED_OFF;
      if (buttonMainSwitch) {
        mainState = STATE_BUSY;
      }
      break;
    case STATE_BUSY:
      ledStandby = LED_OFF;
      ledBusy = LED_ON;
      ledReady = LED_OFF;
      //if(tempMeasured in range)
      //mainState = STATE_READY;
      break;
    case STATE_READY:
      ledStandby = LED_OFF;
      ledBusy = LED_OFF;
      ledReady = LED_ON;
      //if(tempMeasured not in range)
      //mainState = STATE_BUSY;
      break;
    default: break;
  }
  if (!buttonMainSwitch){
    mainState = STATE_STANDBY;
  }
}


void Core_Read_MainSwitch(uint8_t *_input) {
  buttonMainSwitch = *_input;
}
void Core_Read_ButtonPlus(uint8_t *_input) {
  buttonPlus = *_input;
}
void Core_Read_ButtonMinus(uint8_t *_input) {
  buttonMinus = *_input;
}

void Core_Update_BusyLed(uint8_t *_output) {
  *_output = ledBusy;
}
void Core_Update_StandbyLed(uint8_t *_output) {
  *_output = ledStandby;
}
void Core_Update_ReadyLed(uint8_t *_output) {
  *_output = ledReady;
}
void Core_Update_MeasuredTemperature(char _output[]) {
  sprintf(_output, "%d", tempMeasured);
}
float Core_Get_MeasuredTemperature(void) {
  return (float)tempMeasured;
}
void Core_Update_SetpointTemperature(char _output[]) {
  sprintf(_output, "%d", tempSetpoint);
}
float Core_Get_SetpointTemperature(void) {
  return (float)tempSetpoint;
}
void Core_Update_HeatingTime(char _output[]) {
  sprintf(_output, "%d", timeHeatingSeconds);
}
void Core_Update_ProcessTime(char _output[]) {
  sprintf(_output, "%d", timeProcessSeconds);
}

void Dimmer_Write(uint16_t _input) {
  Dimmer_value = _input;
}
