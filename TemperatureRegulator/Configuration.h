#pragma once

#define DIMMER_PIN LED_BUILTIN

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
#define TEMP_HYSTERESIS_C 6
#define TEMP_HALF_HYST (TEMP_HYSTERESIS_C/2)
/*
 * Temperature ready indicator
 */
#define TEMP_READY_HYSTERESIS 10

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
