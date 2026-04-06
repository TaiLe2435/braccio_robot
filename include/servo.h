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
#include "error_codes.h"

/* -- Constants ------------------------------------------------------------- */
// J1 servo pin and LEDC configuration
#define J1_PIN GPIO_NUM_27
#define J1_LEDC_CHANNEL LEDC_CHANNEL_0
#define J1_LEDC_TIMER LEDC_TIMER_0

// J2 servo pin and LEDC configuration
#define J2_PIN GPIO_NUM_26
#define J2_LEDC_CHANNEL LEDC_CHANNEL_1
#define J2_LEDC_TIMER LEDC_TIMER_1

// J3 servo pin and LEDC configuration
#define J3_PIN GPIO_NUM_25
#define J3_LEDC_CHANNEL LEDC_CHANNEL_2
#define J3_LEDC_TIMER LEDC_TIMER_2

// J4 servo pin and LEDC configuration
#define J4_PIN GPIO_NUM_33
#define J4_LEDC_CHANNEL LEDC_CHANNEL_3
#define J4_LEDC_TIMER LEDC_TIMER_3

// J5 servo pin and LEDC configuration
#define J5_PIN GPIO_NUM_32
#define J5_LEDC_CHANNEL LEDC_CHANNEL_4
#define J5_LEDC_TIMER LEDC_TIMER_0 // this might cause conflicts, but we only have 4 timers so we have to reuse

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
    NUM_SERVOS
} ServoNumber_t;

typedef struct 
{
    ServoNumber_t ServoNumber;
    gpio_num_t Pin;
    ledc_channel_t Channel;
    ledc_timer_t Timer;
} ServoDriver_t;

typedef StatusCode_t ServoStatus_t;

/* -- Function prototypes --------------------------------------------------- */

/* -- C++ Class ------------------------------------------------------------- */
#ifdef __cplusplus
class Servo {
public:
    ServoDriver_t ServoDriver;  // Driver configuration for this servo

    Servo(ServoDriver_t driver);
    ~Servo();

    ServoStatus_t Init();
    ServoStatus_t Enable();
    ServoStatus_t Disable();
    ServoStatus_t EnableAll();
    ServoStatus_t DisableAll();
    ServoStatus_t SetAngle(float angle);
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // SERVO_H