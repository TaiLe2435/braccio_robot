/*
 * main.cpp
 * Description: Test program for Braccio servo control
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "servo.h"
#include "braccio.hpp"

static const char *TAG = "MAIN";

static void MoveShoulderSweep(Braccio& braccio,
                              const Braccio::JointState_t& base,
                              float start_deg,
                              float end_deg,
                              float step_deg,
                              int delay_ms)
{
    Braccio::JointState_t cmd = base;

    if (start_deg < end_deg)
    {
        for (float a = start_deg; a <= end_deg; a += step_deg)
        {
            cmd.positions_[1] = a;  // shoulder joint
            braccio.GotoJointPositions(cmd);
            vTaskDelay(pdMS_TO_TICKS(delay_ms));
        }
    }
    else
    {
        for (float a = start_deg; a >= end_deg; a -= step_deg)
        {
            cmd.positions_[1] = a;
            braccio.GotoJointPositions(cmd);
            vTaskDelay(pdMS_TO_TICKS(delay_ms));
        }
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "===========================================");
    ESP_LOGI(TAG, "  Braccio Robot Servo Test - ESP32");
    ESP_LOGI(TAG, "===========================================");
    
    Braccio braccio;
    braccio.Init();

    // Test some joint angles
    Braccio::JointState_t base = 
    {
        .positions_ = {90.0f, 45.0f, 180.0f, 180.0f, 90.0f}
    };

    ESP_LOGI(TAG, "Moving to base pose...");
    braccio.GotoJointPositions(base);
    vTaskDelay(pdMS_TO_TICKS(3000));

    while (true)
    {
        ESP_LOGI(TAG, "Sweeping shoulder joint...");

        MoveShoulderSweep(
            braccio,
            base,
            15.0f,     // start angle
            165.0f,    // end angle
            2.0f,      // step size
            50         // ms delay (controls smoothness)
        );

        vTaskDelay(pdMS_TO_TICKS(2000));

        ESP_LOGI(TAG, "Sweeping back...");

        MoveShoulderSweep(
            braccio,
            base,
            165.0f,
            15.0f,
            2.0f,
            50
        );

        vTaskDelay(pdMS_TO_TICKS(2000));
    }

}