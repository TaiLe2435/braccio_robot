/*
 * servo.h
 * Description: HAL driver for controlling a servo motor
 */

#ifndef SERVO_H
#define SERVO_H

#ifdef __cplusplus // if file is being compiled as C++
extern "C" { // enable C-style linkage
#endif // prevents name mangling when included in C code

/* -- Includes (STL, ESP-IDF, project) -------------------------------------- */


/* -- Constants ----------------------------------------------------- */


/* -- Type definitions (structs, typedefs) ---------------------------------- */
typedef enum 
{
    SERVO_1 = 1,
    SERVO_2,
    SERVO_3,
    SERVO_4,
    SERVO_5,
    NUM_SERVOS
} ServoNumber_t;


/* -- Forward declarations (function prototypes) ---------------------------- */


/* -- Class declaration (C++ only) ------------------------------------------ */

#ifdef __cplusplus // if compiling as C++, include class definitions
class Servo { // c compiler preprocessor will ignore this entire block
public:
    GpioPin_t GpioPin;

    /* -- Public Constructors / Destructors --------------------------------- */
    Servo();

    ~Servo();

    /* -- Public initialization methods ------------------------------------- */


    /* -- Public control/action methods ------------------------------------- */


    /* -- Public getters ---------------------------------------------------- */


    /* -- Public setters ---------------------------------------------------- */


private:
    /* -- Private member variables ------------------------------------------ */


    /* -- Private helper methods -------------------------------------------- */

};
#endif  /* __cplusplus */

/* -- C-compatible functions (extern "C" if needed) ------------------------- */


#ifdef __cplusplus
}
#endif

#endif  // SERVO_H
