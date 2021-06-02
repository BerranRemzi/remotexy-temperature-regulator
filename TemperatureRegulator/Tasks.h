#pragma once
#include "Arduino.h"

void Task_Button(void);
void Task_Timer(void);
void Task_Regulator(void);
void Task_Dimmer(void);
void Task_Main(void);
void Task_Init(void);

void Core_Read_MainSwitch(uint8_t *_input);
void Core_Read_ButtonPlus(uint8_t *_input);
void Core_Read_ButtonMinus(uint8_t *_input);

void Core_Update_BusyLed(uint8_t *_output);
void Core_Update_StandbyLed(uint8_t *_output);
void Core_Update_ReadyLed(uint8_t *_output);
float Core_Get_MeasuredTemperature(void);
void Core_Update_MeasuredTemperature(char _output[]);
void Core_Update_SetpointTemperature(char _output[]);
float Core_Get_SetpointTemperature(void);
void Core_Update_HeatingTime(char _output[]);
void Core_Update_ProcessTime(char _output[]);

void Dimmer_Write(uint16_t _input);
