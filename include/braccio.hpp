/*
 * braccio.hpp
 * Description: [DESCRIBE PURPOSE HERE]
 * Note: .hpp files = Pure app-level C++ (no hardware concern)
 */

#ifndef BRACCIO_HPP
#define BRACCIO_HPP

/* -- Includes (STL, ESP-IDF, project) -------------------------------------- */
#include <array>
#include <memory>
#include "robot.hpp"
#include "error_codes.h"
#include "servo.h"

/* -- Enums / Constants ----------------------------------------------------- */
#define NUM_JOINTS 5 // No end effector control for now

/* -- Type definitions (structs, typedefs) ---------------------------------- */
typedef enum
{
    J1 = 0,
    J2,
    J3,
    J4,
    J5
} JointIndex_t;

// this isn't created in base robot class as DOF != number of axes
typedef struct 
{
    std::array<std::unique_ptr<Servo>, NUM_JOINTS> axis_;
} JointGroup_t;

/* -- Forward declarations (function prototypes) ---------------------------- */


/* -- Class declaration ----------------------------------------------------- */

class Braccio : public Robot<5> {
public:
    using JointState_t = typename Robot<5>::JointState_t;

    /* -- Public Constructors / Destructors --------------------------------- */
    Braccio();
    ~Braccio();

    /* -- Public initialization methods ------------------------------------- */
    RobotStatus_t Init() override;
    RobotStatus_t Enable() override;
    RobotStatus_t Disable() override;

    /* -- Public control/action methods ------------------------------------- */
    RobotStatus_t Stop() override;
    RobotStatus_t Home() override;
    RobotStatus_t GotoPose(const Pose_t& target_pose) override;
    RobotStatus_t GotoJointPositions(const JointState_t& target_joints) override;

    /* -- Public getters ---------------------------------------------------- */

    /* -- Public setters ---------------------------------------------------- */


private:
    /* -- Private member variables ------------------------------------------ */
    JointState_t JointState_; // Current joint positions (angles in degrees)

    JointGroup_t JointGroup_; // Grouping of servo objects for easier control

    /* -- Private helper methods -------------------------------------------- */
    RobotStatus_t InverseKinematics(const Pose_t& pose, JointState_t& solution);
    RobotStatus_t ForwardKinematics(const JointState_t& joints, Pose_t& pose);

    RobotStatus_t WriteServos(const JointState_t& joints);
};

/* -- Inline functions (if any) --------------------------------------------- */


#endif  // BRACCIO_HPP
