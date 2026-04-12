/*
 * robot.hpp
 * Description: [DESCRIBE PURPOSE HERE]
 * Note: .hpp files = Pure app-level C++ (no hardware concern)
 */

#ifndef ROBOT_HPP
#define ROBOT_HPP

/* -- Includes (STL, ESP-IDF, project) -------------------------------------- */
#include <cstddef>
#include "error_codes.h"

/* -- Enums / Constants ----------------------------------------------------- */
enum class RobotState {
    UNINITIALIZED,
    IDLE,
    MOVING,
    ERROR,
    DISABLED
};

/* -- Type definitions (structs, typedefs) ---------------------------------- */
typedef struct
{
    float x;
    float y;
    float z;
    float roll;
    float pitch;
    float yaw;
} Pose_t;

typedef struct {
    float* positions;
    size_t size;
} JointState_t;

typedef StatusCode_t RobotStatus_t;
/* -- Forward declarations (function prototypes) ---------------------------- */


/* -- Class declaration ----------------------------------------------------- */

class Robot {
public:
    /* -- Public Constructors / Destructors --------------------------------- */
    Robot() = default; 
    virtual ~Robot() = default;

    virtual RobotStatus_t Init() = 0;
    virtual RobotStatus_t Enable() = 0;
    virtual RobotStatus_t Disable() = 0;
    virtual RobotStatus_t Stop() = 0;

    virtual RobotStatus_t Home() = 0;

    virtual RobotStatus_t GotoPose(const Pose_t& target_pose) = 0;
    virtual RobotStatus_t GotoJointPositions(const JointState_t& target_joints) = 0;

    RobotState GetState() const { return state_; };

protected:
    void SetState(RobotState new_state) { state_ = new_state; }

private:
    RobotState state_ = RobotState::UNINITIALIZED; 

};

/* -- Inline functions (if any) --------------------------------------------- */


#endif  // ROBOT_HPP
