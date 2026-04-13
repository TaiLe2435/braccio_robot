/*
 * braccio.cpp
 * Description: [DESCRIBE PURPOSE HERE]
 */

/* -- Includes (always include own header first) ----------------------------- */
#include "braccio.hpp"
#include "esp_log.h"
/* add other project headers below */
#include "servo.h"

/* -- Local constants / macros ---------------------------------------------- */
static const char *TAG = "BRACCIO";


/* -- Local type definitions (structs, enums) ------------------------------- */
static ServoDriver_t ServoDriver_J1 = 
{
    .ServoNumber = SERVO_1,
    .Pin = J1_PIN,
    .Channel = J1_LEDC_CHANNEL,
    .Timer = J1_LEDC_TIMER
};
static ServoDriver_t ServoDriver_J2 = 
{
    .ServoNumber = SERVO_2,
    .Pin = J2_PIN,
    .Channel = J2_LEDC_CHANNEL,
    .Timer = J2_LEDC_TIMER
};
static ServoDriver_t ServoDriver_J3 = 
{
    .ServoNumber = SERVO_3,
    .Pin = J3_PIN,
    .Channel = J3_LEDC_CHANNEL,
    .Timer = J3_LEDC_TIMER
};
static ServoDriver_t ServoDriver_J4 = 
{
    .ServoNumber = SERVO_4,
    .Pin = J4_PIN,
    .Channel = J4_LEDC_CHANNEL,
    .Timer = J4_LEDC_TIMER
};
static ServoDriver_t ServoDriver_J5 = 
{
    .ServoNumber = SERVO_5,
    .Pin = J5_PIN,
    .Channel = J5_LEDC_CHANNEL,
    .Timer = J5_LEDC_TIMER
};

/* -- Static module variables (translation unit scope) ---------------------- */


/* -- Constructor / Destructor ---------------------------------------------- */
Braccio::Braccio() 
{
    // Constructor
    SetState(RobotState::UNINITIALIZED);
}

Braccio::~Braccio() 
{
    // Destructor
}

/* -- Public initialization methods ----------------------------------------- */
RobotStatus_t Braccio::Init()
{
    RobotStatus_t ReturnValue = STATUS_OK;

    // Create servo objects and initialize them
    ESP_LOGI(TAG, "Initializing Braccio robot with %d joints", NUM_JOINTS);
    JointGroup_.axis_[0] = std::make_unique<Servo>(ServoDriver_J1);
    JointGroup_.axis_[1] = std::make_unique<Servo>(ServoDriver_J2);
    JointGroup_.axis_[2] = std::make_unique<Servo>(ServoDriver_J3);
    JointGroup_.axis_[3] = std::make_unique<Servo>(ServoDriver_J4);
    JointGroup_.axis_[4] = std::make_unique<Servo>(ServoDriver_J5);


    for (size_t i = 0; i < NUM_JOINTS; i++) 
    {
        ReturnValue = (RobotStatus_t)JointGroup_.axis_[i]->Init();
        if (ReturnValue != STATUS_OK) 
        {
            ESP_LOGE(TAG, "Failed to initialize Axis %d", i + 1);
            SetState(RobotState::ERROR);
            break;
        }
        else
        {
            ESP_LOGI(TAG, "Axis %d initialized successfully", i + 1);
            SetState(RobotState::IDLE);
        }
    }

    return ReturnValue;
}

RobotStatus_t Braccio::Enable()
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

RobotStatus_t Braccio::Disable()
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

/* -- Public control / action methods --------------------------------------- */
RobotStatus_t Braccio::Stop()
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

RobotStatus_t Braccio::Home()
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

RobotStatus_t Braccio::GotoPose(const Pose_t& target_pose)
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

RobotStatus_t Braccio::GotoJointPositions(const JointState_t& target_joints)
{
    SetState(RobotState::MOVING);
    return WriteServos(target_joints);
}

/* -- Public getter methods ------------------------------------------------- */


/* -- Public setter methods ------------------------------------------------- */


/* -- Private helper methods ------------------------------------------------ */
RobotStatus_t Braccio::InverseKinematics(const Pose_t& pose, JointState_t& solution)
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

RobotStatus_t Braccio::ForwardKinematics(const JointState_t& joints, Pose_t& pose)
{
    RobotStatus_t ReturnValue = STATUS_OK;

    return ReturnValue;
}

RobotStatus_t Braccio::WriteServos(const JointState_t& joints)
{
    RobotStatus_t ReturnValue = STATUS_OK;

    for (size_t i = 0 ; i < NUM_JOINTS; i++)
    {
       ReturnValue = (RobotStatus_t)JointGroup_.axis_[i]->SetAngle(joints.positions_[i]);
       if (ReturnValue != STATUS_OK)
       {
            ESP_LOGE(TAG, "Failed to set Angle for Joint %d", i + 1);
            break;
       }
       else
       {
            ESP_LOGI(TAG, "Set Joint %d to angle %.2f degrees", i + 1, joints.positions_[i]);
            JointState_.positions_[i] = joints.positions_[i]; // Update current state
       }
    }

    return ReturnValue;
}

/* -- Extern C wrapper (if needed for C interop) ----------------------------- */

// extern "C" {
//     void template_init() { /* ... */ }
// }
