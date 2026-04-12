/*
 * error_codes.h
 * Description: Definition of error codes for the application
 */

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

/* -- Error Codes ----------------------------------------------------------- */
typedef enum {
    STATUS_OK = 0,
    ERR_INVALID_ARGUMENT,
    ERR_OPERATION_NOT_PERMITTED,
    ERR_RESOURCE_UNAVAILABLE,
    ERR_TIMEOUT,

    // Robot Errors
    ERR_ROBOT_UNINITIALIZED,
    ERR_IK_FAILED,
    ERR_JOINT_LIMITS_EXCEEDED,
    ERR_OUT_OF_RANGE,
    ERR_HARDWARE_FAILURE,
    ERR_BUSY,
    ERR_UNKNOWN
} StatusCode_t;

#ifdef __cplusplus // if file is being compiled as C++
extern "C" { // enable C-style linkage
#endif // prevents name mangling when included in C code

/* -- Includes (STL, ESP-IDF, project) -------------------------------------- */


/* -- Enums / Constants ----------------------------------------------------- */


/* -- Type definitions (structs, typedefs) ---------------------------------- */


/* -- Forward declarations (function prototypes) ---------------------------- */


/* -- Class declaration (C++ only) ------------------------------------------ */


/* -- C-compatible functions (extern "C" if needed) ------------------------- */


#ifdef __cplusplus
}
#endif

#endif  // ERROR_CODES_H
