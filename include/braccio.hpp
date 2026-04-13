/*
 * braccio.hpp
 * Description: [DESCRIBE PURPOSE HERE]
 * Note: .hpp files = Pure app-level C++ (no hardware concern)
 */

#ifndef BRACCIO_HPP
#define BRACCIO_HPP

/* -- Includes (STL, ESP-IDF, project) -------------------------------------- */
#include "robot.hpp"


/* -- Enums / Constants ----------------------------------------------------- */


/* -- Type definitions (structs, typedefs) ---------------------------------- */


/* -- Forward declarations (function prototypes) ---------------------------- */


/* -- Class declaration ----------------------------------------------------- */

class Braccio : public Robot {
public:
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
    static constexpr size_t NUM_JOINTS = 5; // No end effector control for now
    float joint_positions_[NUM_JOINTS]; // Current joint positions (radians or degrees depending on convention)

    /* -- Private helper methods -------------------------------------------- */
    RobotStatus_t InverseKinematics(const Pose_t& pose, JointState_t& solution);
    RobotStatus_t ForwardKinematics(const JointState_t& joints, Pose_t& pose);

    RobotStatus_t WriteServos(const JointState_t& joints);
};

/* -- Inline functions (if any) --------------------------------------------- */


#endif  // BRACCIO_HPP
