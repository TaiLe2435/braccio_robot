/*
 * servo.cpp
 * Description: Servo control with NPN transistor level shifter (inverted signal)
 */

/* -- Includes -------------------------------------------------------------- */
#include "servo.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* -- Constants ------------------------------------------------------------- */
static const char *TAG = "SERVO";

// PWM Configuration
#define SERVO_FREQ_HZ       50      // Standard servo frequency
#define SERVO_RESOLUTION    13      // 13-bit resolution = 8192 steps
#define SERVO_MAX_DUTY      8192    // 2^13

// Servo timing (adjust these if needed for your specific servos)
#define PULSE_MIN_MS        1.0f    // 0° position
#define PULSE_MAX_MS        2.0f    // 180° position
#define PULSE_PERIOD_MS     20.0f   // 50Hz = 20ms period

/* -- Constructor / Destructor ---------------------------------------------- */
Servo::Servo() {
    // Constructor
}

Servo::~Servo() {
    // Destructor
}

/* -- Initialization -------------------------------------------------------- */
ServoStatus_t servo_init(void) {
    ESP_LOGI(TAG, "Initializing servo on GPIO %d", J1_PIN);
    ESP_LOGI(TAG, "Using inverted signal: %s", USE_INVERTED_SIGNAL ? "YES" : "NO");
    
    // Step 1: Configure GPIO with pull-down before LEDC takes over
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << J1_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Keeps transistor OFF on boot
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_ERROR_CHECK(gpio_set_level(J1_PIN, 0));  // Explicitly set LOW
    
    ESP_LOGI(TAG, "GPIO configured with pull-down");
    
    // Small delay to stabilize
    vTaskDelay(pdMS_TO_TICKS(50));
    
    // Step 2: Configure LEDC timer
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = (ledc_timer_bit_t)SERVO_RESOLUTION,
        .timer_num = J1_LEDC_TIMER,
        .freq_hz = SERVO_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));
    
    ESP_LOGI(TAG, "LEDC timer configured: %dHz, %d-bit resolution", 
             SERVO_FREQ_HZ, SERVO_RESOLUTION);
    
    // Step 3: Configure LEDC channel
    ledc_channel_config_t ch_conf = {
        .gpio_num = J1_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = J1_LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = J1_LEDC_TIMER,
        .duty = 0,  // Start with 0 duty (transistor OFF, signal at 5V)
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ch_conf));
    
    ESP_LOGI(TAG, "LEDC channel configured successfully");
    return STATUS_OK;
}

/* -- Control Methods ------------------------------------------------------- */
ServoStatus_t servo_set_angle(float angle) {
    // Clamp angle to valid range
    if (angle < 0.0f) {
        ESP_LOGW(TAG, "Angle %.1f° clamped to 0°", angle);
        angle = 0.0f;
    }
    if (angle > 180.0f) {
        ESP_LOGW(TAG, "Angle %.1f° clamped to 180°", angle);
        angle = 180.0f;
    }
    
    // Calculate pulse width in milliseconds
    // Linear mapping: 0° = 1.0ms, 180° = 2.0ms
    float pulse_ms = PULSE_MIN_MS + (angle / 180.0f) * (PULSE_MAX_MS - PULSE_MIN_MS);
    
    // Convert to duty cycle value
    // Duty = (pulse_width / period) * max_duty
    uint32_t duty = (uint32_t)((pulse_ms / PULSE_PERIOD_MS) * SERVO_MAX_DUTY);
    
#if USE_INVERTED_SIGNAL
    // Invert duty cycle because NPN transistor inverts the signal
    // When PWM is HIGH, transistor turns ON and pulls signal LOW
    // When PWM is LOW, transistor turns OFF and pull-up brings signal HIGH
    uint32_t final_duty = SERVO_MAX_DUTY - duty;
    
    ESP_LOGI(TAG, "Angle: %.1f° | Pulse: %.3fms | Duty: %lu -> Inverted: %lu", 
             angle, pulse_ms, duty, final_duty);
#else
    uint32_t final_duty = duty;
    
    ESP_LOGI(TAG, "Angle: %.1f° | Pulse: %.3fms | Duty: %lu", 
             angle, pulse_ms, duty);
#endif
    
    // Set duty cycle
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, J1_LEDC_CHANNEL, final_duty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, J1_LEDC_CHANNEL));
    return STATUS_OK;
}