#pragma once

#define DIMMER_PIN LED_BUILTIN

#define SENSOR_DO_PIN   14
#define SENSOR_CS_PIN   10
#define SENSOR_CLK_PIN  15
/*
 * PI controller parameters
 */
#define PID_TASK_MS 500
#define KP 5
#define KI 1

/*
 * Regulator hysteresis
 * ex. 10 mean +/-5 C
 */
#define TEMP_REG_HYST_C 6
#define TEMP_REG_HALF_HYST (TEMP_REG_HYST_C/2)
/*
 * Temperature ready indicator
 */
#define TEMP_READY_INDICAOTR_HYST_C 10
#define TEMP_READY_HALF_HYST (TEMP_READY_INDICAOTR_HYST_C/2)

/*
 * Type of temperature regulating algorithm
 * REGULATOR_TYPE_PI
 * REGULATOR_TYPE_HYST
 */
#define REGULATOR_TYPE_HYST

/*
 * Time counting
 * TIME_SECONDS
 * TIME_MINS
 */
#define TIME_SECONDS

/*
 * Size of char arrays
 */
#define USED_CHAR_SIZE 5

#define LED_ON 255
#define LED_OFF 0

#define DIMMER_MAX 255
#define DIMMER_MIN 0
