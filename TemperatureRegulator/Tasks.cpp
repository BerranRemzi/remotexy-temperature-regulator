#include "Tasks.h"
#include "Configuration.h"
#include "xOS.h"
#include <SPI.h>
#include "max6675.h"

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

uint16_t Dimmer_counter = 0;
uint16_t Dimmer_value = 0;

MAX6675 Sensor(SENSOR_CLK_PIN, SENSOR_CS_PIN, SENSOR_DO_PIN);
Task_t TaskStruct[5];

void Task_Init(void) {
  xInit(TaskStruct);      //Struct with function parameters

  xTaskCreate(&Task_Button, 10);
  xTaskCreate(&Task_Timer, 1000);
  xTaskCreate(&Task_Regulator, 500);
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
  tempMeasured = round(Sensor.readCelsius());
#ifdef REGULATOR_TYPE_HYST
  Dimmer_value = Regulator_Hyst_GetResult(tempSetpoint, tempMeasured);
#else
  Dimmer_value = Regulator_PID_GetResult(tempSetpoint, tempMeasured);
#endif
}


void Task_Dimmer(void) {
  if ((Dimmer_counter <= Dimmer_value) && (true == buttonMainSwitch)) {
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


  if (false == buttonMainSwitch) {
    mainState = STATE_STANDBY;
  }

  switch (mainState) {
    case STATE_STANDBY:
      if (buttonMainSwitch) {
        mainState = STATE_BUSY;
      }
      break;
    case STATE_BUSY:
      if (true == Core_IsTemperatureInRange()) {
        mainState = STATE_READY;
      }
      break;
    case STATE_READY:
      if (false == Core_IsTemperatureInRange()) {
        mainState = STATE_BUSY;
      }
      break;
    default: break;
  }

  Core_UpdateLeds();
}

int16_t Regulator_Hyst_GetResult(int16_t _tempSetpoint, int16_t _tempMeasured) {
  int16_t returnValue = 0;
  if (_tempMeasured < (_tempSetpoint - TEMP_REG_HALF_HYST)) {
    returnValue = DIMMER_MAX;
  } else if (_tempMeasured > (_tempSetpoint + TEMP_REG_HALF_HYST)) {
    returnValue = DIMMER_MIN;
  }
  return (returnValue);
}
int16_t Regulator_PID_GetResult(int16_t _tempSetpoint, int16_t _tempMeasured) {
  double _Kp = KP;
  double _Ki = KI;
  double _dT = DT;
  double _error = _tempSetpoint - _tempMeasured;
  static double _integral = 0;
  static double _previousError = 0;
  _integral += (_error + _previousError) / 2 * _dT / 1000.0;   //Riemann sum integral
  _previousError = _error;
  double PID = (_Kp * _error) + (_Ki * _integral);
  int16_t returnValue = (int16_t)PID;
  
  constrain(returnValue, DIMMER_MIN, DIMMER_MAX)
  return (returnValue);
}
bool Core_IsTemperatureInRange(void) {
  bool measuredTempInRange = false;
  if ((tempMeasured > (tempSetpoint - TEMP_READY_HALF_HYST))
      && (tempMeasured < (tempSetpoint + TEMP_READY_HALF_HYST))) {
    measuredTempInRange = true;
  }
  return (measuredTempInRange);
}
void Core_UpdateLeds(void) {
  ledStandby = LED_OFF;
  ledBusy = LED_OFF;
  ledReady = LED_OFF;

  switch (mainState) {
    case STATE_STANDBY:
      ledStandby = LED_ON;
      break;
    case STATE_BUSY:
      ledBusy = LED_ON;
      break;
    case STATE_READY:
      ledReady = LED_ON;
      break;
    default: break;
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
