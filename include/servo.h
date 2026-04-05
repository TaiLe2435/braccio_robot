/*
 * servo.h
 * Description: HAL driver for controlling servo motors via transistor level shifter
 */

#ifndef SERVO_H
#define SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes -------------------------------------------------------------- */
#include "driver/ledc.h"
#include "driver/gpio.h"

/* -- Constants ------------------------------------------------------------- */
// Single servo test configuration
#define SERVO_PIN GPIO_NUM_25
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0

// Signal inversion for NPN transistor level shifter
#define USE_INVERTED_SIGNAL 1

/* -- Type definitions ------------------------------------------------------ */
typedef enum 
{
    SERVO_1 = 1,
    SERVO_2,
    SERVO_3,
    SERVO_4,
    SERVO_5,
    SERVO_6,
    NUM_SERVOS
} ServoNumber_t;

/* -- Function prototypes --------------------------------------------------- */
void servo_init(void);
void servo_set_angle(float angle);

/* -- C++ Class ------------------------------------------------------------- */
#ifdef __cplusplus
class Servo {
public:
    Servo();
    ~Servo();
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // SERVO_H