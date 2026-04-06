/*
 * main.cpp
 * Description: Test program for Braccio servo control
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "servo.h"

static const char *TAG = "MAIN";

static ServoDriver_t J3 = 
{
    .ServoNumber = SERVO_3,
    .Pin = J3_PIN,
    .Channel = J3_LEDC_CHANNEL,
    .Timer = J3_LEDC_TIMER
};

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "===========================================");
    ESP_LOGI(TAG, "  Braccio Robot Servo Test - ESP32");
    ESP_LOGI(TAG, "===========================================");
    
    // Initialize servo system
    Servo J3(J3);
    J3.Init();
    
    // Wait for system to stabilize
    vTaskDelay(pdMS_TO_TICKS(500));
    
    // Move to safe home position (90° = middle)
    ESP_LOGI(TAG, "Moving to home position (90°)...");
    J3.SetAngle(90);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    ESP_LOGI(TAG, "Starting test sequence...\n");
    
    // Test 1: Move to extremes
    ESP_LOGI(TAG, "TEST 1: Moving to 0°");
    J3.SetAngle(0);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    ESP_LOGI(TAG, "TEST 1: Moving to 180°");
    J3.SetAngle(180);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    ESP_LOGI(TAG, "TEST 1: Moving back to 90°");
    J3.SetAngle(90);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Test 2: Smooth sweep
    ESP_LOGI(TAG, "\nTEST 2: Starting smooth sweep (0° -> 180°)");
    for (int angle = 0; angle <= 180; angle += 10) {
        J3.SetAngle(angle);
        vTaskDelay(pdMS_TO_TICKS(500));  // 500ms per step
    }
    
    ESP_LOGI(TAG, "TEST 2: Reverse sweep (180° -> 0°)");
    for (int angle = 180; angle >= 0; angle -= 10) {
        J3.SetAngle(angle);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
    // Test 3: Continuous operation
    ESP_LOGI(TAG, "\nTEST 3: Continuous sweep loop");
    int sweep_count = 0;
    
    while (1) {
        sweep_count++;
        ESP_LOGI(TAG, "Sweep cycle #%d", sweep_count);
        
        // Sweep forward
        for (int angle = 0; angle <= 180; angle += 15) {
            J3.SetAngle(angle);
            vTaskDelay(pdMS_TO_TICKS(300));
        }
        
        // Sweep backward
        for (int angle = 180; angle >= 0; angle -= 15) {
            J3.SetAngle(angle);
            vTaskDelay(pdMS_TO_TICKS(300));
        }
        
        // Pause between cycles
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}